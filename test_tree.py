if __name__ == '__main__':
	f = open("tree_udp.txt", 'r')
	lis = f.readlines()

	li = list()
	for i in range(0, len(lis)):
		l = list()
		for j in range(0, len(lis[i])):
			l.append(lis[i][j])
		li.append(l)

	for x in li:
		print(x)


	for i in range(0, len(lis)):
		for j in range(0, len(lis[i])):
			if(lis[i][j] == '|'):
				try:
					if lis[i + 1][j] == ' ':
						lis[i + 1][j] = '|'
				except:
					continue
	

	"""
	for i in range(0, len(lis)):
		print(lis[i])
		for j in range(0, len(lis[i])):
			print(lis[i][j])
	for x in lis:
		print(x)
	
	f.close()
	"""