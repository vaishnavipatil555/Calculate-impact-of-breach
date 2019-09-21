typedef struct adjListNode{
	int data;
	struct adjListNode *next;
}adjListNode;

typedef struct adjList{
	adjListNode *head;
}adjList;

typedef struct Graph{
	int V;
	adjList* arr;
}Graph;

Graph* createGraph(int V) 
{ 
    Graph* graph =   (Graph*) malloc(sizeof(Graph)); 
    graph->V = V; 
  
    graph->arr =  (adjList*) malloc(V * sizeof(adjList)); 
  
    int i; 
 
    for (i = 0; i < V; ++i) 
        graph->arr[i].head = NULL; 

    return graph; 
} 

adjListNode* newadjListNode(int data) 
{ 
    adjListNode* newNode = (adjListNode*) malloc(sizeof(adjListNode)); 
    newNode->data = data; 
    newNode->next = NULL; 
    return newNode; 
} 

void addEdge(Graph* graph, int src, int dest) 
{ 
    adjListNode* newNode = newadjListNode(dest); 
    newNode->next = graph->arr[src].head; 
    graph->arr[src].head = newNode; 
} 

void dfsUtil(Graph *graph, int index, int *visited){
	adjListNode *p = graph -> arr[index].head;
	if(p == NULL)
	{
		visited[index] = 1; 
		//printf("%d \n", index);
		return;
	}
	
	visited[index] = 1;
	while(p != NULL){
		if(visited[p -> data] == 0)
			dfsUtil(graph, p -> data, visited);
		p = p -> next;
	}
	//printf("%d \n", index);
}

int* dfs_from_node(Graph *graph, int index){
	int *visited;
	visited = (int*)malloc(sizeof(graph -> V));
	
	for(int i = 0; i < graph -> V; i++){
		visited[i] = 0;
	}
	dfsUtil(graph, index, visited);
	/*for(int i = 0; i < graph -> V; i++){
		if(visited[i] == 1)
			printf("* %d \n", i);
	}*/
	return visited;
}

void printGraph(Graph* graph) 
{ 
    int v; 
    for (v = 0; v < graph->V; ++v) 
    { 
        adjListNode* p = graph->arr[v].head; 
        //printf("\n Adjacency list of vertex %d\n head ", v); 
        while (p) 
        { 
            //printf("-> %d", p->data); 
            p = p->next; 
        } 
        //printf("\n"); 
    } 
    //printf("\n");
    return;
} 
