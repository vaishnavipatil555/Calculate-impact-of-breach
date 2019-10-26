def calc_cost_fun(tcp_cost, udp_cost, icmp_cost, vul, no_of_vm):
	cost = list();
	for i in range(no_of_vm):
		cost.append(0)

	file = open("./impact/impact_tcp.txt", "r")
	lines=file.readlines()
	res = lines[int(vul)].strip().split(" ")
	
	for i in res:
		cost[int(i)] += tcp_cost

	file = open("./impact/impact_udp.txt", "r")
	lines=file.readlines()
	res = lines[int(vul)].strip().split(" ")
	for i in res:
		cost[int(i)] += udp_cost

	file = open("./impact/impact_icmp.txt", "r")
	lines=file.readlines()
	res = lines[int(vul)].strip().split(" ")
	for i in res:
		cost[int(i)] += icmp_cost

	return cost
