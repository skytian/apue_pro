#!/usr/bin/env python3
from socket import *
import json

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
    print("recv:",data)
    msg = json.loads(data)
    if msg['type']==6:
        data='{"dest":0,"from":1929488,"type":4,"msg":{"type":1,"t0":2474476}}'         
        tctimeClient.send(data.encode())
        data = tctimeClient.recv(BUFFSIZE).decode()
        if not data:
            break
        print("recv:",data)
        rcvjson = json.loads(data)
        if rcvjson['type'] == 4:
            sycntype = rcvjson['msg']['type']
            if sycntype == 2:
                t2 = rcvjson['msg']['t2']
                data = '{"dest":0,"from":1929488,"type":4,"msg":{"type":1,"t0":%d}}'%t2
                tctimeClient.send(data.encode())
                data = tctimeClient.recv(BUFFSIZE).decode()
                print("recv:",data)
        
        
tctimeClient.close()

