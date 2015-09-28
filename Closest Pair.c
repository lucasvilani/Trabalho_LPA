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
    int n,i,aux,j=0, *vetor, *dist; 
    scanf("%d",&n);
    vetor = (int*) malloc(n * sizeof(int));
      for(i=0;i<n;i++){                                   //receber os n valores
      	scanf("%d",&vetor[i]);
	  }
	  printf("\n");
	  qsort(vetor, n, sizeof(int), funcaocomparacao);          //ordenação do vetor por quick sort
	  dist = (int*) malloc(n-1 * sizeof(int));
	   for(i=0;i<n-1;i++){
	     dist[i]= vetor[i+1]-vetor[i];                     //acha as distâncias entre os numeros
		 }
	     aux = dist [0];
	    for(i=0;i<n-2;i++){
	    	if(dist[i+1]<aux){							//acha a menor distância
	    		j=i+1;
	    		aux = dist[i+1];
			}
		}
	    
	  printf("%d  %d",vetor[j+1],vetor[j]);
	  free(vetor);
	  vetor = NULL;
	  free(dist);
	  dist = NULL;
	  return 0;
	  system("pause");
	}
    
