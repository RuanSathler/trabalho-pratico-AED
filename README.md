# Campo Minado

Trabalho prático solicitado pelo professor Juan na matéria de AED-I
local : ICOMP - UFAM;

este trabalho tempo objetivo fazer uma emulação do jogo campo Minado usando alocação dinâmica de memória, além de exercitar boas práticas relacionadas a manipulação de memória.

## Descrição Geral
Este programa é um jogo de lógica inspirado no "Campo Minado". O jogador escolhe um nível de dificuldade e clica em células de uma grade, tentando evitar as bombas. O jogo tem uma interface simples no terminal e usa alocação dinâmica de memória para gerenciar a grade do jogo.

## Estruturas do Programa

### Funções

- `void LerCoordenadas(int *linha, int *coluna)`
  - **Descrição:** Lê as coordenadas digitadas pelo jogador, garantindo que sejam números válidos.
  - **Parâmetros:**
    - `int *linha`: Ponteiro para guardar a linha digitada.
    - `int *coluna`: Ponteiro para guardar a coluna digitada.
  - **Validação:** Aceita entradas separadas por espaço, vírgula ou ponto. Se a entrada não for válida, pede para tentar novamente.

- `int *CriaVetDinamico(int tamanho)`
  - **Descrição:** Cria um vetor de inteiros com tamanho `tamanho * tamanho`.
  - **Parâmetros:**
    - `int tamanho`: Tamanho do vetor que será criado.
  - **Retorno:** Retorna um ponteiro para o vetor criado ou encerra o programa com uma mensagem de erro se não conseguir alocar.

- `int **CriaMatDinamica(int tamanho)`
  - **Descrição:** Cria uma matriz de inteiros com dimensões `tamanho x tamanho`.
  - **Parâmetros:**
    - `int tamanho`: Tamanho da matriz que será criada.
  - **Retorno:** Retorna um ponteiro para a matriz criada ou encerra o programa com uma mensagem de erro se não conseguir alocar.

- `void converteVetParaMat(int **mat, int vet[], int tamanho)`
  - **Descrição:** Converte um vetor que contém as posições das bombas em uma matriz, colocando zeros nas células sem bomba.
  - **Parâmetros:**
    - `int **mat`: Matriz onde as bombas e os zeros serão armazenados.
    - `int vet[]`: Vetor que contém a posição das bombas.
    - `int tamanho`: Tamanho da matriz.

- `void AlocaBombasEZeros(int qntBomb, int tamanho, int **mat)`
  - **Descrição:** Coloca as bombas e zera as células da matriz, distribuindo as bombas de forma aleatória.
  - **Parâmetros:**
    - `int qntBomb`: Número de bombas a serem colocadas.
    - `int tamanho`: Tamanho da matriz.
    - `int **mat`: Matriz onde as bombas serão colocadas.

- `void mapearAreaProximaBomba(int **mat, int locLinha, int locColuna)`
  - **Descrição:** Marca as células ao redor de uma bomba, contando quantas bombas estão próximas.
  - **Parâmetros:**
    - `int **mat`: Matriz onde as bombas e os contadores serão armazenados.
    - `int locLinha`: Linha onde a bomba está.
    - `int locColuna`: Coluna onde a bomba está.

- `void InializaMatBack(int tamanho, int **mat, int *espacosLivresRestantes)`
  - **Descrição:** Prepara a matriz que guarda as bombas e conta quantos espaços livres ainda existem.
  - **Parâmetros:**
    - `int tamanho`: Tamanho da matriz.
    - `int **mat`: Matriz onde as bombas serão armazenadas.
    - `int *espacosLivresRestantes`: Ponteiro para guardar o número de espaços livres.

- `void InializaMatFront(int tamanho, int **mat)`
  - **Descrição:** Prepara a matriz que será mostrada para o jogador, preenchendo com -1 (representa que nenhuma célula foi clicada).
  - **Parâmetros:**
    - `int tamanho`: Tamanho da matriz.
    - `int **mat`: Matriz que será mostrada ao jogador.

- `void ImprimeMatFront(int tamanho, int **mat)`
  - **Descrição:** Mostra a matriz que está visível para o jogador.
  - **Parâmetros:**
    - `int tamanho`: Tamanho da matriz.
    - `int **mat`: Matriz que será mostrada.

- `void ImprimeMatBack(int tamanho, int **mat)`
  - **Descrição:** Mostra a matriz que contém a localização das bombas, usada quando o jogador perde, ou quando o jogo termina.
  - **Parâmetros:**
    - `int tamanho`: Tamanho da matriz.
    - `int **mat`: Matriz que contém as bombas.

- `void LiberaMatDinamica(int tamanho, int **mat)`
  - **Descrição:** Libera a memória usada pela matriz.
  - **Parâmetros:**
    - `int tamanho`: Tamanho da matriz.
    - `int **mat`: Matriz que será liberada.

### Função Principal

- `int main()`
  - **Descrição:** A função principal que controla como o jogo funciona.
  - **Processo:**
    - Pede ao usuário que escolha um nível de dificuldade.
    - Lê as coordenadas e valida as entradas do jogador.
    - Atualiza a matriz mostrada ao jogador e verifica se ele ganhou ou perdeu.
    - Limpa a tela após cada jogada (opcional).
    - Mostra a matriz final se o jogador perdeu ou venceu.
    - Libera a memória que foi usada.

## Considerações Finais
O código foi feito para ser fácil de ler e manter. As funções são separadas, o que ajuda a entender e a reutilizar em outros projetos.

As validações estão lá para garantir que a entrada do usuário seja sempre correta, evitando erros e problemas inesperados.

A alocação dinâmica permite que o jogo funcione com diferentes tamanhos de tabuleiro, dependendo da dificuldade escolhida.

