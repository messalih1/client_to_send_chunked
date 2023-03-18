#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

#include <fcntl.h>
#include <unistd.h>
#include <sstream>

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <curl/curl.h>

#define PORT 8081
using namespace std;

int main(int ac, char *argv[])
{
    string path = argv[1];
    string contentType;
    string header;
    
    int flag = 0;
    int f =  path.find("jpg");
    if(f != -1)
    {
        contentType = "image/jpg";
        flag = 10;
    }
    f =  path.find("video");
    if(f != -1 && flag == 0)
    {
        contentType = "video/mp4";
        flag = 10;
    }
    f = path.find("pdf");
    if(f != -1 && flag == 0)
    {
        contentType = "application/pdf";
        flag = 10;
    }
    if(flag == 0)
        contentType = "application/octet-stream";

    header = "POST / HTTP/1.1\r\nHost: 127.0.0.1:8081\r\nUser-Agent: vscode..\r\n"; 
    header.append("Content-Type: ").append(contentType).append("\r\n").append("Transfer-Encoding: chunked\r\n\r\n");
   
    int sock = 0; long valread;
    struct sockaddr_in serv_addr;
     
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
    
    memset(&serv_addr, '0', sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

     
    ifstream file(path, ios::binary);
    int chunk_size_read;
    int size = 1000;
    string chunk_data("\0",size);// use string

    send(sock , (void *)(header.data()) , header.size() , 0 );
 
    while (!file.eof()) 
    {
        string data = "";
        
        file.read((char*)(chunk_data.data()), size);
        
        chunk_size_read = file.gcount();
        
        if(chunk_size_read < size)
        {
            std::ostringstream ss;
            ss << std::hex << chunk_size_read;
            chunk_data.resize(chunk_size_read);
            
            std::string result = ss.str();
            data.append(result).append("\r\n").append(chunk_data).append("\r\n0\r\n\r\n");
            send(sock , (void *)(data.data()) , data.size() , 0 );
            // write(fd,(void*)(data.data()),data.size());
        }
        else
        { 
            std::ostringstream ss;
            ss << std::hex << chunk_size_read;

            std::string result = ss.str();
            data.append(result).append("\r\n").append(chunk_data).append("\r\n");
            send(sock , (void *)(data.data()) , data.size() , 0 );
        }
    
    }


}
