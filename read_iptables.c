# include <stdio.h> 
# include <string.h> 
# include "graph.c"
int main( ){ 
    FILE *fp ; 
    char dataToBeRead[50]; 
  	char arr[50][50];
 
    fp = fopen("info.txt", "r") ; 

	
    int i = 0;
    while( fgets ( dataToBeRead, 50, fp ) != NULL ){ 
      	strcpy(arr[i], dataToBeRead);
      	i++;
    } 

    fclose(fp); 

    //Argument is number of nodes
	Graph* tg = createGraph(7);
	Graph* ug = createGraph(7);
	Graph* ig = createGraph(7);   
 	char* tok;
 	int j;
	for(int j = 0; j < i; j++)
	{
	 	tok = strtok(arr[j], " ");
	 	while(tok != NULL){
	 		if(tok[0] != '-' && tok[2] == 'a'){
				if(tok[1] == 't'){
					addEdge(tg, j, tok[0] - '0');
				}
				else if(tok[1] == 'u'){
					addEdge(ug, j, tok[0] - '0');
				}
				else{
					addEdge(ig, j, tok[0] - '0');
				}
			}
			tok = strtok(NULL, " ");
		}
	}

	printGraph(ug); 

	int *res;


	printf("Targeted node 0 \nImpacted nodes are :- \n");
	res = dfs_from_node(ug, 0);
	for(int i = 0; i < ug -> V; i++){
		if(res[i] == 1)
			printf("* %d \n", i);
	}

	printGraph(tg); 
	printf("Targeted node 0 \nImpacted nodes are :- \n");
	res = dfs_from_node(tg, 0);
	for(int i = 0; i < tg -> V; i++){
		if(res[i] == 1)
			printf("* %d \n", i);
	}

	printGraph(ig);
	printf("Targeted node 0 \nImpacted nodes are :- \n");
	res = dfs_from_node(ig, 0);
	for(int i = 0; i < ig -> V; i++){
		if(res[i] == 1)
			printf("* %d \n", i);
	}

	for(int i = 0; i < ug -> V; i++){
		printf("Targeted node %d \nImpacted nodes are :- \n", i);
		res = dfs_from_node(ug, i);
		for(int j = 0; j < ug -> V; j++){
			if(res[j] == 1)
				printf("* %d \n", j);
		}
		free(res);		
	}

/*
	for(int i = 0; i < tg -> V; i++){
		printf("Targeted node %d \nImpacted nodes are :- \n", i);
		res = dfs_from_node(tg, i);
		for(int j = 0; j < tg -> V; j++){
			if(res[j] == 1)
				printf("* %d \n", j);
		}		
		free(res);
	}

	for(int i = 0; i < ig -> V; i++){
		printf("Targeted node %d \nImpacted nodes are :- \n", i);
		res = dfs_from_node(ig, i);
		for(int j = 0; j < ig -> V; j++){
			if(res[j] == 1)
				printf("* %d \n", j);
		}		
		free(res);
	}*/
    return 0;         
} 