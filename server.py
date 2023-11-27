import socket

MAX_LEN = 1024

port = 3000
host = '148.204.63.78'
#host = '127.0.0.1'

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((host, port))
    s.listen()
    print('Escuchando')
    while True:
        conn, addr = s.accept()
        with conn:
            while True:
                data = conn.recv(MAX_LEN)
                print('Mensaje:', data)
                #num = 2 * int(data)
                #num_str = str(num)
                print('Envia:', data)
                conn.sendall(data)

