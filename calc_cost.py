def calc_cost(vul, no_of_vm):
	#create list
	cost = list();
	for i in range(no_of_vm):
		cost.append(0);

	file = open("t.txt", "r")
	res = file.read()
	pro = res.split("\n\n")

	tmp1 = pro[0].split("\n")
	del(tmp1[0]) #del first \n
	tcp = tmp1[int(vul)].split(" ")
	tcp.pop() #delete last /n

	tmp2 = pro[1].split("\n")
	udp = tmp2[int(vul)].split(" ")
	udp.pop() #delete last /n

	tmp3 = pro[2].split("\n")
	tmp3.pop() #delete last /n
	icmp = tmp3[int(vul)].split(" ")
	icmp.pop() #delete last /n

	for i in tcp:
		cost[int(i)] += 15

	for i in udp:
		cost[int(i)] += 35

	for i in icmp:
		cost[int(i)] += 50

	return cost

print calc_cost(2, 8)

#res = file.split("\n\n")
#print res
#file = open("impact_tcp.txt", "r")
#lines=file.readlines()
#res = lines[int(vul) - 1].split(" ")
#print(res)
#for i in res:
#	cost[int(i) - 1] += 15

	
