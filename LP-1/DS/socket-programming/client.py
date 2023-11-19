'''
socket programming client
'''
import socket
import sys

HOST = 'localhost'
PORT = 12345

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    while True:
        MESSAGE = input()
        s.send(MESSAGE.encode())
        data = s.recv(1024)
        if data.decode() == "exit":
            print("Bye")
            sys.exit(1)
        print('Received:', data.decode())
