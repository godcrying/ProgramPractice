#! /usr/bin/python3
#
from pysnmp.hlapi import *

for (errorIndication,
     errorStatus,
     errorIndex,
     varBinds) in nextCmd(
                          SnmpEngine(),
                          CommunityData('z93657'),
                          UdpTransportTarget(('10.0.25.2', 161)),
                          ContextData(),
                          ObjectType(ObjectIdentity('1.3.6.1.2.1.2.2')),
                          lexicographicMode=False):

    if errorIndication:
        print(errorIndication)
    elif errorStatus:
        print('%s at %s' % (errorStatus.prettyPrint(),
                            errorIndex and varBinds[int(errorIndex) - 1][0] or '?'))
    else:
        for varBind in varBinds:
            print(' = '.join([x.prettyPrint() for x in varBind]))
