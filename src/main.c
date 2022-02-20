/**
 * @autores:
 * Nome: Afonso Marques Ferreira    Número de Aluno: a48277
 * Nome: Pedro Manuel Peres Batista Número de Aluno: a48389
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Número de barcos (B)
#define B 6
// Linhas e colunas do tabuleiro (N e M)
#define N 8
#define M 8

/* Cores para o terminal */
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RESET "\x1b[0m"

/**Representa uma coordenada**/
typedef struct
{
  int x;
  int y;
} Position;

/**Associa cada coordenada do barco com um estado**/
typedef struct
{
  int afloat;   // 0 indica que está afundada, 1 indica que não
  Position pos; // Coordenada
} StateCoord;

/**Representa um barco**/
typedef struct
{
  int afloat;          // Posições que ainda não foram afundadas
  int tSize;           // Tamanho do tipo do barco
  StateCoord coord[5]; // O barco maior tem 5 coordenadas, usando o tSize garantimos que acedemos apenas às existentes
  char type;           // Caracter que representa o tipo do barco
} Boat;

/**Representa um tabuleiro**/
typedef struct
{
  int numBoatsAfloat; // Número de barcos não afundados
  int numBoats;       // Número de barcos que foram colocados
  Boat boats[B];      // Array de barcos. Cada barco é do tipo Boat.
  char board[N][M];   // Array que contém a informação de cada posição do tabuleiro
} Board;

/**
 * NOTA IMPORTANTE:
 * Não pode alterar nenhuma das assinaturas das funções abaixo.
 * Este ficheiro tem de ser considerado em conjunção com o enunciado do TP2.
 **/

/**
 * Function: cleanConsole
 *
 * Limpa o histórico do terminal.
 *
 **/
void clearConsole(void)
{
  system("clear || cls");
}

/**
 * Function: init_board
 *
 * Inicializa um Board.
 *
 * n: dimensão x do tabuleiro
 * m: dimensão y do tabuleiro
 * b: apontador para o Board que vai ser inicializado
 *
 **/
void init_board(int n, int m, Board *b)
{
  b->numBoatsAfloat = 0;
  b->numBoats = 0;

  // Inicializa o array board
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      b->board[i][j] = ' ';
    }
  }
}

/**
 * Function: print_board
 *
 * Mostra no ecrã o estado atual do tabuleiro.
 * Se a flag é 0 (zero) não mostra os barcos, se for 1, mostra.
 * Quando a flag é 1, para indicar a posição de cada barco, é colocada em todas
 * as posições do barco a letra que representa o seu tipo.
 *
 * n: número de linhas do tabuleiro
 * m: número de colunas do tabuleiro
 * board: estado do tabuleiro
 * flag: indicador do modo de visualização do tabuleiro -- se for 0 (zero) não
 *       mostra os barcos; se for diferente de 0 (zero) mostra.
 */

void print_board(int n, int m, char board[n][m], int flag)
{
  printf("+");
  for (int j = 0; j < n; j++)
  {
    printf("---+");
  }
  printf("\n");

  for (int i = 0; i < m; i++)
  {
    printf("|");
    if (flag) // Mostra tudo
    {
      for (int j = 0; j < n; j++)
      {
        printf(ANSI_COLOR_GREEN " %c " ANSI_COLOR_RESET "|", board[i][j]);
      }
      printf("\n");
    }
    else // Esconde os barcos
    {
      char charToPrint;
      for (int j = 0; j < n; j++)
      {
        printf(ANSI_COLOR_RED);
        charToPrint = (board[i][j] == '*' || board[i][j] == 'A' || board[i][j] == 'F') ? board[i][j] : ' ';
        printf(" %c " ANSI_COLOR_RESET "|", charToPrint);
      }
      printf("\n");
    }

    printf("+");
    for (int j = 0; j < n; j++)
    {
      printf("---+");
    }
    printf("\n");
  }
}

/**
 * Function: typeToSize
 *
 * Dado o tipo do barco devolve o seu tamanho.
 *
 * type: tipo do barco ('P', 'N', 'C', ou 'S')
 *
 * return
 *  -1 se o tipo de barco for inválido
 *  caso contrário, devolve o tamanho do barco
 **/
int typeToSize(char type)
{
  int size = -1;

  switch (type)
  {
  case 'P':
    size = 5;
    break;

  case 'N':
    size = 4;
    break;

  case 'C':
    size = 3;
    break;

  case 'S':
    size = 2;
    break;
  }

  return size;
}

/**
 * Function: init_boat
 *
 * Dado um apontador para um barco, o tipo, a posição inicial e a direcção,
 * inicializa o barco com todas as sua posições, tamanho e tipo.
 * Por exemplo, se o tipo do barco é 'C' (contratorpedeiro),
 * a posição inicial (1,1), e a direcção 'H', então o barco fica inicializado
 * com os seguintes valores
 *
 * afloat = 3;
 * tSize = 3;
 * coord = [(1,(1,1)),(1,(1,2)),(1,(1,3))]; Onde (s,(x,y)) representa um elemento do tipo StateCoord
 * type = 'C';
 *
 * b: barco que vai ser inicializado
 * type: tipo do barco
 * xy: posição inicial do barco
 * dir: direcção do barco
 *
 **/
void init_boat(Boat *b, char type, Position xy, char dir)
{
  int boatSize = typeToSize(type);

  b->type = type;
  b->afloat = b->tSize = boatSize;
  for (int i = 0; i < boatSize; i++)
  {
    b->coord[i].afloat = 1;
    if (dir == 'H')
    {
      b->coord[i].pos.x = xy.x + i;
      b->coord[i].pos.y = xy.y;
    }
    else
    {
      b->coord[i].pos.x = xy.x;
      b->coord[i].pos.y = xy.y + i;
    }
  }
}

/**
 * Function: check_free
 *
 * Verifica se estão livres todas as posições que serão ocupadas por um
 * barco no tabuleiro.
 *
 * n: dimensão x do tabuleiro
 * m: dimensão y do tabuleiro
 * boat: barco a colocar no tabuleiro
 * board: estado atual do tabuleiro
 *
 * returns:
 *  1 se todas as posições estão livres
 *  0 caso contrário
 *
 **/
int check_free(int n, int m, Boat *boat, char board[n][m])
{
  for (int i = 0; i < boat->tSize; i++)
  {
    if (board[boat->coord[i].pos.y][boat->coord[i].pos.x] != ' ')
    {
      return 0;
    }
  }

  return 1;
}

/**
 * Function: place_boat
 *
 * Cria e coloca, se tal for possível, um barco no tabuleiro.
 *
 * x1: coordenada x inicial do barco
 * y1: coordenada y inicial do barco
 * dir: dirrecção do barco ('H' ou 'V')
 * type: o tipo de barco
 * board: estado atual do tabuleiro
 *
 * returns:
 * 0 se o barco for colocado com sucesso.
 * -1 se alguma das posições já está ocupada.
 * -2 se as coordenadas forem inválidas.
 * -3 se a direcção for inválida.
 * -4 se o tipo de barco for inválido.
 **/
int place_boat(int x1, int y1, int dir, char type, Board *board)
{
  // Valida tipo de barco
  if (type != 'P' && type != 'N' && type != 'C' && type != 'S')
  {
    return -4;
  }

  // Valida tipo de direção
  if (dir != 'H' && dir != 'V')
  {
    return -3;
  }

  Boat newBoat;
  Position pos;
  pos.x = x1;
  pos.y = y1;
  init_boat(&newBoat, type, pos, dir);

  int boatSize = newBoat.tSize;

  if (dir == 'H')
  {
    // Valida as coordenadas na horizontal
    if (x1 < 0 || x1 + boatSize > M || y1 < 0 || y1 >= N)
    {
      return -2;
    }

    // Verifica se as posições estão livres
    if (!check_free(N, M, &newBoat, board->board))
    {
      return -1;
    }

    // Coloca o barco no tabuleiro (horizontal)
    for (int i = 0; i < boatSize; i++)
    {
      board->board[y1][x1 + i] = type;
    }
  }
  else
  {
    // Verifica as coordenadas na vertical
    if (x1 < 0 || x1 >= M || y1 < 0 || y1 + boatSize > N)
    {
      return -2;
    }

    // Verifica se as posições estão livres
    if (!check_free(N, M, &newBoat, board->board))
    {
      return -1;
    }

    // Coloca o barco no tabuleiro (vertical)
    for (int i = 0; i < boatSize; i++)
    {
      board->board[y1 + i][x1] = type;
    }
  }

  // Adiciona o barco à estrutura "Board"
  board->boats[board->numBoats] = newBoat;
  board->numBoats++;
  board->numBoatsAfloat++;

  return 0;
}

/**
 * Function: check_sink
 *
 * Verifica se ao atacar a posição (x,y) algum barco é afundado.
 *
 * x: coordenada x a atacar
 * y: coordenada y a atacar
 * board: estado atual do tabuleiro
 *
 * returns:
 *   'F' se não for afundado nenhum barco;
 *   Se afundar um barco devolve a letra que representa o seu tipo: 'P', 'N', 'C' ou 'S';
 *   'I' se a coordenada for inválida.
 *
 **/
char check_sink(int x, int y, Board *board)
{
  // Validação das coordenadas.
  if (x < 0 || y < 0 || x >= N || y >= M)
  {
    return 'I';
  }

  // Caso não tenha sido atingido nenhum barco (ou seja, nenhum afundado).
  if (board->board[y][x] == ' ')
  {
    return 'F';
  }

  Boat *targetedBoat;
  // Encontra o barco atingido
  for (int i = 0; i < B; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      if (board->boats[i].coord[j].pos.x == x && board->boats[i].coord[j].pos.y == y)
      {
        targetedBoat = &board->boats[i];

        // Verifica se a coordenada já havia sido atingida. Se não, atualiza os valores da mesma.
        if (targetedBoat->coord[j].afloat)
        {
          // Decrementa o número posições do barco não afundadas.
          targetedBoat->afloat--;
          // Indica que a coordenada foi afundada.
          targetedBoat->coord[j].afloat = 0;

          // Verifica se o barco foi totalmente afundado.
          if (!targetedBoat->afloat)
          {
            // Decrementa o número de barcos não afundados.
            board->numBoatsAfloat--;
            // Retorna o tipo do barco.
            return targetedBoat->type;
          }
        }

        break;
      }
    }
  }

  // Caso o barco atingido não tenha sido afundado.
  return 'F';
}

/**
 * Function: target
 *
 * Ataca a coordenada (x,y) no tabuleiro.
 * Se a coordenada (x,y) é parte de um barco, então coloca um '*' nessa
 * posição '*'; caso contrário coloca a letra 'F' nessa posição; caso afunde
 * um barco coloca em todas as posições desse barco a letra 'A'.
 *
 * x: coordenada x a atacar
 * y: coordenada y a atacar
 * board: estado atual do tabuleiro
 *
 * returns:
 *   0 se a posicao já foi atacada anteriormente
 *   1 se acerta numa coordenada de um barco mas sem o afundar
 *   -1 se nao tiver sucesso
 *   -2 se a coordenada for inválida.
 *   caso afunde um barco, devolve o número correspondente ao tamanho do barco
 *   que afundou (valor de 2 a 5)
 *
 **/
int target(int x, int y, Board *board)
{
  int checkSink = check_sink(x, y, board);

  Boat *targetedBoat;

  // Encontra o barco atingido
  for (int i = 0; i < B; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      if (board->boats[i].coord[j].pos.x == x && board->boats[i].coord[j].pos.y == y)
      {
        targetedBoat = &board->boats[i];
        break;
      }
    }
  }

  // Retorna 0 se a coordenada já foi atingida anteriormente.
  if (board->board[y][x] == '*' || board->board[y][x] == 'A' || board->board[y][x] == 'F')
  {
    return 0;
  }

  switch (checkSink)
  {
  case 'I':
    return -2;

  case 'F':
    if (board->board[y][x] == ' ')
    {
      board->board[y][x] = checkSink; // checkSink = 'F', neste caso.
      return -1;
    }

    board->board[y][x] = '*';
    return 1;

  default:
    // Verifica se foi afundado. Se sim, coloca 'A' nas posições do barco.
    if (!targetedBoat->afloat)
    {
      for (int i = 0; i < targetedBoat->tSize; i++)
      {
        board->board[targetedBoat->coord[i].pos.y][targetedBoat->coord[i].pos.x] = 'A';
      }
      return targetedBoat->tSize;
    }
    // Caso não tenha sido afundado, coloca um asterísco na coordenada atacada.

    return 1;
    board->board[y][x] = '*';
  }
}

/**
 * Function: listBoatsAfloat
 *
 * Lista os barcos não afundados.
 *
 * board: estado atual do tabuleiro
 *
 * returns:
 *  1 se o tipo de barco está disponível
 *  0 caso contrário
 *
 **/
void listBoatsAfloat(Board board)
{
  // Variável auxiliar para verificar o primeiro barco não afundado, com finalidade de formatação (não colocar "," no início do primeiro barco)
  int firstBoatAfloat = 1;

  printf("(");
  for (int i = 0; i < B; i++)
  {
    if (board.boats[i].afloat)
    {
      // Coloca uma vírgula a separar os tipos, à excessão da primeira iteração.
      if (!firstBoatAfloat)
      {
        printf(", ");
      }

      printf("%c", board.boats[i].type);

      firstBoatAfloat = 0;
    }
  }
  printf(")");
}

/**
 * Function: checkTypeAvailability
 *
 * Verifica se existem barcos do tipo dado disponíveis.
 *
 * board: estado atual do tabuleiro
 * type: tipo do barco
 *
 * returns:
 *  1 se o tipo de barco está disponível
 *  0 caso contrário
 *
 **/
int checkTypeAvailability(Board board, char type)
{
  /**
   *  maxOfType: Número máximo de cada tipo de barco
   * typeAccumulator: Número de instâncias do tipo de barco no tabuleiro
   */
  int maxOfType, typeAccumulator = 0;

  // Verifica o número máximo de cada tipo de barco
  maxOfType = (type == 'P' || type == 'N') ? 1 : 2;

  for (int i = 0; i < board.numBoats; i++)
  {
    if (type == board.boats[i].type)
    {
      typeAccumulator++;
    }
  }

  // Se "typeAccumulator" >= "maxOfType", o tipo de barco dado não pode ser adicionado.
  if (typeAccumulator >= maxOfType)
  {
    return 0;
  }

  return 1;
}

/**
 * Function: askNewGame
 *
 * Pergunta ao jogador se deseja começar um novo jogo.
 *
 * returns:
 *  1 se o jogador desejar começar um novo jogo
 *  0 caso contrário
 *
 **/
int askNewGame(void)
{
  clearConsole();
  char newGame = ' ';

  // Ciclo irá repetir até que uma opção válida seja introduzida.
  while (newGame != 'S' && newGame != 'N')
  {
    printf("Deseja começar um novo jogo [S/N]: ");
    scanf(" %c", &newGame);
  }

  if (newGame == 'N')
  {
    return 0;
  }

  return 1;
}

/**
 * Function: printInfo
 *
 * Imprime uma mensagem com um formato especial, conforme sucesso ou erro.
 *
 * message: Mensagem a ser impressa.
 * error: 2 se for uma mensagem de aviso, 1 se for de erro e 0 se for de sucesso.
 */
void printInfo(char *message, int error)
{
  int messageLength = strlen(message);

  // Ciclo que imprime os traços do tamanho da string
  for (int i = 0; i < messageLength; i++)
  {
    printf("-");
  }

  // Seleciona uma cor com base no parametro formal "error"
  switch (error)
  {
  case 0:
    printf(ANSI_COLOR_GREEN);
    break;

  case 1:
    printf(ANSI_COLOR_RED);
    break;

  case 2:
    printf(ANSI_COLOR_YELLOW);
    break;

  default:
    printf(ANSI_COLOR_RESET);
  }

  printf("\n%s\n" ANSI_COLOR_RESET, message);

  for (int i = 0; i < messageLength; i++)
  {
    printf("-");
  }

  printf("\n\n");
}

/**
 * Function: confirmExit
 *
 * Verifica se o jogador deseja sair ou render-se.
 *
 * valueToCheck: Valor a verificar
 * cloneBoard: Clone do tabuleiro com os barcos originais
 * attacker: Nome do jogador atacante
 * defender: Nome do jogador defensor
 *
 * returns:
 *  2 caso o jogador deseje render-se (e visualize o tabuleiro inimigo)
 *  1 caso deseje sair
 *  0 caso anule a decisão de sair/render-se
 *
 **/
int confirmExit(int valueToCheck, Board cloneBoard, char *attacker, char *defender)
{
  int exit = 0;

  // Caso o jogador decida sair do jogo.
  if (valueToCheck == -1)
  {
    // Confirma se o jogador realmente quer desistir.
    char confirmSurrender = ' ';
    // Ciclo irá repetir até que uma opção válida seja introduzida.
    while (confirmSurrender != 'S' && confirmSurrender != 'N')
    {
      printf(ANSI_COLOR_YELLOW "Deseja realmente sair? [S/N]: " ANSI_COLOR_RESET);
      scanf(" %c", &confirmSurrender);
    }

    if (confirmSurrender == 'N')
    {
      return 0;
    }

    printf(ANSI_COLOR_RED "%s saiu do jogo.\n" ANSI_COLOR_RESET, attacker);

    exit = 1;
  }
  else if (valueToCheck == -2)
  {
    // Confirma se o jogador realmente quer desistir.
    char confirmSurrender = ' ';
    // Ciclo irá repetir até que uma opção válida seja introduzida.
    while (confirmSurrender != 'S' && confirmSurrender != 'N')
    {
      printf(ANSI_COLOR_YELLOW "Quer realmente desistir do jogo ao ver o tabuleiro inimigo?" ANSI_COLOR_RESET "\nO jogo continuará de qualquer forma.\nDeseja desistir [S/N]: ");
      scanf(" %c", &confirmSurrender);
    }

    if (confirmSurrender == 'N')
    {
      return 0;
    }

    // Caso o jogador desista, vendo o tabuleiro adversário.

    char continueGame[10];
    strcpy(continueGame, "");
    // Enquanto o input for diferente de "ok"...
    while (strcmp(continueGame, "ok"))
    {
      printf(ANSI_COLOR_YELLOW "ATENÇÃO: %s, você perdeu o jogo." ANSI_COLOR_RESET " O jogo continuará de qualquer forma.\nO tabuleiro com os navios de %s será exibido.\n\n", attacker, defender);

      print_board(N, M, cloneBoard.board, 1);

      printf("\nEscreva \"" ANSI_COLOR_GREEN "ok" ANSI_COLOR_RESET "\" para continuar: ");
      scanf(" %s", continueGame);
    }

    exit = 2;
  }

  return exit;
}

int main(void)
{
  Board brd;

  // Número de partidas realizadas
  int plays = 0;

  // Nome dos jogadores
  char player1[100] = "", player2[100] = "";

  clearConsole();

  // Pedido da idenficiação dos jogadores
  printInfo("Bem-vindos. Primeiramente, insiram os nomes dos jogadores (Máximo 100 caracteres)", -1);
  printf("Jogador defensor: ");
  fgets(player1, 100, stdin);
  printf("Jogador atacante: ");
  fgets(player2, 100, stdin);

  // Remoção da quebra de linha dos nomes dos jogadores
  for (int i = 0; i < 100; i++)
  {
    if (player1[i] == '\n')
    {
      player1[i] = '\0';
    }

    if (player2[i] == '\n')
    {
      player2[i] = '\0';
    }
  }

  // Enquanto não forem realizadas 2 jogadas (plays = {0, 1}), o jogo continua.
  while (plays < 2)
  {
    init_board(N, M, &brd);

    char defender[100], attacker[100];

    if (!plays)
    {
      // Se for a primeira jogada (play = 0)
      strcpy(defender, player1);
      strcpy(attacker, player2);
    }
    else
    {
      // Se for a segunda jogada (play = 1)
      strcpy(defender, player2);
      strcpy(attacker, player1);
    }

    clearConsole();

    printf("Partida " ANSI_COLOR_GREEN "%d/2" ANSI_COLOR_RESET ".\n%s irá proceder à colocação dos " ANSI_COLOR_GREEN "%d" ANSI_COLOR_RESET " navios e %s irá atacá-los.\n\n", plays + 1, defender, B, attacker);

    /**
     * Variáveis auxiliares:
     *  boatType: Armazena o tipo de barco temporariamente
     *  dir: Armazena a direção do barco temporariamente
     *  defExit: Indica se o jogador defensor decidiu sair do jogo
     *  boatSize: Armazena o tamanho do barco para fins de validação
     *  (x, y): Coordenadas iniciais do barco a ser colocado
     */
    char boatType, dir, defExit = 0;
    int boatSize, x, y;

    // Pede as informações dos "B" barcos
    for (int i = 0; i < B; i++)
    {
      int checkBoatPlacement = 0;

      // Enquanto "checkBoatPlacement" (informação inválida) for zero, continua a pedir novos dados acerca do respetivo barco.
      while (!checkBoatPlacement)
      {
        defExit = 0;
        print_board(N, M, brd.board, 1);

        printf("\n%s, restam colocar " ANSI_COLOR_GREEN "%d" ANSI_COLOR_RESET " navios.\n-------------------------------| Barco %d |-------------------------------\n", defender, B - brd.numBoatsAfloat, i);

        printf("\n");
        printInfo("Nos inputs que se seguem, se assim o desejar, insira \"q\" para sair.", 2);

        // Tipo de barco e nº de posições.
        printf("Tipo de barco ('P', 'N', 'C' ou 'S'): ");
        scanf(" %c", &boatType);

        // Verifica se o jogador deseja sair
        if (boatType == 'q')
        {
          clearConsole();
          printf("%s saiu do jogo.\n", defender);
          defExit = 1;
          break;
        }

        boatSize = typeToSize(boatType);

        if (boatSize == -1)
        {
          clearConsole();
          printInfo("Tipo de barco inválido. Por favor, adicione um dos disponíveis.", 1);

          continue;
        }

        if (!checkTypeAvailability(brd, boatType))
        {
          clearConsole();
          printInfo("Tipo de barco indisponível. Por favor, adicione um dos disponíveis.", 1);

          continue;
        }

        dir = ' ';
        // Pede a direção do barco até que a mesma seja válida ou que o jogador decida sair
        while (dir != 'H' && dir != 'V')
        {
          printf("\nIndique a direção do barco.\n('H' - Horizontal ou 'V' - Vertical): ");
          scanf(" %c", &dir);

          if (dir != 'H' && dir != 'V')
          {
            // Verifica se o jogador deseja sair
            if (dir == 'q')
            {
              printf("%s saiu do jogo.\n", defender);
              defExit = 1;
              break;
            }

            printInfo("Tipo de direção inválida. Por favor, indique uma das disponíveis.", 1);
          }
        }

        // Se na selação da direção o jogador decidir sair
        if (defExit)
        {
          break;
        }

        printInfo("Nos inputs que se seguem, se assim o desejar, insira \"-1\" para sair.", 2);

        // Pedido das coordenadas iniciais do barco a colocar
        printf("Considerando o barco '%c' com %d posições, insira as coordenadas iniciais.\nO tabuleiro tem %d linhas e %d colunas, ou seja:\n\"x inicial\" deve estar compreendido entre 0 e %d;\n\"y inicial\" deve estar compreendido entre 0 e %d:\n", boatType, boatSize, N, M, N - 1, N - 1);

        // Coordenada inicial "x" do barco
        printf("x inicial: ");
        scanf("%d", &x);
        if (x < 0 || x >= N)
        {
          // Verifica se o jogador deseja sair
          if (x == -1)
          {
            clearConsole();
            printf("%s saiu do jogo.\n", defender);
            defExit = 1;
            break;
          }

          printInfo("Tipo de coordenada inválida. Por favor, adicione uma disponível.", 1);

          continue;
        }

        // Coordenada inicial "y" do barco
        printf("y inicial: ");
        scanf("%d", &y);
        if (y < 0 || y >= M)
        {
          // Verifica se o jogador deseja sair
          if (y == -1)
          {
            clearConsole();
            printf("%s saiu do jogo.\n", defender);
            defExit = 1;
            break;
          }

          printInfo("Tipo de coordenada inválida. Por favor, adicione uma disponível.", 1);

          continue;
        }

        int boatPlacement = place_boat(x, y, dir, boatType, &brd);

        clearConsole();

        switch (boatPlacement)
        {
        case -1:
          printInfo("Uma das posições já se encontra ocupada. Por favor, adicione uma posição disponível.", 1);
          break;

        case -2:
          printInfo("Coordenadas inválidas. Por favor, adicione uma coordenada válida.", 1);
          break;

        case -3:
          printInfo("Direção inválida. Por favor, adicione uma direção válida.", 1);
          break;

        case -4:
          printInfo("Tipo de barco inválido. Por favor, adicione um dos disponíveis.", 1);
          break;

        default:
          printInfo("Barco colocado com sucesso.", 0);
          checkBoatPlacement = 1;
        }
      }

      if (defExit)
      {
        // Pergunta se o jogador deseja começar um novo jogo.
        if (!askNewGame())
        {
          return 0;
        }
        else
        {
          clearConsole();
          init_board(N, M, &brd);
          i = -1;
          printInfo("A começar um novo jogo.", 0);
          printf("\n");
        }
      }
    }

    /** Variáveis auxiliares:
     * availablePlays: Jogadas disponíveis;
     * (targetX, targetY): Coordenada a atacar;
     * exit:
     *  - (0) Caso o jogador atacante decida não sair/render-se;
     *  - (1) Caso o jogador atacante decidir sair do jogo;
     *  - (2) Caso o jogador atacante veja o tabuleiro adversário, rendendo-se.
     * cloneBoard: Cópia do tabuleiro inicial, caso o jogador atacante o decida visualizar.
     */
    int availablePlays = 40, targetX, targetY, exit = 0;
    Board cloneBoard = brd;

    while (availablePlays > 0 && brd.numBoatsAfloat)
    {
      clearConsole();
      print_board(N, M, brd.board, 0);

      // Caso o jogador atacante se tenha rendido
      if (exit == 2)
      {
        printf(ANSI_COLOR_YELLOW "\nATENÇÃO: %s já ganhou o jogo, dado você visualizou o tabuleiro inimigo." ANSI_COLOR_RESET, defender);
      }

      // Mensagem especialmente formatada, com toda a informação essencial para o atacante
      printf("\nPartida " ANSI_COLOR_GREEN "%d/2" ANSI_COLOR_RESET ". %s, você tem " ANSI_COLOR_GREEN "%d" ANSI_COLOR_RESET " jogadas e restam afundar " ANSI_COLOR_GREEN "%d" ANSI_COLOR_RESET " navios ", plays + 1, attacker, availablePlays, brd.numBoatsAfloat);

      // Lista o número de barcos disponíveis, na mesma linha do resto da mensagem
      listBoatsAfloat(brd);

      // Continua a mensagem
      printf(".\nCaso deseje (declarando a vitória a %s):\n - Sair, digite \"" ANSI_COLOR_YELLOW "-1" ANSI_COLOR_RESET "\" numa das coordenadas.\n - Ver todos os navios (o jogo continuará), digite \"" ANSI_COLOR_YELLOW "-2" ANSI_COLOR_RESET "\" numa das coordenadas.\n", defender);

      // Coordenadas x a atacar
      printf("Coordenada a atacar:\n");
      printf("x: ");
      scanf("%d", &targetX);

      // Verifica a coordenada x
      if (targetX == -1 || targetX == -2)
      {
        exit = confirmExit(targetX, cloneBoard, attacker, defender);

        if (!exit || exit == 2)
        {
          continue;
        }
        else
        {
          break;
        }
      }

      // Coordenada y a atacar
      printf("y: ");
      scanf("%d", &targetY);

      // Verifica a coordenada y
      if (targetY == -1 || targetY == -2)
      {
        exit = confirmExit(targetY, cloneBoard, attacker, defender);

        // Se decidir não sair ou render-se
        if (!exit || exit == 2)
        {
          continue;
        }
        // Se decidir sair
        else
        {
          break;
        }
      }

      int targetState = target(targetX, targetY, &brd);

      switch (targetState)
      {
      case 0:
        printInfo("Esta coordenada já foi atacada anteriormente.", 2);
        break;

      case 1:
        printInfo("Acertou num navio. Ainda não o afundou.", 0);
        availablePlays--;
        break;

      case -1:
        printInfo("Sem sucesso.", 2);
        availablePlays--;
        break;

      case -2:
        printInfo("Coordenada inválida.", 1);
        break;

      default:
        printInfo("Barco afundado.", 0);
        availablePlays--;
      }
    }

    clearConsole();
    // Parabeliza o jogador vencedor.
    printf(ANSI_COLOR_GREEN "Parabéns %s, você ganhou a %dª ronda.\n" ANSI_COLOR_RESET, (!brd.numBoatsAfloat && exit != 2 && !exit) ? attacker : defender, plays + 1);

    if (!plays)
    {
      if (exit)
      {
        // Pergunta se o jogador deseja começar um novo jogo.
        if (!askNewGame())
        {
          return 0;
        }

        // Se sim, começa um novo jogo reiniciando o número de jogadas.
        plays = 0;
        continue;
      }

      plays++;
    }
    else
    {
      // Pergunta se o jogador deseja começar um novo jogo.
      if (!askNewGame())
      {
        // Caso não, sai
        return 0;
      }

      // Caso afirmativo, começa um novo jogo reiniciando o número de jogadas.
      plays = 0;
      continue;
    }
  }

  return 0;
}
