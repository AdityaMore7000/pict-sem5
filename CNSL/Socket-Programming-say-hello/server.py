'''
Socket programming server
'''
import socket
s = socket.socket()
print ("Socket successfully created")
IP='127.0.0.1'
PORT = 12346
s.bind((IP, PORT))
print (f"socket bound to {PORT}")
s.listen(5)
print ("socket is listening\n")
while True:
    c, addr = s.accept()
    c.send('Hello Client'.encode())
    print(c.recv(1024).decode())
    c.close()
    break
