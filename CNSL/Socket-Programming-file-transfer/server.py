import socket

# create a server socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# bind the socket to a specific IP address and port number
server_address = ('localhost', 12345)
server_socket.bind(server_address)

# listen for incoming connections
server_socket.listen(1)

# accept a connection from a client
client_socket, client_address = server_socket.accept()

# read the file from the server
filename = './server/example.txt'
with open(filename, 'rb') as f:
    file_data = f.read()

# send the file data to the client
client_socket.sendall(file_data)

# close the sockets
client_socket.close()
server_socket.close()