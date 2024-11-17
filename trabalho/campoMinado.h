#ifndef CAMPO_MINADO_H
#define CAMPO_MINADO_H

//o mapa do campo minado será uma matriz de celulas, onde cada celula tem as informaçoes abaixo
//qntBomba receb 0 ou 1, onde 0 é falso e quer dizer que não há bomba e 1 quer dizer que há uma bomba
typedef struct celulaCampoMinado{
    int bomba;
    int qntBombaProx;
    int estaAberto;
}celula;


//ler as coordenadas e garante que sejam entradas validas, são consideradas entradas validas dois numeros na mesmda linhas,
//sejam separados por ponto, virgula ou espaço além disso ela verica se a entrada é EOF
int LerCoordenadas(int *linha, int *coluna);

//cria o mapa e coloca 0 em todas os atributos das celulas do mapa
celula **CriaMapa(int tamanho);

//cola as bombas aleatoriamente dentro da matriz, funciona sorteando um numero aleatorio para a linha e outro para coluna
//entao repete o processo até colocar o numero de bombas nescessarias
void AlocaBombasEZeros(int qntBomb, int tamanho, celula **mapa);

// Atualiza os contadores de bombas nas células próximas a uma bomba.
// Recebe o mapa e a localização da bomba (linha e coluna).
void mapearAreaProximaBomba(celula **mapa, int locLinha, int locColuna);

// Inicializa o mapa com células vazias e distribui bombas aleatoriamente.
// Define o total de espaços livres no mapa.
void InializaMapa(int tamanho, celula **mapa, int *espacosLivresRestantes);

// Mostra o mapa para o jogador com células abertas ou marcadas.
// Esconde bombas e informações não reveladas.
void ImprimeMapaUsuario(int tamanho, celula **mapa);

// Exibe o mapa completo com a localização de todas as bombas.
// Usada geralmente ao final do jogo ou caso se queira verificar algum erro
void ImprimeBombas(int tamanho, celula **mapa);

// Libera a memória alocada para o mapa do jogo.
// Evita vazamentos de memória após o término do jogo.
void LiberaMapa(int tamanho, celula **mat);

void floodfill(celula **mapa, int linha, int coluna, int tamanho, int *espacoeslivres);

#endif