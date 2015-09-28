#include<stdio.h>
#include<stdlib.h>

int funcaocomparacao( const void * x, const void * y){
    if (*(int*)x == *(int*)y)
        return 0;//iguais
    else
        if(*(int*)x < *(int*)y)
            return -1;//vem antes
        else
            return 1;//vem depois
    }
    
    int main(){
     int i,n, *vetor;
     scanf("%d",&n);
     vetor = (int*) malloc (n * sizeof(int));
      for(i=0;i<n;i++){                                   
      	scanf("%d",&vetor[i]);
	  }
	  printf("\n");
	  qsort(vetor, n, sizeof(int), funcaocomparacao);          //ordenação do vetor por quick sort
	  
	for(i=1;i<n;i++){                                           
		if(vetor[i]!=vetor[i+1] && vetor[i]!= vetor[i-1])			//acha o elemento que ocorre apenas uma vez
		printf(" %d \n",vetor[i]);
		
		}
	
		free(vetor);
		vetor = NULL;
	  return 0;
	  system("pause");
	}
