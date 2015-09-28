#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef int coord;

typedef struct
{
    coord x, y;
}Ponto;

typedef struct
{
    float inclinacao;// o fator a em f(x) = ax + b
    float b;//o fator b em f(x) = ax + b, caso a reta for vertical Ã© o valor de x
    int vertical;//se a reta Ã© paralela ao eixo y ou nao
}Reta;

typedef struct
{
    Ponto a;
    Ponto b;
    Reta reta_aux;//reta que passa por esse lado
}Lado;

typedef struct
{
    Ponto *pontos;
    int num_pontos;
    int num_lados;
    Lado *lados;
}Poligono;

void AdicionaPontos(Poligono*);

Ponto ponto_extremidade(int, Poligono*);

void tracar_lado(Poligono*, Ponto, Ponto ,int);

void tracar_reta(Lado*);

void adicionaLados(Poligono*, int, int);

void printaPoligono(Poligono*);

int acimaOUabaixo(Ponto, Reta);

int ponto_esta_lado(Ponto, Lado);

Ponto Oponto_mais_acimaOUabaixo(Poligono*, Lado*, int);

int ponto_esta_poligono(Poligono*, Ponto);


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
    tracar_lado(poligono, ponto1, ponto2, -1);//TraÃ§a a maior diagonal
    tracar_lado(poligono, ponto2, ponto1, -1);//TraÃ§a a mesma diagonal no sentido contrario
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

//adiciona os pontos ao plano
void AdicionaPontos(Poligono *poligono)
{
    int i;
    poligono->pontos = (Ponto*)malloc(poligono->num_pontos * sizeof(Ponto));
    for(i = 0; i < poligono->num_pontos; i ++)
    {
        scanf("%d %d",&poligono->pontos[i].x,&poligono->pontos[i].y);
    }
    return;
}


//retorna o ponto mais para cima e direita ou o ponto mais para baixo e esquerda
Ponto ponto_extremidade(int sentido, Poligono *poligono)
{
    Ponto aux;
    int max, min, i;
    aux.x = poligono->pontos[0].x;
    aux.y = poligono->pontos[0].y;
    switch(sentido)
    {
        case 1://ponto mais a esquerda e baixo
            min = poligono->pontos[0].x +poligono->pontos[0].y;
            for(i = 0; i < poligono->num_pontos; i ++)
            {

                if(poligono->pontos[i].x + poligono->pontos[i].y < min)
                {
                    min = poligono->pontos[i].x + poligono->pontos[i].y;
                    aux.x = poligono->pontos[i].x;
                    aux.y = poligono->pontos[i].y;
                }
            }
            break;
        case 2://ponto mais a direita e cima
        max = poligono->pontos[0].x + poligono->pontos[0].y;
        for(i = 0; i < poligono->num_pontos; i ++)
        {

            if(poligono->pontos[i].x + poligono->pontos[i].y > max)
            {
                max = poligono->pontos[i].x + poligono->pontos[i].y;
                aux.x = poligono->pontos[i].x;
                aux.y = poligono->pontos[i].y;
            }
        }
            break;
        default:
            break;
    }

    return aux;
}


//traça um lado a partir de dois pontos ou traca dois lados a partir de um lado e um ponto entre eles
void tracar_lado(Poligono *poligono, Ponto ponto1, Ponto ponto2, int indiceLado)
{
    int aux;
    aux = poligono->num_lados;
    poligono->num_lados ++;
    poligono->lados = (Lado*) realloc(poligono->lados, poligono->num_lados * sizeof(Lado));
    if(indiceLado < 0)//caso seja para traçar um lado entre 2 pontos
    {
    poligono->lados[poligono->num_lados-1].a.x = ponto1.x;
    poligono->lados[poligono->num_lados-1].a.y = ponto1.y;
    poligono->lados[poligono->num_lados-1].b.x = ponto2.x;
    poligono->lados[poligono->num_lados-1].b.y = ponto2.y;
    tracar_reta(&(poligono->lados[poligono->num_lados-1]));//traça a reta auxiliar ao novo lado
    }
    else //case seja para traçar dois lados apartir de um ponto e de outro lado
    {

        while(aux > indiceLado)//Passa os outros lados para frente
        {
            aux --;
            poligono->lados[aux+1].a.x = poligono->lados[aux].a.x;
            poligono->lados[aux+1].a.y = poligono->lados[aux].a.y;
            poligono->lados[aux+1].b.x = poligono->lados[aux].b.x;
            poligono->lados[aux+1].b.y = poligono->lados[aux].b.y;
            tracar_reta(&(poligono->lados[aux+1]));//atualiza as retas auxiliares
        }

        poligono->lados[indiceLado+1].a.x = ponto1.x;//Novo lado começa no ponto1
        poligono->lados[indiceLado+1].a.y = ponto1.y;//Novo lado começa no ponto1
        poligono->lados[indiceLado+1].b.x = poligono->lados[indiceLado].b.x;//Novo lado termina onde o antigo terminava
        poligono->lados[indiceLado+1].b.y = poligono->lados[indiceLado].b.y;//Novo lado termina onde o antigo terminava
        tracar_reta(&(poligono->lados[indiceLado+1]));//Define a reta do novo lado
        poligono->lados[indiceLado].b.x = ponto1.x;//Lado antigo termina no ponto1
        poligono->lados[indiceLado].b.y = ponto1.y;//Lado antigo termina no ponto1
        tracar_reta(&(poligono->lados[indiceLado]));//Atualiza a reta auxiliar do lado antigo

    }
    return;
}


//traca uma reta auxiliar a partir de um lado
void tracar_reta(Lado *lado)
{
    float ax1,ax2,ay1,ay2;
    if(lado->a.x == lado->b.x)//reta vertical
    {
        lado->reta_aux.vertical = 1;
        lado->reta_aux.inclinacao = lado->a.x;
        lado->reta_aux.b = 0.0;
    }

    else//reta normal
    {
        ax1 = lado->a.x;
        ax2 = lado->b.x;
        ay1 = lado->a.y;
        ay2 = lado->b.y;

        lado->reta_aux.vertical = 0;
        lado->reta_aux.inclinacao = (ay1 - ay2)/(ax1 - ax2);//define a inclinação
        lado->reta_aux.b = lado->a.y - (lado->a.x * lado->reta_aux.inclinacao);//define o fator b
    }
    return;
}


//mostra os pontos que compõe o poligono
void printaPoligono(Poligono *poligono)
{
    int i;
    for(i = 0; i < poligono->num_lados; i ++)
    {
        printf("\n%d %d",poligono->lados[i].a.x,poligono->lados[i].a.y);
    }
}


//verifica se sao necessarios lados adicionais entre os ja existentes
void adicionaLados(Poligono *poligono, int indiceLado, int quadrante)
{
    int i, fim = 1;
    Ponto P;
    switch(quadrante)
    {
        case 1://lados Para Cima ou esquerda
            P = Oponto_mais_acimaOUabaixo(poligono,&poligono->lados[indiceLado],1);//O ponto mais acima ao lado
            for(i = 0; i < poligono->num_pontos; i ++)
            {
                if(!ponto_esta_lado(P,poligono->lados[indiceLado]))//Se P nao estiver no lado dado
                {
                    if(!ponto_esta_poligono(poligono,P))//Se P nÃ£o estiver no poligono ja
                    {
                        tracar_lado(poligono,P , poligono->pontos[i], indiceLado);//Traça o lado com P
                        fim = 0;//Para chamar novamente a função e verificar se precisa traçar novos lados
                        i = poligono->num_lados;
                    }
                }

                else if(!ponto_esta_lado(poligono->pontos[i],poligono->lados[indiceLado]))//Verifica se o ponto nao esta no lado
                    if(acimaOUabaixo(poligono->pontos[i], poligono->lados[indiceLado].reta_aux) == 1 || acimaOUabaixo(poligono->pontos[i], poligono->lados[indiceLado].reta_aux) == 2)
                    {//Verifica se o ponto esta acima ou a direita do lado
                        if(poligono->lados[indiceLado].reta_aux.inclinacao >= 0)//Verifica se a inclinação da reta e positiva
                        {
                            tracar_lado(poligono,poligono->pontos[i] , poligono->pontos[i], indiceLado);//Traça dois lados a partir do lado anterior e do novo que esta mais externo e entre o lado
                            fim = 0;//Chama a função novamente para verificar se precisa traçar outros lados
                            i = poligono->num_lados;
                        }
                    }
            }
            break;
        case 2://Para Baixo ou direita
            P = Oponto_mais_acimaOUabaixo(poligono,&poligono->lados[indiceLado],-1);//O ponto mais abaixo ao lado dado
            for(i = 0; i < poligono->num_pontos; i ++)
            {
                if(!ponto_esta_lado(P,poligono->lados[indiceLado]))//Se P nao estiver no lado dado
                {
                    if(!ponto_esta_poligono(poligono,P))//Se P nao estiver no poligono ja
                    {
                        tracar_lado(poligono,P , poligono->pontos[i], indiceLado);//Traça o lado com P
                        fim = 0;//Para chamar novamente a função e verificar se precisa traçar novos lados
                        i = poligono->num_lados;
                    }
                }
                else if(!ponto_esta_lado(poligono->pontos[i],poligono->lados[indiceLado]))//Verifica se o ponto nao esta no lado
                    if(acimaOUabaixo(poligono->pontos[i], poligono->lados[indiceLado].reta_aux) == -1 || acimaOUabaixo(poligono->pontos[i], poligono->lados[indiceLado].reta_aux) == -2)
                    {//Verifica se o ponto esta abaixo ou a esquerda do lado
                        if(poligono->lados[indiceLado].reta_aux.inclinacao >= 0)//Verifica se a inclinção da reta e positiva
                        {
                            tracar_lado(poligono,poligono->pontos[i], poligono->pontos[i], indiceLado);//Traça dois lados a partir do lado anterior e do novo que esta mais externo e entre o lado
                            fim = 0;//Chama a função novamente para verificar se precisa traçar outros lados
                            i = poligono->num_lados;
                        }

                    }
            }
            break;
        default:
            break;
    }
    if(!fim)//Como ele adicionou outro lado, agora ele vai verificar se precisa adicionar mais
    {
        adicionaLados(poligono,indiceLado+1, quadrante);
        adicionaLados(poligono,indiceLado  , quadrante);
    }
    else
        return;
}


//retorna 1 se um ponto esta acima de uma reta ou 2 se estiver abaixo
int acimaOUabaixo(Ponto p, Reta r)
{
    float fx, resultado;
    if(r.vertical == 0)//retorna 1 se o ponto esta acima da reta e -1 se estiver abaixo
    {
        fx = p.y;
        resultado =(p.x * r.inclinacao) + r.b;
        if(fx > resultado)
            return 1;
        else
            return -1;
    }
    else// se a reta for vertical retorna 2 se esta a esquerda e -2 se estiver a direita
    {
        if(p.x < r.inclinacao)
            return 2;
        else
            return -2;
    }
}


//retorna 1 se um ponto esta em um lado e 0 se nao esta
int ponto_esta_lado(Ponto p, Lado l)
{
    if((l.a.x == p.x && l.a.y == p.y) || (l.b.x == p.x && l.b.y == p.y))
        return 1;
    else
        return 0;
}


//retorna o ponto mais acima ou mais abaixo de um lado
Ponto Oponto_mais_acimaOUabaixo(Poligono* poligono, Lado *l, int acima_abaixo)
{
    int i;
    Ponto p;
    p.x = l->a.x;
    p.y = l->a.y;

    double d1, d2, dt = 0;
    for(i = 0; i < poligono->num_pontos; i ++)
    {
        if(acima_abaixo == 1)//Se for acima ou direita
        {
            if(acimaOUabaixo(poligono->pontos[i], l->reta_aux) == 1 || acimaOUabaixo(poligono->pontos[i], l->reta_aux) == 2)
            {
                d1 = sqrt(pow(l->a.x- poligono->pontos[i].x,2) +pow(l->a.y-poligono->pontos[i].y,2));
                d2 = sqrt(pow(l->b.x- poligono->pontos[i].x,2) +pow(l->b.y-poligono->pontos[i].y,2));
                if(d1 + d2 > dt && d1 != 0 && d2 != 0)
                {
                    dt =  d1 + d2;
                    p.x = poligono->pontos[i].x;
                    p.y = poligono->pontos[i].y;
                }
            }
        }
        else//Se for abaixo ou esquerda
        {
            if(acimaOUabaixo(poligono->pontos[i], l->reta_aux) == -1 || acimaOUabaixo(poligono->pontos[i], l->reta_aux) == -2)
            {
                d1 = sqrt(pow(l->a.x- poligono->pontos[i].x,2) +pow(l->a.y-poligono->pontos[i].y,2));
                d2 = sqrt(pow(l->b.x- poligono->pontos[i].x,2) +pow(l->b.y-poligono->pontos[i].y,2));
                if(d1 + d2 > dt && d1 != 0 && d2 != 0)
                {
                    dt =  d1 + d2;
                    p.x = poligono->pontos[i].x;
                    p.y = poligono->pontos[i].y;
                }
            }
        }
    }
    return p;
}


//retorna 1 se um ponto ja pertence ao poligono e 0 se nao pertence
int ponto_esta_poligono(Poligono *poligono, Ponto p)
{
    int i;
    for(i = 0; i < poligono->num_lados; i ++)
    {
        if(p.x == poligono->lados[i].a.x && p.y == poligono->lados[i].a.y)
           return 1;
        if(p.x == poligono->lados[i].b.x && p.y == poligono->lados[i].b.y)
           return 1;
    }
    return 0;
}
