'''
socket programming server
'''
import socket

HOST = 'localhost'
PORT = 12345
connected = True
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    conn, addr = s.accept()
    with conn:
        print('Connected by', addr)
        while True:
            data = conn.recv(1024)
            if data == "exit":
                connected = False
                break
            print('Received:', data.decode())
            MESSAGE = input()
            if connected:
                conn.send(MESSAGE.encode())
            else:
                conn.send("exit".encode())
                conn.close()
