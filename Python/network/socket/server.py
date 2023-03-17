#! /usr/bin/python3
from socket import *
SERVER_TYPE="TCP"
if SERVER_TYPE=="UDP":
    serverSocket = socket(AF_INET,SOCK_DGRAM)
    serverSocket.bind(('127.0.0.1',6669))
    print('This server is ready to recieve message:')
    while True:
        message,clientAddress = serverSocket.recvfrom(2048)
        modifiedMessage = message.upper()
        serverSocket.sendto(modifiedMessage,clientAddress)

"""TCP--server端的数据流程：
建立socket对象（握手套接字）--> 绑定端口 --> 启动TCP监听 --> 接受请求并建立连接（连接套接字）
--> 接收数据 --> 处理、发送数据 --> 关闭连接
"""
if SERVER_TYPE=="TCP":
    serverSocket = socket(AF_INET,SOCK_STREAM)
    serverSocket.bind(('127.0.0.1',6669))
    print('This server is ready to recieve message:')
    serverSocket.listen() # 启动监听，listen可以有参数，定义待处理请求队列的长度。超过队列长度后的请求会被拒绝。
    while True:
        conSocket,clientAddress = serverSocket.accept() # 处理的客户端的connect，建立连接套接字
        message = conSocket.recv(2048)
        modifiedMessage = message.upper()
        conSocket.send(modifiedMessage)
