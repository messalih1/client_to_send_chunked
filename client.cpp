#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
 #include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iconv.h>
#include <iostream>
#include <iostream>
#include <algorithm>
#include <utility>
#include <memory>
#include <stack>
#include <vector>
#include <map>
 #include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <cstring>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <exception>
#include <type_traits>
 

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::stack;


#include <iostream>
#include <fstream>
#include <string>
#define PORT 8080

int main(int argc, char const *argv[])
{
  std::string filename = "file";
  std::ifstream file(filename);

  if (!file) {
    std::cerr << "Failed to open file: " << filename << std::endl;
    return 1;
  }

  std::string line;
  std::getline(file, line);
  
  // while (std::getline(file, line)) {
  //   std::cout << line << std::endl;
  // }
    int sock = 0; long valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
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
    send(sock , (void*)(line.data()) , line.size() , 0 );
    
    return 0;
}