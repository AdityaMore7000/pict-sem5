'''
socket programming client
'''
import socket

HOST = 'localhost'
PORT = 12345

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    while True:
        MESSAGE = input()
        s.send(MESSAGE.encode())
        data = s.recv(1024)
        if data.decode() == "exit":
            break
        print('Received:', data.decode())
