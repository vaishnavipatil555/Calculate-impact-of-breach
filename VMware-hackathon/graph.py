# Python program to print DFS traversal for complete graph 
from collections import defaultdict 
import re
import sys

# This class represents a directed graph using adjacency 
# list representation 
class Graph: 

	# Constructor 
	def __init__(self): 

		# default dictionary to store graph 
		self.graph = defaultdict(list) 

	# function to add an edge to graph 
	def addEdge(self,u,v): 
		self.graph[u].append(v) 

	# A function used by DFS 
	def DFSUtil(self, v, visited, res, space, prev_space, leave, f1): 

		# Mark the current node as visited and print it 
		visited[v]= True
		#print(v)

		prefix = ""
		for x in range(0, leave):
			prefix = prefix + ' '
		f1.write(prefix + '|')
		f1.write(space + str(v) + "\n")

		leave = len(prev_space + '|' + space + str(v))

		"""
		leav = ""
		for i in range(0, leave):
			leav = leav + ' '

		f1.write(leav + "\n")
		"""

		res.append(v)
		# Recur for all the vertices adjacent to 
		# this vertex 
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

	# The function to do DFS traversal. It uses 
	# recursive DFSUtil() 
	def DFS(self): 
		V = len(self.graph) #total vertices 

		# Mark all the vertices as not visited 
		visited =[False]*(V) 

		# Call the recursive helper function to print 
		# DFS traversal starting from all vertices one 
		# by one 
		for i in range(V): 
			if visited[i] == False: 
				self.DFSUtil(i, visited) 

if __name__ == '__main__':

	f = open("info.txt", "r")
	lis = f.readlines()
	#print(lis)
	ug = Graph()
	tg = Graph()
	ig = Graph()

	"""
	l = len(lis)
	for _ in range(0, int(sys.argv[1]) - l):
		lis.append("\n")
	"""

	fp = open("tot_nodes.txt", "w")
	fp.write(str(len(lis)))
	fp.close()

	for i in range(0, len(lis)):
		li = lis[i].strip().split(" ")
		#print(li)
		for x in li:
			temp = re.findall(r'\d+', x) 
			try:
				#print(temp[0])
				if(x[len(x) - 2] == 'u'):
					#print("*")
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
		#f.write(str(res))
		
		s = ""
		for x in res:
			s = s + str(x) + " "
		f.write(s)
		f.write("\n")
		#print(res)
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

		#print(res)
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

		#print(res)
	f.close()
	f1.close()


