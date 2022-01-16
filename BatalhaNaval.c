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

/**Representa uma coordenada**/
typedef struct
{
  int x;
  int y;
} Position;

/**Associa cada coordenada do barco com um estado**/
typedef struct
{
  int afloat;   //0 indica que está afundada, 1 indica que não
  Position pos; //Coordenada
} StateCoord;

/**Representa um barco**/
typedef struct
{
  int afloat;          //Posições que ainda não foram afundadas
  int tSize;           //Tamanho do tipo do barco
  StateCoord coord[5]; //O barco maior tem 5 coordenadas, usando o tSize garantimos que acedemos apenas às existentes
  char type;           //Caracter que representa o tipo do barco
} Boat;

/**Representa um tabuleiro**/
typedef struct
{
  int numBoatsAfloat; //Número de barcos não afundados
  int numBoats;       //Número de barcos que foram colocados
  Boat boats[B];      //Array de barcos. Cada barco é do tipo Boat.
  char board[N][M];   //Array que contém a informação de cada posição do tabuleiro
} Board;

/**
 * NOTA IMPORTANTE:
 * Não pode alterar nenhuma das assinaturas das funções abaixo. 
 * Este ficheiro tem de ser considerado em conjunção com o enunciado do TP2.
 **/

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

  //Inicializa o array board
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
  printf("   ");
  for (int i = 0; i < M; i++)
  {
    printf(" %d  ", i);
  }
  printf("\n");

  printf("  +");
  for (int j = 0; j < n; j++)
  {
    printf("---+");
  }
  printf("\n");

  for (int i = 0; i < m; i++)
  {
    printf("%d |", i);
    if (flag) //Mostra tudo
    {
      for (int j = 0; j < n; j++)
      {
        printf(" %c |", board[i][j]);
      }
      printf("\n");
    }
    else // Esconde os barcos
    {
      //Implementar

      char charToPrint;
      for (int j = 0; j < n; j++)
      {
        charToPrint = (board[i][j] == '*' || board[i][j] == 'A' || board[i][j] == 'F') ? board[i][j] : ' ';
        printf(" %c |", charToPrint);
      }
      printf("\n");
    }

    printf("  +");
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
  //Implementar

  /*
  A estrutura Switch case, neste caso, dispensa de "break statements" dado que o "return" termina a execução da função nesse mesmo ponto.
  */
  switch (type)
  {
  case 'P':
    return 5;

  case 'N':
    return 4;

  case 'C':
    return 3;

  case 'S':
    return 2;

  default:
    return -1;
  }
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
  //Implementar
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
  //Implementar
  int isFree = 1;

  for (int i = 0; i < boat->tSize; i++)
  {
    if (board[boat->coord[i].pos.y][boat->coord[i].pos.x] != ' ')
    {
      isFree = 0;
    }
  }

  return isFree;
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
  if (type != 'P' && type != 'N' && type != 'C' && type != 'S')
  {
    return -4;
  }

  if (dir != 'H' && dir != 'V')
  {
    return -3;
  }

  Boat newBoat;
  Position pos;
  pos.x = x1;
  pos.y = y1;
  init_boat(&newBoat, type, pos, dir);

  //Implementar
  int boatSize = newBoat.tSize;

  if (dir == 'H')
  {
    if (x1 < 0 || x1 + boatSize > M || y1 < 0 || y1 >= N)
    {
      return -2;
    }

    if (!check_free(N, M, &newBoat, board->board))
    {
      return -1;
    }

    for (int i = 0; i < boatSize; i++)
    {
      board->board[y1][x1 + i] = type;
    }

    board->boats[board->numBoats] = newBoat;
    board->numBoats++;
    board->numBoatsAfloat++;
  }
  else
  {
    if (!check_free(N, M, &newBoat, board->board))
    {
      return -1;
    }

    if (x1 < 0 || x1 >= M || y1 < 0 || y1 + boatSize > N)
    {
      return -2;
    }

    for (int i = 0; i < boatSize; i++)
    {
      board->board[y1 + i][x1] = type;
    }

    board->boats[board->numBoats] = newBoat;
    board->numBoats++;
    board->numBoatsAfloat++;
  }
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
  //Implementar

  // Validação das coordenadas.
  if (x < 0 || y < 0 || x >= N || y >= M)
  {
    return 'I';
  }

  // Caso não tenha sido atingido nenhum barco (ou seja, nenhum afundado).
  // if (board->board[x][y] == ' ')
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
          // Decrementa o número posições não afundadas.
          targetedBoat->afloat--;
          // Indica que a coordenada foi afundada.
          targetedBoat->coord[j].afloat = 0;

          // Verifica se o barco foi totalmente afundado.
          if (!targetedBoat->afloat)
          {
            // Decrementa o número de barcos não afundados.
            board->numBoatsAfloat--;
            // Retorna o tipo do barco.
            return board->board[y][x];
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
  //Implementar
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
  // Variável auxiliar para verificar o primeiro barco não afundado, com finalidade de formatação
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
   * typeAccumulator: Número de instâncias do tipo dado no tabuleiro
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

  // Se "typeAccumulator" >= "maxOfType", o tipo de barco não pode ser adicionado.
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
  // Verifica se o jogador deseja começar um novo jogo.
  char newGame = ' ';
  // Ciclo irá repetir até que uma opção válida seja introduzida.
  while (newGame != 'S' && newGame != 'N')
  {
    system("clear");
    printf("Deseja começar um novo jogo [S/N]: ");
    scanf(" %c", &newGame);
  }

  if (newGame == 'N')
  {
    return 0;
  }

  return 1;
}

// ? colocaNavio();
int main(void)
{
  Board brd;

  // Número de jogadas feitas (começa com 0 e acaba em 2).
  int plays = 0;

  // Nome dos jogadores
  char player1[100] = "", player2[100] = "";

  // system("clear");

  printf("Bem-vindos. Primeiramente, insiram os nomes dos jogadores (Máximo 100 caracteres):\n");
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

    system("clear");
    printf("O jogador %s irá proceder à colocação dos %d navios e o jogador %s irá atacá-los.\n\n", defender, B, attacker);

    /* time_t timestamp;
    short int interval = 0.1;
    printf("A colocar o barco 1\n");
    place_boat(1, 1, 'H', 'P', &brd);
    timestamp = time(NULL) + interval;
    while (timestamp >= time(NULL))
      ;
    printf("A colocar o barco 2\n");
    place_boat(7, 1, 'V', 'N', &brd);
    timestamp = time(NULL) + interval;
    while (timestamp >= time(NULL))
      ;
    printf("A colocar o barco 3\n");
    place_boat(2, 3, 'H', 'C', &brd);
    timestamp = time(NULL) + interval;
    while (timestamp >= time(NULL))
      ;
    printf("A colocar o barco 4\n");
    place_boat(0, 4, 'V', 'C', &brd);
    timestamp = time(NULL) + interval;
    while (timestamp >= time(NULL))
      ;
    printf("A colocar o barco 5\n");
    place_boat(3, 5, 'H', 'S', &brd);
    timestamp = time(NULL) + interval;
    while (timestamp >= time(NULL))
      ;
    printf("A colocar o barco 6\n");
    place_boat(6, 6, 'V', 'S', &brd);
    timestamp = time(NULL) + interval;
    while (timestamp >= time(NULL))
      ; */

    // Variáveis auxiliares.
    char boatType, dir;
    int boatSize, x, y;

    for (int i = 0; i < B; i++)
    {
      // While "checkBoatPlacement" is false (0), program will keep asking for valid boat info
      int checkBoatPlacement = 0;

      // Enquanto "checkBoatPlacement" for zero, continua a pedir novos dados.
      while (!checkBoatPlacement)
      {
        print_board(N, M, brd.board, 1);

        printf("\n%s, restam colocar %d navios.\n-------------------------------| Barco %d |-------------------------------\n", defender, B - brd.numBoatsAfloat, i);

        // Tipo de barco e nº de posições.
        printf("Tipo de barco ('P', 'N', 'C' ou 'S'): ");
        scanf(" %c", &boatType);

        boatSize = typeToSize(boatType);

        // Direção do barco;
        printf("Indique a direção do barco.\n('H' - Horizontal ou 'V' - Vertical): ");
        scanf(" %c", &dir);

        // Coordenadas iniciais.
        printf("\nConsiderando o barco '%c' com %d posições, insira as coordenadas iniciais.\nO tabuleiro tem %d linhas e %d colunas, ou seja:\n\"x inicial\" deve estar compreendido entre 0 e %d;\n\"y inicial\" deve estar compreendido entre 0 e %d:\n", boatType, boatSize, N, M, N - 1, N - 1);
        printf("x inicial: ");
        scanf("%d", &x);
        printf("y inicial: ");
        scanf("%d", &y);

        system("clear");
        printf("-------------------------------------------------------------------\n");
        if (!checkTypeAvailability(brd, boatType))
        {
          printf("Tipo de barco indisponível. Por favor, adicione um dos disponíveis.\n");
        }
        else
        {
          int boatPlacement = place_boat(x, y, dir, boatType, &brd);

          switch (boatPlacement)
          {
          case -1:
            printf("Uma das posições já se encontra ocupada.\n");
            break;

          case -2:
            printf("Coordenadas inválidas\n");
            break;

          case -3:
            printf("Direção inválida\n");
            break;

          case -4:
            printf("Tipo de barco inválido\n");
            break;

          default:
            printf("Barco colocado com sucesso.\n");
            checkBoatPlacement = 1;
          }
        }
        printf("-------------------------------------------------------------------\n\n");

        if (!checkBoatPlacement)
        {
          printf("Ser-lhe-ão pedidas as informações novamente...\n");
        }
      }
    }

    system("clear");

    /** Variáveis auxiliares:
     * availablePlays: Jogadas disponíveis;
     * (targetX, targetY): Coordenadas a atacar;
     * Surrender: Caso o jogador atacante veja o tabuleiro adversário, rendendo-se;
     * Exit: Caso o jogador atacante decidir sair do jogo.
     */
    int availablePlays = 40, targetX, targetY, surrender = 0, exit = 0;
    // Variável usada para continuar o jogo, depois de uma pausa no terminal.
    char continueGame[10];
    // Cópia do tabuleiro inicial.
    Board cloneBoard = brd;

    while (availablePlays > 0 && brd.numBoatsAfloat)
    {
      print_board(N, M, brd.board, 0);

      if (surrender)
      {
        printf("\nATENÇÃO: %s já ganhou o jogo, dado que visualizou o tabuleiro do mesmo.", defender);
      }

      printf("\n%s, você tem %d jogadas e restam afundar %d navios ", attacker, availablePlays, brd.numBoatsAfloat);
      listBoatsAfloat(brd);
      printf(".\nCaso deseje (declarando a vitória a %s):\n - Sair, digite \"-1\" numa das coordenadas.\n - Ver todos os navios (o jogo continuará), digite \"-2\" numa das coordenadas.\n", defender);
      printf("Coordenada a atacar:\n");
      printf("x: ");
      scanf("%d", &targetX);
      printf("y: ");
      scanf("%d", &targetY);

      if (targetX == -1 || targetY == -1)
      {
        // Caso o jogador decida sair do jogo.

        // Confirma se o jogador realmente quer desistir.
        char confirmSurrender = ' ';
        // Ciclo irá repetir até que uma opção válida seja introduzida.
        while (confirmSurrender != 'S' && confirmSurrender != 'N')
        {
          system("clear");
          printf("Deseja realmente sair? [S/N]: ");
          scanf(" %c", &confirmSurrender);
        }

        if (confirmSurrender == 'N')
        {
          system("clear");
          continue;
        }

        printf("%s saiu do jogo.\n", attacker);
        exit = 1;
        break;
      }
      else if (targetX == -2 || targetY == -2)
      {
        // Confirma se o jogador realmente quer desistir.
        char confirmSurrender = ' ';
        // Ciclo irá repetir até que uma opção válida seja introduzida.
        while (confirmSurrender != 'S' && confirmSurrender != 'N')
        {
          system("clear");
          printf("Quer realmente desistir do jogo ao ver o tabuleiro inimigo?\nO jogo continuará de qualquer forma.\nDeseja desistir [S/N]: ");
          scanf(" %c", &confirmSurrender);
        }

        if (confirmSurrender == 'N')
        {
          system("clear");
          continue;
        }

        // Caso o jogador desista, vendo o tabuleiro adversário.
        surrender = 1;

        // Reinicia o valor da string "continueGame".
        strcpy(continueGame, "");
        // Enquanto o input for diferente de "ok"...
        while (strcmp(continueGame, "ok"))
        {
          system("clear");
          printf("ATENÇÃO: %s, você perdeu o jogo. O jogo continuará de qualquer forma.\nO tabuleiro com os navios de %s será exibido.\n\n", attacker, defender);

          print_board(N, M, cloneBoard.board, 1);

          printf("\nEscreva \"ok\" para continuar: ");
          scanf(" %s", continueGame);
        }

        system("clear");
        continue;
      }

      system("clear");

      int targetState = target(targetX, targetY, &brd);
      printf("---------------------------------------------\n");
      switch (targetState)
      {
      case 0:
        printf("Esta coordenada já foi atacada anteriormente.\n");
        break;

      case 1:
        printf("Acertou num navio. Ainda não o afundou.\n");
        availablePlays--;
        break;

      case -1:
        printf("Sem sucesso.\n");
        availablePlays--;
        break;

      case -2:
        printf("Coordenada inválida.\n");
        break;

      default:
        printf("Barco afundado.\n");
        availablePlays--;
      }
      printf("---------------------------------------------\n\n");
    }

    if (!plays)
    {
      // Reinicia o valor da string "continueGame".
      strcpy(continueGame, "");
      // Enquanto o input for diferente de "ok"...
      while (strcmp(continueGame, "ok"))
      {
        system("clear");

        printf("Parabéns %s, você ganhou a %dª ronda.\n", (!brd.numBoatsAfloat && !surrender && !exit) ? attacker : defender, plays + 1);

        printf("\nEscreva \"ok\" para continuar: ");
        scanf(" %s", continueGame);

        if (exit)
        {
          // Pergunta se o jogador deseja começar um novo jogo.
          if (!askNewGame())
          {
            // Caso não, sai
            system("clear");
            return 0;
          }

          // Se sim, começa um novo jogo reiniciando o número de jogadas.
          plays = 0;
          continue;
        }
      }

      plays++;
    }
    else
    {
      // Pergunta se o jogador deseja começar um novo jogo.
      if (!askNewGame())
      {
        // Caso não, sai
        system("clear");
        return 0;
      }

      // Se sim, começa um novo jogo reiniciando o número de jogadas.
      plays = 0;
      continue;
    }
  }

  return 0;
}
