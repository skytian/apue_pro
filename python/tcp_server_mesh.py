#!/usr/bin/env python3
#-*- coding:utf-8 -*-

from socket import *
from time import ctime
import json

host = '192.168.0.7'
#host = '127.0.0.2'
port = 5555
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
                rtdata='{\"dest\":\"123\",\"from\":666,\"subs\":[{\"nodeId\":\"1\",\"subs\":[{\"nodeId\":\"11\",\"subs\":[]},{\"nodeId\":\"12\",\"subs\":[]},{\"nodeId\":\"13\",\"subs\":[]},{\"nodeId\":\"14\",\"subs\":[]}]},{\"nodeId\":\"2\",\"subs\":[{\"nodeId\":\"21\",\"subs\":[]},{\"nodeId\":\"22\",\"subs\":[]}]},{\"nodeId\":\"3\",\"subs\":[{\"nodeId\":\"31\",\"subs\":[]},{\"nodeId\":\"32\",\"subs\":[]}]}]}'
                if not rtdata:
                    break
                #tctimeClient.send(rtdata.encode())
                tctimeClient.send(rtdata)
                print("#########send:",rtdata.encode())
                tctimeClient.close()
    except:
        print "error connect"
tctimeClient.close()
