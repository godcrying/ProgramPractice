#! /usr/bin/python3
import os,netsnmp
class Switcher():
    def __init__(self,name,ipaddr):
        self._name = name
        self._ipaddr = ipaddr
    @property
    def name(self):
        return self._name
    @name.setter
    def name(self,value):
        self._name = value
    @property
    def ipaddr(self):
        return self._ipaddr
    @ipaddr.setter
    def ipaddr(self,value):
        self._ipaddr = value

#netsnmp的一个例子
sess = netsnmp.Session(DestHost='10.0.25.126',Version=2,Community='z93657')
varlist = netsnmp.VarList(netsnmp.Varbind('.1.3.6.1.2.1.2.2.1.2'))
print(sess.walk(varlist))

SW_list = []
