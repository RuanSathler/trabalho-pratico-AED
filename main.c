#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int LerInt(){
    int num;

    scanf("%d,", &num);

    return num;
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

void AlocaBombas(int *vet, int qntBomb, int tamanho){
    int cont, locBomb;

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
}

void converteVetParaMat(int **mat, int vet[], int tamanho){
    int contL, contC;

    for(contL=0; contL<tamanho; contL++){
        for(contC=0; contC<tamanho; contC++){
            if(vet[contL * tamanho +contC]==-1) mat[contL][contC] = vet[contL * tamanho +contC];
            else mat[contL][contC] = 0;
        }
    }
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
    int *vet = CriaVetDinamico(tamanho);

    indicemax = tamanho - 1;

    if(tamanho==10) qntBomb = 3;
    else if(tamanho==20) qntBomb = 6;
    else qntBomb = 9;

    *espacosLivresRestantes = (tamanho * tamanho) - qntBomb;

    //coloca tamanho -1 para que ele seja igual ao indice max
    AlocaBombas(vet, qntBomb, tamanho);
    converteVetParaMat(mat, vet, tamanho);

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
    free(vet);
}

void InializaMatFront(int tamanho, int **mat){
    int contL, contC;

    for(contL=0; contL<tamanho; contL++){
        for(contC=0; contC<tamanho; contC++){
            mat[contL][contC] = -1;
        }
    }
}

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

    while(tamanho = LerInt(), tamanho<1 || tamanho>3){
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

        while(coorL=LerInt(), coorC=LerInt(), coorL>tamanho || coorC>tamanho){
            printf("coordena incorreta, tente novamente\n");
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
    }while(espacosLivresRestantes>0);

    if(espacosLivresRestantes==0) printf("parabens, voce he fera\n");


    LiberaMatDinamica(tamanho, matBack);
    LiberaMatDinamica(tamanho, matFront);

    return 0;
}