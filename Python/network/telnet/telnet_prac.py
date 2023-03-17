import getpass
import telnetlib

HOST = "10.0.25.2"
USER = input("Enter your name remote account:")
PASSWORD = getpass.getpass()

tn = telnetlib.Telnet(HOST)

tn.read_until(b"Username:")
tn.write(USER.encode('ascii') + b"\n")
if PASSWORD:
    tn.read_until(b"Password:")
    tn.write(PASSWORD.encode('ascii') + b"\n")
    
tn.read_until(b"<BJ-YHG-S1-GX>")
tn.write(b"dis cu\n")

print(tn.read_all().decode('ascii'))

tn.write(b"q\n")
tn.close()
