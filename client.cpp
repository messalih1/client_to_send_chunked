import random
import os
import sys
import requests

# Open the file and read its contents
filename = 'test\ copy.txt'
with open(filename, 'rb') as f:
    data = f.read()

# Define the endpoint URL and headers
url = '127.0.0.1:8085'
headers = {'Transfer-Encoding': 'chunked'}

# Send the data in chunks
while len(data) > 0:
    # Choose a random chunk size between 1 and 10 bytes
    chunk_size = random.randint(5055, 10000)

    # Send the next chunk
    chunk = data[:chunk_size]
    data = data[chunk_size:]
    requests.post(url, headers=headers, data='%x\r\n%s\r\n' % (chunk_size, chunk))

# Send the final chunk with size 0
requests.post(url, headers=headers, data='0\r\n\r\n')
