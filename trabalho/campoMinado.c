#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "campoMinado.h"


int LerCoordenadas(int *linha, int *coluna) {
    int valor;
    while (valor=scanf("%d%*[ ,.]%d", linha, coluna), valor!= 2 && valor != -1){

        // Entrada inválida, solicitar novamente
        printf("Entrada invalida! Tente novamente no formato: Linha, Coluna (exemplo: 4,2)\n");
        // Limpar o buffer de entrada
        while (getchar() != '\n');
    }

    return valor;
}

celula **CriaMapa(int tamanho){
    int contL, contC;
    celula **mat = (celula **)malloc(tamanho * sizeof(*mat));

    if(mat==NULL){ printf("memoria insuficiente"); exit(1);}

    for(contL=0; contL<tamanho; contL++){
        mat[contL] = (celula *)malloc(tamanho * sizeof(celula));
        if(mat[contL]==NULL){ printf("memoria insuficiente"); exit(1);}
    }

    for(contL=0; contL<tamanho; contL++){
        for(contC=0; contC<tamanho; contC++){
            mat[contL][contC].bomba = 0;
            mat[contL][contC].qntBombaProx = 0;
            mat[contL][contC].estaAberto = 0;
        }
    }

    return mat;
}

void AlocaBombas(int qntBomb, int tamanho, celula **mapa){
    int cont, contC, contL;

    srand(time(0));

    for(cont=0; cont<qntBomb;){
        contL = rand() % (tamanho) + 1;
        contC = rand() % (tamanho) + 1;

        if(mapa[contL][contC].bomba==-1){
            continue;
        }
        else{
            mapa[contL][contC].bomba=-1;
            cont++;
        }
    }
}

void mapearAreaProximaBomba(celula **mapa, int locLinha, int locColuna){
    int contC, contL;

    for(contL=locLinha-1; contL<=locLinha+1; contL++){
        for(contC=locColuna-1; contC<=locColuna+1; contC++){
            if(contL==locLinha && contC==locColuna) continue;

            if(mapa[contL][contC].bomba!=-1) mapa[contL][contC].qntBombaProx += 1;
        }
    }

}

void InializaMapa(int tamanho, celula **mapa, int *espacosLivresRestantes){
    int qntBomb, contC, contL;

    if(tamanho==10) qntBomb = 15;
    else if(tamanho==20) qntBomb = 60;
    else qntBomb = 135;

    *espacosLivresRestantes = (tamanho * tamanho) - qntBomb;

    AlocaBombas(qntBomb, tamanho, mapa);

    //inicializa o restante da matriz
    for(contL=1; contL<=tamanho; contL++){
        for(contC=1; contC<=tamanho; contC++){
            if(mapa[contL][contC].bomba==-1) mapearAreaProximaBomba(mapa, contL, contC);
        }
    }
}

void ImprimeMapaUsuario(int tamanho, celula **mapa){
    int contL, contC;

    printf("     ");
    for(contC=1; contC<=tamanho; contC++){
        //imprime indice com cor cinza escuro
        printf("\033[90m%.2d \033[0m", contC);
    }

    putchar('\n');

    for(contL=1; contL<=tamanho; contL++){
        //imprime indice com cor cinza escuro
        printf("\033[90m%.2d - \033[0m", contL);
        for(contC=1; contC<=tamanho; contC++){

            //imprime as letras na cor verde
            if(!mapa[contL][contC].estaAberto) printf("\033[32mX  \033[0m");
            //imprime as casas proximas a bombas com a cor amarela
            else if(mapa[contL][contC].qntBombaProx>0) printf("\033[33m%d  \033[0m", mapa[contL][contC].qntBombaProx);
            //imprime demais cmapos com cor azul
            else printf("\033[34m%d  \033[0m", mapa[contL][contC].qntBombaProx);
        }
        putchar('\n');
    }
}

void ImprimeBombas(int tamanho, celula **mapa){
    int contL, contC;

    printf("     ");
    for(contC=1; contC<=tamanho; contC++){
        //imprime indice com cor cinza escuro
        printf("\033[90m%.2d \033[0m", contC);
    }

    putchar('\n');

    for(contL=1; contL<=tamanho; contL++){
        //imprime indice com cor cinza escuro
        if(mapa[contL][1].bomba==-1) printf("\033[90m%.2d -\033[0m", contL);
        else printf("\033[90m%.2d - \033[0m", contL);

        for(contC=1; contC<=tamanho; contC++){

        //imprime as bombas em vermelho
        if(mapa[contL][contC].bomba==-1 && mapa[contL][contC+1].bomba==-1) printf("\033[31m%d \033[0m", mapa[contL][contC].bomba);
        else if(mapa[contL][contC].bomba==-1)printf("\033[31m%d  \033[0m", mapa[contL][contC].bomba);
        //imprime as areas proximas as bombas em amarelo
        else if(mapa[contL][contC+1].bomba==-1) printf("\033[33m%d \033[0m", mapa[contL][contC].qntBombaProx);
        else if(mapa[contL][contC].qntBombaProx>0) printf("\033[33m%d  \033[0m", mapa[contL][contC].qntBombaProx);
        //imprime o restante das celulas em azul
        else printf("\033[34m%d  \033[0m", mapa[contL][contC].qntBombaProx);
        }
        putchar('\n');
    }
}

void LiberaMapa(int tamanho, celula **mat){
  int cont;

  for(cont=0; cont<tamanho; cont++){
    free(mat[cont]);
  }

  free(mat);
}

void floodfill(celula **mapa, int linha, int coluna, int tamanho, int *espacoeslivres){
    int contC, contL;

    // Condições de parada
    if (linha < 1 || linha > tamanho || coluna < 1 || coluna > tamanho || mapa[linha][coluna].estaAberto)
        return;
    
    if (mapa[linha][coluna].qntBombaProx > 0) {
        mapa[linha][coluna].estaAberto = 1;
        (*espacoeslivres)--;
        return;
    }
    
    if (mapa[linha][coluna].bomba == -1) return;

    // Marca a célula como aberta
    mapa[linha][coluna].estaAberto = 1;
    (*espacoeslivres)--;

    for (contL = linha - 1; contL <= linha + 1; contL++) {
        for (contC = coluna - 1; contC <= coluna + 1; contC++) {
            if (contL < 1 || contL > tamanho || contC < 1 || contC > tamanho || (contL == linha && contC == coluna))
                continue;

            floodfill(mapa, contL, contC, tamanho, espacoeslivres);
        }
    }
}