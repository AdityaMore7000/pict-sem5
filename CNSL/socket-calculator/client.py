'''
socket client 
'''
import socket

HOST = 'localhost'
PORT = 65432

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    print('Connected to server')
    while True:
        message = input('Enter a message to send to the server: ')
        s.sendall(message.encode())
        data = s.recv(1024)
        print('Received from server:', data.decode())
