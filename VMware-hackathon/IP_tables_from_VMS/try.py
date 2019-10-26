import os
dirname = 'iptables'
filename = 'iptable'
wd = os.getcwd()

with open(filename, 'wb') as fp:
	fp.seek(0)
	path = os.path.join(wd, dirname)
	os.chdir(path)
	curr = os.getcwd()
	filenames = list(os.listdir(curr))
	i = 0
	for f in filenames:		
		if f.find('~') == -1:			
			with open(f, 'rb') as fd:
				fd.seek(0)
				data = fd.readline()
				j = 0
				while data:
					if i != 0 and j == 0:
						data = fd.readline()
						j = 1
					fp.write(data)
					data = fd.readline()
				i = 1
		else:
			pass
		
		
		



