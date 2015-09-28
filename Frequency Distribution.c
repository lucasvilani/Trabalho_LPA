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
     int i,n,x=0, *vetor, *vetor_rep, diferentes = 1, cont = 0, j, aux;
     scanf("%d",&n);
    vetor = (int*) malloc (n * sizeof(int));
      for(i=0;i<n;i++){                                  
      	scanf("%d",&vetor[i]);
	  }
	 printf("\n"); 
	  qsort(vetor, n, sizeof(int), funcaocomparacao);          //ordenação do vetor por quick sort
	  x = vetor[0];
	  for(i = 0; i < n; i ++)					//conta o número de números diferentes no vetor
	  {
	  	if(x != vetor[i])
	  	{
	  		diferentes ++;
			x = vetor[i];	
	    }	
	  }
    vetor_rep = (int*) calloc (diferentes, sizeof(int));
	  cont  = 0;
	x = vetor[0];
	for(i = 0; i < n; i ++)				//conta quantas vezes cada número se repete
	{
		if(x == vetor[i])
		{
			vetor_rep[cont] ++;
			
		}
		else
		{
			cont ++;
			x = vetor[i];
			vetor_rep[cont]++;
		}
		
	}
	x = vetor_rep[0];
	  for(i=0;i<diferentes;i++){       //pega o maior número de repetições
		  	 if(vetor_rep[i] > x)
		  	 	x = vetor_rep[i];
	  		
		  }
	  
		 
	for(i = 0; i < diferentes; i ++)								//mostra os números que mais se repetiram
	{
		if(x == vetor_rep[i])
		{
			aux = vetor[0];
			cont = 0;
			
			for(j = 0; j < n; j ++)
			{
				if(cont == i)
				{
					printf("%d ",vetor[j]);
					j = n;
				}
				else if(aux != vetor[j])
				{
					cont++;
					aux = vetor[j];
				}
			}
		}
	}
	  	
	   
	   free(vetor_rep);
	   free(vetor);
	   vetor = NULL;
	   vetor_rep = NULL;
}
