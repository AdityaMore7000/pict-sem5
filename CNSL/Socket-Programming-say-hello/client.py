'''
Socket programming server
'''
import socket
s = socket.socket()
PORT = 12346
s.connect(('127.0.0.1', PORT))
print (s.recv(1024).decode())
s.send('Hello server'.encode())
s.close()
