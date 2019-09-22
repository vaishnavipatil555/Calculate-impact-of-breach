# include <stdio.h> 
# include <stdlib.h>
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
	
	int *res;

	//printf("UDP\n");
	//FILE *fp1 = fopen("impact_udp.txt", "wb");
	printf("\n");
	//printGraph(ug);

	printf("\n kuashdkua \n");
	 
	for(int i = 0; i < ug -> V; i++){
		//printf("Targeted node %d \nImpacted nodes are :- \n", i);
		res = dfs_from_node(ug, i);
		int j;
		for(j = 0; j < ug -> V; j++){
			if(res[j] == 1){
				printf("%d ", j);
				//fwrite(&j, sizeof(int), 1,fp1);
				//fprintf(fp1, "rr ");
			}
		}
		printf("%d \n", j);
				
		free(res);		
	}
	//fclose(fp1);
	//printf("*******************************************************************************************\n");
	
	printf("\n kuashdkua \n");
	

	printf("\n");
	//printGraph(tg); 
	for(int i = 0; i < tg -> V; i++){
		//printf("Targeted node %d \nImpacted nodes are :- \n", i);
		res = dfs_from_node(tg, i);
		for(int j = 0; j < tg -> V; j++){
			if(res[j] == 1)
				printf("%d ", j);
		}
		printf("\n");
		free(res);		
	}
	//printf("*******************************************************************************************\n");

	
	printf("\n");
	//printGraph(ig);
	for(int i = 0; i < ig -> V; i++){
		//printf("Targeted node %d \nImpacted nodes are :- \n", i);
		res = dfs_from_node(ig, i);
		for(int j = 0; j < ig -> V; j++){
			if(res[j] == 1)
				printf("%d ", j);
		}
		printf("\n");		
		free(res);
	}
	//printf("*******************************************************************************************\n");

    return 0;         
} 