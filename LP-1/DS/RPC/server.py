'''
RPC for server
'''
from xmlrpc.server import SimpleXMLRPCServer

def cube(n):
    cb = n * n * n 
    return cb

def factorial(n):
    fact = 1
    if(n < 0):
        return -1
    for i in range(1, n + 1):
        fact = fact * i
    return fact

port = 8000

server = SimpleXMLRPCServer(("localhost", port), logRequests = False)
server.register_function(factorial, 'factorial_rpc')
server.register_function(cube, 'cube_rpc')

try:
    print("Server started and is listening on Port ", port)
    server.serve_forever()
except Exception as e:
    print("Error:",e)
finally:
    print("Server Shutting down")
    server.server_close()
