#! /usr/bin/python3
"""这是一个UDP协议的client"""
from socket import *
from sys import *
HOSTNAME='127.0.0.1'
PORT=6669
ADDRESS=(HOSTNAME,PORT)
"""UDP socket很简单，只要建立socket对象，然后向目标地址发送数据，然后接收响应就可以了。
但是在发送数据时，因为没有建立连接，所以需要指定目标地址端口。同理，接收时也最好获取到来源主机的地址端口
"""
def udp_client():
    clientSocket = socket(AF_INET,SOCK_DGRAM)
    message = input('please input a lowercase message:')
    clientSocket.sendto(message.encode('utf-8'),ADDRESS)
    modified_message,serveraddress = clientSocket.recvfrom(2048)
    print(modified_message.decode('utf-8'))
    clientSocket.close()

"""相对于UDP，TCP需要建立连接。而且TCP需要两个套接字：握手套接字，连接套接字。
对于客户端，握手套接字是透明的（即无需关心握手套接字的存在，但是服务器端需要区分两者。）
建立套接字对象 --> 连接目标主机 --> 发送数据 --> 接收数据 --> 关闭连接
"""
def tcp_client():
    clientSocket = socket(AF_INET,SOCK_STREAM)
    clientSocket.connect(ADDRESS) # 相比UDP，这里多了建立连接的步骤
    message = input('please input a lowercase message:')
    clientSocket.sendall(message.encode('utf-8'))
    modified_message = clientSocket.recv(2048)
    print(modified_message.decode('utf-8'))
    clientSocket.close()

if __name__ == "__main__":
    tcp_client()
