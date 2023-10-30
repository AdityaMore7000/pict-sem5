import socket

# create a UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# bind the socket to a specific address and port
server_address = ('localhost', 12345)
sock.bind(server_address)

while True:
    # receive data from a client
    data, address = sock.recvfrom(4096)
    
    # process the data
    processed_data = data.upper()
    
    # send the processed data back to the client
    sock.sendto(processed_data, address)