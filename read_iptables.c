# include <stdio.h> 
# include <string.h> 
int main( ){ 
    FILE *fp ; 
    char dataToBeRead[50]; 
  	char arr[50][50];
 
    fp = fopen("info.txt", "r") ; 

    if ( fp == NULL ) {         
    } 
    else
    {       
        int i = 0;
        while( fgets ( dataToBeRead, 50, fp ) != NULL ){ 
          	strcpy(arr[i], dataToBeRead);
          	i++;
        } 
        fclose(fp); 
   		for(int i = 0; i < 4; i++){
    		printf("%s\n", arr[i]);
   	 	}
   	 	char* tok;
   	 	tok = strtok(arr[0], " ");
   	 	while(tok != NULL){
   	 		printf("%s\n", tok);
   	 		tok = strtok(NULL, " ");
   	 	}

    }  
     
   
    return 0;         
} 