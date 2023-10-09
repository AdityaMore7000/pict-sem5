'''
Socket programming server
'''
import socket
s = socket.socket()
print ("Socket successfully created")
ip='127.0.0.1'
port = 12346
s.bind((ip, port))
print ("socket binded to %s"%(port))
s.listen(5)
print ("socket is listening\n")
while True:
    c, addr = s.accept()
    c.send('Hello Client'.encode())
    print(c.recv(1024).decode())
    c.close()
    break
