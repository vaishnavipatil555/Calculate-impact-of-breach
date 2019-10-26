# Python program to print DFS traversal for complete graph 
from collections import defaultdict 
import re
import sys
 
class Graph: 
	def __init__(self): 
		self.graph = defaultdict(list) 

	def addEdge(self,u,v): 
		self.graph[u].append(v) 

	def DFSUtil(self, v, visited, res, space, prev_space, leave, f1): 
		visited[v]= True
		prefix = ""
		for x in range(0, leave):
			prefix = prefix + ' '
		f1.write(prefix + '|')
		f1.write(space + str(v) + "\n")
		leave = len(prev_space + '|' + space + str(v))

		res.append(v)
		
		for i in self.graph[v]:
			try:
				if visited[int(i[0])] == False: 
					self.DFSUtil(int(i[0]), visited, res, '_______________________', space, leave, f1) 
			except:
				pass

	def dfs_from_node(self, v, length, f1):
		visited = [False] * (length)
		res = list()
		self.DFSUtil(v, visited, res, '', '', 0, f1)
		return res
	
	def DFS(self): 
		V = len(self.graph) #total vertices 
		visited =[False]*(V) 
		for i in range(V): 
			if visited[i] == False: 
				self.DFSUtil(i, visited) 

if __name__ == '__main__':

	f = open("info.txt", "r")
	lis = f.readlines()
	
	ug = Graph()
	tg = Graph()
	ig = Graph()

	
	fp = open("tot_nodes.txt", "w")
	fp.write(str(len(lis)))
	fp.close()

	for i in range(0, len(lis)):
		li = lis[i].strip().split(" ")
		for x in li:
			temp = re.findall(r'\d+', x) 
			try:
				if(x[len(x) - 2] == 'u'):
					ug.addEdge(i, temp)
				elif (x[len(x) - 2] == 't'):
					tg.addEdge(i, temp)
				elif (x[len(x) - 2] == 'i'):
					ig.addEdge(i, temp)
			except:
				pass
			
	f.close()
	
	f = open("./impact/impact_udp.txt", "w")
	f1 = open("./tree/tree_udp.txt", "w")
	for i in range(0, len(lis)):
		visited = [False] * (len(lis))
		res = ug.dfs_from_node(i, len(lis), f1) 
		f1.write("\n")
	
		s = ""
		for x in res:
			s = s + str(x) + " "
		f.write(s)
		f.write("\n")
	f.close()
	f1.close()

	f = open("./impact/impact_tcp.txt", "w")
	f1 = open("./tree/tree_tcp.txt", "w")
	for i in range(0, len(lis)):
		visited = [False] * (len(lis))
		res = tg.dfs_from_node(i, len(lis), f1) 
		f1.write("\n")
		s = ""
		for x in res:
			s = s + str(x) + " "
		f.write(s)
		f.write("\n")

	f.close()
	f1.close()

	f = open("./impact/impact_icmp.txt", "w")
	f1 = open("./tree/tree_icmp.txt", "w")
	for i in range(0, len(lis)):
		visited = [False] * (len(lis))
		res = ig.dfs_from_node(i, len(lis), f1) 
		f1.write("\n")
		s = ""
		for x in res:
			s = s + str(x) + " "
		f.write(s)
		f.write("\n")

	f.close()
	f1.close()