import socket

host = 'localhost'
port = 12345

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((host, port))
    message = 'Hello, server!'
    s.sendall(message.encode())
    data = s.recv(1024)
    print('Received:', data.decode())