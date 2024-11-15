#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//o mapa do campo minado será uma matriz de celulas, onde cada celula tem as informaçoes abaixo
//qntBomba receb 0 ou 1, onde 0 é falso e quer dizer que não há bomba e 1 quer dizer que há uma bomba
typedef struct celulaCampoMinado{
    int bomba;
    int qntBombaProx;
    int estaAberto;
}celula;


//ler as coordenadas e garante que sejam entradas validas, são consideradas entradas validas dois numeros na mesmda linhas,
//sejam separados por ponto, virgula ou espaço
void LerCoordenadas(int *linha, int *coluna) {
    while (scanf("%d%*[ ,.]%d", linha, coluna) != 2) {
        // Entrada inválida, solicitar novamente
        printf("Entrada invalida! Tente novamente no formato: Linha, Coluna (exemplo: 4,2)\n");
        // Limpar o buffer de entrada
        while (getchar() != '\n');
    }
}

//cria o mapa e coloca 0 em todas os atributos das celulas do mapa
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

//cria um vetor com o mesmmo tamanho da matriz e coloca as bombas dentro dele
void AlocaBombasEZeros(int qntBomb, int tamanho, celula **mapa){
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

//funcao auxiliar para inicalizar os 8 quadrados em volta da bomba(nao funciona em quadrados que estejam na borda)
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

    if(tamanho==10) qntBomb = 3;
    else if(tamanho==20) qntBomb = 6;
    else qntBomb = 9;

    *espacosLivresRestantes = (tamanho * tamanho) - qntBomb;

    AlocaBombasEZeros(qntBomb, tamanho, mapa);

    //inicializa o restante da matriz
    for(contL=1; contL<=tamanho; contL++){
        for(contC=1; contC<=tamanho; contC++){
            if(mapa[contL][contC].bomba==-1) mapearAreaProximaBomba(mapa, contL, contC);
        }
    }
}

/*imprime a matriz do usuario e se algum dos suas casas tiver sido clicada, ou seja se seu valor for -1 imprime 
a casa corespondente na matriz que carrega as bombas*/

void ImprimeMapaUsuario(int tamanho, celula **mapa){
    int contL, contC;

    printf("     ");
    for(contC=1; contC<=tamanho; contC++){
        printf("%.2d ", contC);
    }

    putchar('\n');

    for(contL=1; contL<=tamanho; contL++){
        printf("%.2d - ", contL);
        for(contC=1; contC<=tamanho; contC++){
            if(!mapa[contL][contC].estaAberto) printf("X  ");
            else printf("%d  ", mapa[contL][contC].qntBombaProx);
        }
        putchar('\n');
    }
}

// imprime todos os espaços da matriz, é usada caro queria ver algum possivel erro ou se o usuario tiver perdido o jogo
void ImprimeBombas(int tamanho, celula **mapa){
    int contL, contC;

    printf("     ");
    for(contC=1; contC<=tamanho; contC++){
        printf("%.2d ", contC);
    }

    putchar('\n');

    for(contL=1; contL<=tamanho; contL++){
        if(mapa[contL][1].bomba==-1) printf("%.2d -", contL);
        else printf("%.2d - ", contL);

        for(contC=1; contC<=tamanho; contC++){
        if(mapa[contL][contC].bomba==-1)printf("%d ", mapa[contL][contC].bomba);
        else printf("%d  ", mapa[contL][contC].qntBombaProx);
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