#include "plano_convexo.h"

int main(void)
{
    Poligono *poligono;
    Ponto ponto1, ponto2, ponto3, ponto4;
    int i;

    poligono = (Poligono*) malloc(sizeof(Poligono));
    poligono->lados = NULL;
    poligono->num_lados = 0;

    scanf("%d",&poligono->num_pontos);

    AdicionaPontos(poligono);
    ponto1 = ponto_extremidade(1, poligono);//encontra o ponto mais para esquerda e baixo
    ponto2 = ponto_extremidade(2, poligono);//encontra o ponto mais para direita e cima
    tracar_lado(poligono, ponto1, ponto2, -1);//Traça a maior diagonal
    tracar_lado(poligono, ponto2, ponto1, -1);//Traça a mesma diagonal no sentido contrario
    if(!ponto_esta_lado(Oponto_mais_acimaOUabaixo(poligono,&poligono->lados[0],1),poligono->lados[0]))//Se possui um ponto acima da maior diagonal
    {
        ponto3 = Oponto_mais_acimaOUabaixo(poligono,&poligono->lados[0],1);
        tracar_lado(poligono, ponto3, ponto3, 0);//Traça dois lados apartir da diagonal e do ponto mais acima
        adicionaLados(poligono, 1, 1);
    }
    if(!ponto_esta_lado(Oponto_mais_acimaOUabaixo(poligono,&poligono->lados[1],-1),poligono->lados[1]))//Se posuui um ponto abaixo da maior diagonal
    {
       ponto4 = Oponto_mais_acimaOUabaixo(poligono,&poligono->lados[0],-1);
       tracar_lado(poligono, ponto4, ponto3, poligono->num_lados-1);//Traça dois lados apartir da diagonal com o ponto mais abaixo
       adicionaLados(poligono, poligono->num_lados-2, 2);
    }

    adicionaLados(poligono, 0, 1);//Adiciona lados extras para cima da reta
    adicionaLados(poligono, poligono->num_lados-1, 2);//Adiciona lados extras para baixo da reta
    i = 0;
    while(i < poligono->num_lados)//Confirma que não sobraram pontos externos ao poligono
    {
        adicionaLados(poligono, i, 1);
        i++;
    }
    printaPoligono(poligono);//Mostra a saida

    free(poligono->pontos);
    free(poligono->lados);
    poligono->pontos = NULL;
    poligono->lados = NULL;
    free(poligono);
    poligono = NULL;

    return 0;
}
