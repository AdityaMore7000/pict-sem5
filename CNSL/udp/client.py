import socket

# create a UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# send some data to the server
server_address = ('localhost', 12345)
message = input("Enter message: ").encode()
sock.sendto(message, server_address)

# receive the response from the server
data, server = sock.recvfrom(4096)
print('Received:', data.decode())