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
	Graph* tg = createGraph(i);
	Graph* ug = createGraph(i);
	Graph* ig = createGraph(i);   
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

	printGraph(ug); printGraph(tg); printGraph(ig);


    return 0;         
} 