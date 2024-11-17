# Campo Minado - Versão 2.0
<p>Esta é uma versão aprimorada da primeira versão. Neste trabalho, implementei a versão 2.0 do jogo, com o objetivo de introduzir novas funcionalidades, incluindo a capacidade de salvar e carregar partidas. Além disso, a estrutura do código foi reorganizada para melhorar a legibilidade e manutenibilidade.</p>

<p><strong>Funcionalidades</strong></p>

<p><strong>1. Novo Sistema de Salvamento de Partidas</strong></p>
<p>Na versão 2.0, agora suas partidas são sslvas em uma pasta e você pode vê-las qualquer momento. As mudanças incluem:</p>
<ul>
  <li><strong>Salvar Jogo:</strong> Durante toda a partida automatimante as suas jogadas e o mapa é armazenada em um arquivo txt, e pode ser acessado depois pelo jogador.</li>
</ul>

#
<p><strong>2. Separação das Funções em Arquivos</strong></p>
<p>A estrutura do código foi reorganizada para melhorar a modularidade e a manutenção. Agora, temos diferentes arquivos para organizar as funcionalidades do jogo.</p>
<ul>
  <li><strong>campo_minadoV2.c:</strong> Arquivo principal do jogo, onde ocorre a lógica do jogo, incluindo a interação com o usuário e a execução das funções.</li>
  <li><strong>campoMinado.c:</strong> Contém as funções auxiliares que gerenciam a criação da matriz do campo minado, a alocação de bombas, e a manipulação de células.</li>
  <li><strong>registro.c:</strong> Arquivo responsável pelas funções de salvar e carregar o progresso do jogo.</li>
  <li><strong>registro.c:</strong> Cabeçalho com as declarações das funções e definições necessárias para salvar o jogo.</li>
  <li><strong>campoMinado.h:</strong> Cabeçalho com as declarações das funções e definições necessárias para a jogabilidade.</li>
</ul>

#
<p><strong>3. Interação com o Usuário</strong></p>
<p>O jogo agora inclui interações mais flexíveis para o jogador, como a adição de cores para melho visualização do mapa, além da adiçao do algoritimo flood fill</p>
<ul>
  <li><strong>Escolha de Dificuldade:</strong> O jogador pode escolher entre três níveis de dificuldade:
    <ul>
      <li><strong>Fácil:</strong> 10x10 com 15 bombas.</li>
      <li><strong>Médio:</strong> 20x20 com 60 bombas.</li>
      <li><strong>Difícil:</strong> 30x30 com 135 bombas.</li>
    </ul>
  </li>
</ul>

#
<p><strong>4. Estrutura de Funções</strong></p>
<p>As funções foram divididas e melhoradas para otimizar o código. Algumas funções importantes incluem:</p>
<ul>
  <li><strong>LerCoordenadas:</strong> Função para ler as coordenadas inseridas pelo jogador e validar se são válidas.</li>
  <li><strong>CriaMatDinamica:</strong> Cria a matriz do campo minado dinamicamente com base no tamanho do campo escolhido.</li>
  <li><strong>AlocaBombasEZeros:</strong> Distribui as bombas de forma aleatória na matriz.</li>
  <li><strong>InializaMatFront:</strong> Inicializa a matriz visível ao jogador, que é preenchida com -1 para indicar células não clicadas.</li>
  <li><strong>ImprimeMatFront:</strong> Exibe a matriz do jogo visível para o jogador.</li>
  <li><strong>ImprimeJogada e ImprimeFimPartida:</strong> Funções responsáveis pela gravação do progresso do jogo em arquivos e o resultado do jogo.</li>
</ul>

#
<p><strong>5. Melhorias de Usabilidade</strong></p>
<ul>
  <li><strong>Validação de Entradas:</strong> Melhor tratamento de entradas do usuário, garantindo que apenas valores válidos sejam aceitos.</li>
  <li><strong>Interface de Jogo no Terminal:</strong> O jogo foi feito para rodar no terminal, usando apenas texto para exibir o campo minado e a interface, mas agora o programa imprime o campo em diferentes cores para melhoras a visibilidade do mapa.</li>
</ul>

<p><strong>Arquivos do Projeto</strong></p>
<ul>
  <li><strong>campoMinadoV2.c:</strong> Contém o código principal do jogo, incluindo a interação com o usuário.</li>
  <li><strong>campoMinadoFuncoes.c:</strong> Funções auxiliares para manipulação da matriz do campo minado.</li>
  <li><strong>salvamento.c:</strong> Funções para salvar e carregar o estado do jogo.</li>
  <li><strong>campoMinado.h:</strong> Arquivo de cabeçalho que define as funções e estruturas do jogo.</li>
</ul>

<p><strong>Explicação das Mudanças</strong></p>
<ul>
  <li><strong>Alocação Dinâmica de Memória:</strong> O jogo agora utiliza alocação dinâmica para criar a matriz que representa o campo minado. Isso permite que o tamanho do campo seja ajustado com base na escolha do nível de dificuldade.</li>
  <li><strong>Salvar e Carregar Partidas:</strong> Utilizamos arquivos para salvar o progresso do jogo. Quando o jogador opta por salvar, o estado do campo minado, incluindo as bombas e o progresso do jogador, é salvo em um arquivo binário. O jogo pode ser retomado carregando esse arquivo.</li>
  <li><strong>Estrutura Modular:</strong> O código foi dividido em múltiplos arquivos, com funções específicas para cada parte do jogo, como criação da matriz, alocação de bombas, impressão do campo e manipulação do salvamento. Isso melhora a organização e a manutenção do código.</li>
  
  <li><strong>Melhorias na Interface:</strong> A interação com o usuário foi aprimorada, com validações para entradas incorretas e uma interface mais amigável, no terminal, para escolher as coordenadas e salvar o progresso.</li>
</ul>

#
<p><strong>Contribuições</strong></p>
<ul>
  <li><strong>Professor:</strong> Juan Colonna, por guiar o desenvolvimento do projeto e fornecer as diretrizes iniciais.</li>
  <li><strong>Aluno:</strong>Ruan Sathler, por implementar as mudanças e melhorias, incluindo a funcionalidade de salvamento de partidas.</li>
</ul>

#
<p><strong>Considerações Finais</strong></p>
<p>Esta versão do Campo Minado oferece uma experiência mais robusta e flexível, permitindo que o jogador salve o progresso de sua partida e reveja a qualquer momento. A alocação dinâmica de memória garante que o jogo seja escalável para diferentes tamanhos de tabuleiro, tornando o código mais modular e fácil de manter.</p>
