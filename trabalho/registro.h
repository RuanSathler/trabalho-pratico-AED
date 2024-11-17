#ifndef REGISTRO_H
#define REGISTRO_H

#include <stdio.h>
#include "campoMinado.h"

FILE *CriaArquivo();
void SalvaJogada();
void SalvaFimJogo(int cooL, int cooC, int espacosRestantes, celula **mapa, int tamanho, FILE *arquivo, int vitoria);
void FecharArquivo(FILE *arquivo);


#endif