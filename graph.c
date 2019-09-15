#include<stdio.h>
#include<stdlib.h>
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

adjListNode* newadjListNode(int dest) 
{ 
    adjListNode* newNode = (adjListNode*) malloc(sizeof(adjListNode)); 
    newNode->data = dest; 
    newNode->next = NULL; 
    return newNode; 
} 

void addEdge(Graph* graph, int src, int dest) 
{ 
    adjListNode* newNode = newadjListNode(dest); 
    newNode->next = graph->arr[src].head; 
    graph->arr[src].head = newNode; 
} 

void printGraph(Graph* graph) 
{ 
    int v; 
    for (v = 0; v < graph->V; ++v) 
    { 
        adjListNode* pCrawl = graph->arr[v].head; 
        printf("\n Adjacency list of vertex %d\n head ", v); 
        while (pCrawl) 
        { 
            printf("-> %d", pCrawl->data); 
            pCrawl = pCrawl->next; 
        } 
        printf("\n"); 
    } 
    printf("\n\n\n\n");
} 