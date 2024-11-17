#include <stdio.h>
#include <stdlib.h>
#include "campoMinado.h"
#include "registro.h"

int main(){

    int tamanho, espacosLivresRestantes, coorL = 0, coorC = 0, qntEntrada;
    FILE *registro;
    celula **mapa;

    printf("hola, seja bem-vindo\n");
    printf("qual level deseja jogar?\n");
    printf("1 - Facil\n");
    printf("2 - medio \n");
    printf("3 - dificil\n");

    while((scanf("%d", &tamanho)!=1) || tamanho<1 || tamanho>3){
        while(getchar() != '\n');
        printf("entrada incorreta, por favor insira um level valido\n");
    }
    /*
    tamanho é passado somando dois para resolvemos dois problemas.
    1. as cooerdenadas que agora nao precisam de tratameto porque garatimos que ela terá os indices nescessarios para funcionar
    2. na hora de alocar as bombas não precisamos nos importar com as bordas e afins pq sempre afera um espaço acima e baixo
    */
    registro = CriaArquivo();
    tamanho = tamanho *10;
    mapa = CriaMapa(tamanho+2);
    InializaMapa(tamanho, mapa, &espacosLivresRestantes);

    do{
        ImprimeMapaUsuario(tamanho, mapa);
        SalvaJogada(coorL, coorC, espacosLivresRestantes,  mapa, tamanho, registro);
        printf("digite as coordenadas no padrao: Linha, Coluna\n");

        while(qntEntrada = LerCoordenadas(&coorL, &coorC), coorL>tamanho || coorC>tamanho || coorL<1|| coorC<1){
            if(qntEntrada== -1){
            printf("parece que seu arquivo de entradas acabou, até a procima");
            exit(1);
            }

            printf("coordena fora do tamanho do mapa, tente novamente\n");
        }

        if(mapa[coorL][coorC].bomba==-1){
            printf("game over\n");
            ImprimeBombas(tamanho, mapa);
            SalvaFimJogo(coorL, coorC, espacosLivresRestantes,  mapa, tamanho, registro, 0);
            break;
        }
        else if(mapa[coorL][coorC].estaAberto){
            printf("coordenada ja esta aberta,  insira alguma diferente\n");
            continue;
        }
        else floodfill(mapa, coorL, coorC, tamanho, &espacosLivresRestantes);
        
        //descomentar a linha abaixo caso queria que o terminal seja limpo depois de cada rodada
        //Windows
        //system("cls");
        //linux
        //system("clear");
    }while(espacosLivresRestantes>0);

    if(espacosLivresRestantes==0){
        ImprimeBombas(tamanho, mapa);
        SalvaFimJogo(coorL, coorC, espacosLivresRestantes,  mapa, tamanho, registro, 1);
        printf("parabens, voce he fera\n");
    }

    FecharArquivo(registro);
    LiberaMapa(tamanho, mapa);
    return 0;
}
