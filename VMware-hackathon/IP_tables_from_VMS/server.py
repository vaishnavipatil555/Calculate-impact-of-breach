from socket import *
from threading import *
import os
import sys

def createSocket():
	try:
		global Sock 
		Sock = socket(AF_INET,SOCK_STREAM)
	except error, msg:
		print 'Can\'t connect: '+ msg[1]

def bindSocket():
	try:
		global Port
		global Sock
		Port = 2127
		Sock.bind(('',Port))
		Sock.listen(10)
	except error, msg:
		print 'Can\'t connect: '+ msg[1]
		sys.exit()
	
def sockAccept():
	global conn, addr
	conn, addr = Sock.accept()

def clientThread():
	global conn, addr
	filename = addr[0]
	wd = os.getcwd()
	dirname = 'iptables'
	if os.path.isdir(dirname) == False:
		path = os.path.join(wd, dirname)
		if os.path.isdir(path) == False:
			os.mkdir(path)
			os.chdir(path)
	else:
		os.chdir(dirname)
	with open(filename,'wb') as f:
		while True:
			data= conn.recv(1024)
			if not data:
				break
			f.write(data)
	os.chdir(wd)

createSocket()
bindSocket()
while True:
	global conn
	sockAccept()
	new_thread = Thread(target = clientThread)
	new_thread.start()


