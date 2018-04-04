#!/usr/bin/env python3
#-*- coding:utf-8 -*-

from socket import *
from time import ctime
import json

host = ''
port = 12345
buffsize = 2048
ADDR = (host,port)

tctime = socket(AF_INET,SOCK_STREAM)
tctime.bind(ADDR)
tctime.listen(3)

while True:
    print('Wait for connection ...')
    tctimeClient,addr = tctime.accept()
    print("Connection from :",addr)

    while True:
        rcv = tctimeClient.recv(buffsize).decode()
        print("#########recv:",rcv)
        data=json.loads(rcv)
        print("type:",data['type']) 
        if data['type'] == 5:
            rtdata='{"dest":2786751926,"from":2786614220,"type":6,"subs":[]}'
        elif data['type'] == 4:
            sycntype = data['msg']['type']
            print("sycntype:",sycntype)
            rtdata='{"dest":2786751926,"from":2786614220,"type":4,"msg":{"type":2,"t0":2474476,"t1":4790955,"t2":4805971}}'
        if not rtdata:
            break
        tctimeClient.send(rtdata.encode())
    tctimeClient.close()
tctimeClient.close()
