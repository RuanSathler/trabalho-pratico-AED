#ifndef REGISTRO_H
#define REGISTRO_H

typedef struct celulaCampoMinado celula;
// CriaArquivo: Função responsável por criar um arquivo para salvar o histórico do jogo.
// O nome do arquivo é gerado com base na data e hora atual, no formato "historico/dd-mm-yy HH-MM".
// Retorna um ponteiro para o arquivo criado. Caso não consiga criar, exibe uma mensagem de erro.
FILE *CriaArquivo();

// SalvaJogada: Função que registra o estado do jogo em um arquivo após cada jogada.
void SalvaJogada(int cooL, int cooC, int espacosRestantes,  celula **mapa, int tamanho, FILE *arquivo);

// SalvaFimJogo: Registra o estado final do jogo no arquivo, incluindo o resultado (vitória ou derrota).
void SalvaFimJogo(int cooL, int cooC, int espacosRestantes, celula **mapa, int tamanho, FILE *arquivo, int vitoria);

// FecharArquivo: Função responsável por fechar o arquivo após o término do jogo ou jogadas.
// Garante que os dados sejam gravados corretamente no arquivo antes de encerrá-lo.
void FecharArquivo(FILE *arquivo);


#endif