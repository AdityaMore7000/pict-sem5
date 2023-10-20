import socket

# create a client socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# connect to the server
server_address = ('localhost', 12345)
client_socket.connect(server_address)

# receive the file data from the server
file_data = b''
while True:
    data = client_socket.recv(1024)
    if not data:
        break
    file_data += data

# save the file data to a file on the client
filename = './client/example.txt'
with open(filename, 'wb') as f:
    f.write(file_data)

# close the socket
client_socket.close()