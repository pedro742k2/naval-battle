/**
 * @autores:
 * Nome: Afonso Marques Ferreira    Número de Aluno: a48277
 * Nome: Pedro Manuel Peres Batista Número de Aluno: a48389
 **/

#include <stdio.h>

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

int main(void)
{
  Board brd;
  init_board(N, M, &brd);

  /**Exemplo de uso da print_board e da place_boat**/
  /**Precisa de as implementar primeiro**/
  //print_board(N, M, brd.board, 0);
  //place_boat(1, 3, 'H', 'P', &brd);

  char player1[100] = "", player2[100] = "";
  printf("Bem-vindos. Primeiramente, insiram os nomes dos jogadores (Máximo 100 caracteres):\n");
  printf("Jogador 1 (defensor): ");
  fgets(player1, 100, stdin);
  printf("Jogador 2 (atacante): ");
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

  printf("Agora que ambos os jogadores estão identificados, o jogador 1 (%s) irá proceder à colocação dos %d barcos.\n", player1, B);

  // Variáveis auxiliares.
  char boatType, dir;
  int boatSize, x, y;
  /** Máximo de cada tipo de barco:
   * 1 'P'
   * 1 'N'
   * 2 'C'
   * 2 'S' */

  for (int i = 0; i < B; i++)
  {
    // While "checkBoatPlacement" is false (0), program will keep asking for valid boat info
    int checkBoatPlacement = 0;

    // Enquanto "checkBoatPlacement" for zero, continua a pedir novos dados.
    while (!checkBoatPlacement)
    {
      print_board(N, M, brd.board, 1);

      printf("Nota: %s, restam colocar %d navios.\n--- Barco %d ---\n", player1, B - brd.numBoatsAfloat, i);

      // Tipo de barco e nº de posições.
      printf("Tipo de barco ('P', 'N', 'C' ou 'S'): ");
      scanf(" %c", &boatType);

      boatSize = typeToSize(boatType);

      // Direção do barco;
      printf("\nIndique a direção do barco.\n('H' - Horizontal e 'V' - Vertical): ");
      scanf(" %c", &dir);

      // Coordenadas iniciais.
      printf("\nConsiderando o barco '%c' com %d posições, insira as coordenadas iniciais.\nO tabuleiro tem %d linhas e %d colunas, ou seja:\n\"x inicial\" deve estar compreendido entre 0 e %d;\n\"y inicial\" deve estar compreendido entre 0 e %d:\n", boatType, boatSize, N, M, N - 1, N - 1);
      printf("x inicial: ");
      scanf("%d", &x);
      printf("y inicial: ");
      scanf("%d", &y);

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

      if (!checkBoatPlacement)
      {
        printf("Ser-lhe-ão pedidas as informações novamente...\n");
      }
    }
  }

  print_board(N, M, brd.board, 1);

  int availablePlays = 40, targetX, targetY;

  while (availablePlays >= 0)
  {
    print_board(N, M, brd.board, 0);

    printf("%s, você tem %d jogadas e restam afundar %d navios.\nCaso deseje (declarando a vitória a %s):\n - Sair, digite \"-1\" numa das coordenadas.\n - Ver todos os navios (o jogo continuará), digite \"-2\" numa das coordenadas.\n", player2, availablePlays, brd.numBoatsAfloat, player1);
    printf("Coordenada a atacar:\n");
    printf("x: ");
    scanf("%d", &targetX);
    printf("y: ");
    scanf("%d", &targetY);

    if (targetX == -1 || targetY == -1)
    {
      printf("%s ganhou o jogo! A sair...\n", player1);
      return 0;
    }
    else if (targetX == -2 || targetY == -2)
    {
      // Função para mostar todos os navios.
    }

    int targetState = target(targetX, targetY, &brd);
    printf("\n---------------------------------------------\n");
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
    printf("---------------------------------------------\n");
  }

  return 0;
}
