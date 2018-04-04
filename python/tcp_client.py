#!/usr/bin/env python3
from socket import *

HOST ='localhost'

PORT = 12345

BUFFSIZE=2048

ADDR = (HOST,PORT)

tctimeClient = socket(AF_INET,SOCK_STREAM)

tctimeClient.connect(ADDR)

while True:
    data = input(">")
    if not data:
        break
    tctimeClient.send(data.encode())
    data = tctimeClient.recv(BUFFSIZE).decode()
    if not data:
        break
    print(data)
tctimeClient.close()

