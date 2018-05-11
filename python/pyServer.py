#!/usr/bin/python
import sys
import SocketServer
import socket

class echorequestserver(SocketServer.BaseRequestHandler):
    def handle(self):
        print('server start...')
        conn = self.request
        print('connect:', self.client_address)
        while True:
            client_data = conn.recv(1024)
            if not client_data:
                print('break!')
                break
            print(client_data.decode('utf-8'))
            print('start to send...')
            conn.sendall(client_data)
            
if __name__ == '__main__':
    server =SocketServer.TCPServer(("127.0.0.1", 8266),echorequestserver)
    server.serve_forever()
