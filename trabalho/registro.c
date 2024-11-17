#include <stdio.h>
#include <time.h>
#include "registro.h"
#include "campoMinado.h"

FILE *CriaArquivo(){
    time_t tempo = time(NULL);
    struct tm dataAtual = *localtime(&tempo);

    char nomeArquivo[100];
    strftime(nomeArquivo, sizeof(nomeArquivo), "historico/%d-%m-%y %H-%M", &dataAtual);

    FILE *arquivo = fopen(nomeArquivo, "w");
    if(arquivo == NULL) printf("Erro ao tentar Criar arquivo, reinicie o programa ou jogue sem salvar");

    return arquivo;
}

void SalvaJogada(int cooL, int cooC, int espacosRestantes,  celula **mapa, int tamanho, FILE *arquivo){
    int contL, contC;

    fprintf(arquivo, "coordenadas escolhidas: %d,%d\n", cooL, cooC);
    fprintf(arquivo, "Espacos Restantes: %d\n", espacosRestantes);

    fprintf(arquivo, "     ");
    for(contC=1; contC<=tamanho; contC++){
        //imprime indice com cor cinza escuro
        fprintf(arquivo, "%.2d ", contC);
    }
    fputc('\n', arquivo);

    for(contL=1; contL<=tamanho; contL++){
        //imprime indice com cor cinza escuro
        fprintf(arquivo,"%.2d - ", contL);
        for(contC=1; contC<=tamanho; contC++){

            //imprime as letras na cor verde
            if(!mapa[contL][contC].estaAberto) fprintf(arquivo,"X  ");
            //imprime as casas proximas a bombas com a cor amarela
            else if(mapa[contL][contC].qntBombaProx>0) fprintf(arquivo, "%d  ", mapa[contL][contC].qntBombaProx);
            //imprime demais cmapos com cor azul
            else fprintf(arquivo, "%d  ", mapa[contL][contC].qntBombaProx);
        }
        fputc('\n', arquivo);
    }

    fputc('\n', arquivo);
}

void SalvaFimJogo(int cooL, int cooC, int espacosRestantes, celula **mapa, int tamanho, FILE *arquivo, int vitoria){
        int contL, contC;

    if(vitoria) fprintf(arquivo, "parabens voce ganhou ao acerta a ultimacelula: %d,%d\n", cooL, cooC);
    else fprintf(arquivo, "voce perdeu, havia uma bomba na celula que vc escolheu: %d,%d\n", cooL, cooC);
    fprintf(arquivo, "Espacos Restantes: %d\n", espacosRestantes);

    fprintf(arquivo, "     ");
    for(contC=1; contC<=tamanho; contC++){
        //imprime indice com cor cinza escuro
        fprintf(arquivo, "%.2d ", contC);
    }
    fputc('\n', arquivo);

        for(contL=1; contL<=tamanho; contL++){
        //imprime indice com cor cinza escuro
        if(mapa[contL][1].bomba==-1) fprintf(arquivo, "%.2d -", contL);
        else fprintf(arquivo, "%.2d - ", contL);

        for(contC=1; contC<=tamanho; contC++){

        //imprime as bombas em vermelho
        if(mapa[contL][contC].bomba==-1 && mapa[contL][contC+1].bomba==-1) fprintf(arquivo, "%d ", mapa[contL][contC].bomba);
        else if(mapa[contL][contC].bomba==-1) fprintf(arquivo, "%d  ", mapa[contL][contC].bomba);
        //imprime as areas proximas as bombas em amarelo
        else if(mapa[contL][contC+1].bomba==-1) fprintf(arquivo, "%d ", mapa[contL][contC].qntBombaProx);
        else if(mapa[contL][contC].qntBombaProx>0) fprintf(arquivo, "%d  ", mapa[contL][contC].qntBombaProx);
        //imprime o restante das celulas em azul
        else fprintf(arquivo, "%d  ", mapa[contL][contC].qntBombaProx);
        }
        fputc('\n', arquivo);
    }
}

void FecharArquivo(FILE *arquivo){
    fclose(arquivo);
}