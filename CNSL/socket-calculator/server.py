'''
socket server
'''
import socket

HOST = 'localhost'
PORT = 65432


def calculate(expression):
    try:
        return str(eval(expression))
    except SyntaxError:
        return 'Invalid expression'


with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    print('Server listening on', (HOST, PORT))
    conn, addr = s.accept()
    with conn:
        print('Connected by', addr)
        while True:
            data = conn.recv(1024)
            if not data:
                break
            expression = data.decode()
            result = calculate(expression)
            conn.sendall(result.encode())
