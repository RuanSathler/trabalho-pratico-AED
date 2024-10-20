#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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


int *CriaVetDinamico(int tamanho){
    int *vet = (int*)malloc((tamanho * tamanho)* sizeof(int));

    if(vet==NULL){ printf("memoria insuficiente"); exit(1);}

    return vet;
}

int **CriaMatDinamica(int tamanho){
    int cont;
    int **mat = (int **)malloc(tamanho * sizeof(int *));

    if(mat==NULL){ printf("memoria insuficiente"); exit(1);}

    for(cont=0; cont<tamanho; cont++){
        mat[cont] = (int *)malloc(tamanho * sizeof(int));
        if(mat[cont]==NULL){ printf("memoria insuficiente"); exit(1);}
    }

    return mat;
}


//aqui o verto um vetor carregando a localizacao das bombas é convertido para a matriz original e onde não houver bomba é colocado um zero
void converteVetParaMat(int **mat, int vet[], int tamanho){
    int contL, contC;

    for(contL=0; contL<tamanho; contL++){
        for(contC=0; contC<tamanho; contC++){
            if(vet[contL * tamanho +contC]==-1) mat[contL][contC] = vet[contL * tamanho +contC];
            else mat[contL][contC] = 0;
        }
    }
}

//cria um vetor com o mesmmo tamanho da matriz e coloca as bombas dentro dele
void AlocaBombasEZeros(int qntBomb, int tamanho, int **mat){
    int cont, locBomb;
    int *vet = CriaVetDinamico(tamanho);

    srand(time(0));

    for(cont=0; cont<qntBomb;){
        locBomb = rand() % (tamanho * tamanho);

        if(vet[locBomb]==-1){
            continue;
        }
        else{
            vet[locBomb]=-1;
            cont++;
        }
    }
    converteVetParaMat(mat, vet, tamanho);
    free(vet);
}

//funcao auxiliar para inicalizar os 8 quadrados em volta da bomba(nao funciona em quadrados que estejam na borda)
void mapearAreaProximaBomba(int **mat, int locLinha, int locColuna){
    int contC, contL;

    for(contL=locLinha-1; contL<=locLinha+1; contL++){
        for(contC=locColuna-1; contC<=locColuna+1; contC++){
            if(contL==locLinha && contC==locColuna) continue;

            if(mat[contL][contC]!=-1) mat[contL][contC] += 1;
        }
    }

}

void InializaMatBack(int tamanho, int **mat, int *espacosLivresRestantes){
    int qntBomb, contC, contL, indicemax;

    indicemax = tamanho - 1;

    if(tamanho==10) qntBomb = 3;
    else if(tamanho==20) qntBomb = 6;
    else qntBomb = 9;

    *espacosLivresRestantes = (tamanho * tamanho) - qntBomb;

    //coloca tamanho -1 para que ele seja igual ao indice max
    AlocaBombasEZeros(qntBomb, tamanho, mat);

    //comeca verificanto se tem bomba em algum dos cantos
    //borda superior esquerda
    if(mat[0][0]==-1){
        if(mat[0][1]!=-1) mat[0][1] += 1;
        if(mat[1][0]!=-1) mat[1][0] += 1;
        if(mat[1][1]!=-1) mat[1][1] += 1;
    }
    //borda superior direira
    if(mat[0][indicemax]==-1){
        if(mat[0][indicemax-1]!=-1) mat[0][indicemax-1] += 1;
        if(mat[1][indicemax-1]!=-1) mat[1][indicemax-1] += 1;
        if(mat[1][indicemax]!=-1) mat[1][indicemax] += 1;
    }
    //borda inferior esquerda
    if(mat[indicemax][0]==-1){
        if(mat[indicemax][1]!=-1) mat[indicemax][1] += 1;
        if(mat[indicemax-1][0]!=-1) mat[indicemax-1][0] += 1;
        if(mat[indicemax-1][1]!=-1) mat[indicemax-1][1] += 1;
    }
    //borda inferior direira
    if(mat[indicemax][indicemax]==-1){
        if(mat[indicemax-1][indicemax]!=-1) mat[indicemax-1][indicemax] += 1;
        if(mat[indicemax][indicemax-1]!=-1) mat[indicemax][indicemax-1] += 1;
        if(mat[indicemax-1][indicemax-1]!=-1) mat[indicemax-1][indicemax-1] += 1;
    }

    //verifica a primeira e ultima linha em busca de bombas
    for(contL=0; contL<tamanho;){
        for (contC=1; contC<indicemax; contC++){
            
            //inializando a primeira linha
            if(contL==0 && mat[contL][contC]==-1){
                if(mat[contL][contC-1]!=-1) mat[contL][contC-1] += 1;
                if(mat[contL][contC+1]!=-1) mat[contL][contC+1] += 1;
                if(mat[contL+1][contC-1]!=-1) mat[contL+1][contC-1] += 1;
                if(mat[contL+1][contC]!=-1) mat[contL+1][contC] += 1;
                if(mat[contL+1][contC+1]!=-1) mat[contL+1][contC+1] += 1;


            }
            //inicializando a ultima linha
            else if(mat[contL][contC]==-1){
                if(mat[contL][contC-1]!=-1) mat[contL][contC-1] += 1;
                if(mat[contL][contC+1]!=-1) mat[contL][contC+1] += 1;
                if(mat[contL-1][contC-1]!=-1) mat[contL-1][contC-1] += 1;
                if(mat[contL-1][contC]!=-1) mat[contL-1][contC] += 1;
                if(mat[contL-1][contC+1]!=-1) mat[contL-1][contC+1] += 1;
            }        
        }

        contL += indicemax;      
    }
    //verifica a primeira e ultima coluna em busca de bombas
    for(contL=1; contL<indicemax;contL++){
        for (contC=0; contC<tamanho;){
            
            //inializando a coluna direita
            if(contC==0 && mat[contL][contC]==-1){
                if(mat[contL][contC+1]!=-1) mat[contL][contC+1] += 1;
                if(mat[contL-1][contC+1]!=-1) mat[contL-1][contC+1] += 1;
                if(mat[contL-1][contC]!=-1) mat[contL-1][contC] += 1;
                if(mat[contL+1][contC]!=-1) mat[contL+1][contC] += 1;
                if(mat[contL+1][contC+1]!=-1) mat[contL+1][contC+1] += 1;


            }
            //inicializando a coluna esquerda
            else if(mat[contL][contC]==-1){
                if(mat[contL][contC-1]!=-1) mat[contL][contC-1] += 1;
                if(mat[contL-1][contC]!=-1) mat[contL-1][contC] += 1;
                if(mat[contL-1][contC-1]!=-1) mat[contL-1][contC-1] += 1;
                if(mat[contL+1][contC]!=-1) mat[contL+1][contC] += 1;
                if(mat[contL+1][contC-1]!=-1) mat[contL+1][contC-1] += 1;
            }
            contC += indicemax;        
        }     
    }

    //inicializa o restante da matriz
    for(contL=1; contL<indicemax; contL++){
        for(contC=1; contC<indicemax; contC++){
            if(mat[contL][contC]==-1) mapearAreaProximaBomba(mat, contL, contC);
        }
    }
}

//inicializa matriz que será mostrada para o o usuário, iniciada com -1, o que indica que nehum dos seus numeros foi clicado
void InializaMatFront(int tamanho, int **mat){
    int contL, contC;

    for(contL=0; contL<tamanho; contL++){
        for(contC=0; contC<tamanho; contC++){
            mat[contL][contC] = -1;
        }
    }
}

/*imprime a matriz do usuario e se algum dos suas cas tiver sido clicada, ou seja se seu valor for -1 imprime 
a casa corespondente na matriz que carrega as bombas*/

void ImprimeMatFront(int tamanho, int **mat){
    int contL, contC;

    printf("     ");
    for(contC=0; contC<tamanho; contC++){
        printf("%.2d ", contC+1);
    }

    putchar('\n');

    for(contL=0; contL<tamanho; contL++){
        printf("%.2d - ", contL+1);
        for(contC=0; contC<tamanho; contC++){
            if(mat[contL][contC]==-1) printf("X  ");
            else printf("%d  ", mat[contL][contC]);
        }
        putchar('\n');
    }
}

// imprime a matriz que carrega as bombas, é usada caro queria ver algum possivel erro ou se o usuario tiver perdido o jogo
void ImprimeMatBack(int tamanho, int **mat){
    int contL, contC;

    printf("     ");
    for(contC=0; contC<tamanho; contC++){
        printf("%.2d ", contC+1);
    }

    putchar('\n');

    for(contL=0; contL<tamanho; contL++){
        if(mat[contL][0]==-1) printf("%.2d -", contL+1);
        else printf("%.2d - ", contL+1);

        for(contC=0; contC<tamanho; contC++){
        if(mat[contL][contC+1]==-1)printf("%d ", mat[contL][contC]);
        else printf("%d  ", mat[contL][contC]);
        }
        putchar('\n');
    }
}

void LiberaMatDinamica(int tamanho, int **mat){
  int cont;

  for(cont=0; cont<tamanho; cont++){
    free(mat[cont]);
  }

  free(mat);
}

int main(){

    int tamanho, **matBack, **matFront, espacosLivresRestantes, coorL, coorC;

    printf("hola, seja bem-vindo\n");
    printf("qual level deseja jogar?\n");
    printf("1 - Facil\n");
    printf("2 - medio \n");
    printf("3 - dificil\n");

    while((scanf("%d", &tamanho)!=1) || tamanho<1 || tamanho>3){
        while(getchar() != '\n');
        printf("entrada incorreta, por favor insira um level valido\n");
    }

    tamanho = tamanho *10;

    matBack = CriaMatDinamica(tamanho);
    matFront = CriaMatDinamica(tamanho);

    InializaMatBack(tamanho, matBack, &espacosLivresRestantes);
    InializaMatFront(tamanho, matFront);    

   do{
        ImprimeMatFront(tamanho, matFront);
        printf("digite as coordenadas no padrao: Linha, Coluna\n");

        while(LerCoordenadas(&coorL, &coorC), coorL>tamanho || coorC>tamanho || coorL<1|| coorC<1){
            printf("coordena maior que o tamanho do mapa, tente novamente\n");
        }

        coorL -= 1;
        coorC -= 1;

        if(matBack[coorL][coorC]==-1){
            printf("voce perdeu\n");
            ImprimeMatBack(tamanho, matBack);
            break;
        }
        else if(matFront[coorL][coorC]==0 || matFront[coorL][coorC]==1){
            printf("coordenada repetida, insira alguma diferente\n");
            continue;
        }
        else matFront[coorL][coorC] = matBack[coorL][coorC];

        espacosLivresRestantes--;
        
        //descomentar a linha abaixo caso queria que o terminal seja limpo depois de cada rodada
        //Windows
        //system("cls");
        //linux
        //system("clear");
    }while(espacosLivresRestantes>0);

    if(espacosLivresRestantes==0){
        ImprimeMatBack(tamanho, matBack);
        printf("parabens, voce he fera\n");
    }


    LiberaMatDinamica(tamanho, matBack);
    LiberaMatDinamica(tamanho, matFront);

    return 0;
}