from socket import *
from sys import *

if len(argv) > 2:
	server = argv[1]
	port = int(argv[2])
else:
	print'Please mention server address and port number\n'
	exit()
sock = socket(AF_INET, SOCK_STREAM)
try:
	sock.connect((server, port))
except error, msg:
	print'Can\'t connect\n' + msg[1]
	exit()
filename = 'iptables'
with open(filename, 'rb') as f:
	l = f.read(1024)
	while (l):
		sock.send(l)
		l = f.read(1024)

sock.close()

