import socket

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
    sock.connect(("192.168.1.6", 9024))
    x = sock.recv(1024)
    print(x)
