#!/usr/bin/env python3
#-*- coding:utf-8 -*-

from socket import *
from time import ctime
import json

host = '192.168.0.7'
port = 8266
buffsize = 2048
ADDR = (host,port)

tctime = socket(AF_INET,SOCK_STREAM)
tctime.bind(ADDR)
tctime.listen(3)

while True:
    print('Wait for connection ...')
    try:
        tctimeClient,addr = tctime.accept()
        print("Connection from :",addr)

        while True:
            rcv = tctimeClient.recv(buffsize).decode()
            if(len(rcv) > 0):
                print("#########recv:",rcv)
                rtdata='ok123456789'
                if not rtdata:
                    break
                #tctimeClient.send(rtdata.encode())
                tctimeClient.send(rtdata)
                print("#########send:",rtdata.encode())
                tctimeClient.close()
    except:
        print "error connect"
tctimeClient.close()
