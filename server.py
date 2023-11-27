import socket

port = 3000
host = '148.204.63.78'

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((host, port))
    s.listen()
    while True:
        conn, addr = s.accept()
        with conn:
            while True:
                data = conn.recv(MAX_LEN)
                num = 2 * int(data)
                num_str = str(num)
                conn.sendall(num_str)

