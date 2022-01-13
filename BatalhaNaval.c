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

/**Representa uma coordenada*/
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
  printf("+");
  for (int j = 0; j < n; j++)
  {
    printf("---+");
  }
  printf("\n");

  for (int i = 0; i < m; i++)
  {
    printf("|");
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
      for (int j = 0; j < n; j++)
      {
        printf("   |");
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
    if (board[boat->coord[i].pos.x][boat->coord[i].pos.y] != ' ')
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
  Boat newBoat;
  Position pos;
  pos.x = x1;
  pos.y = y1;
  init_boat(&newBoat, type, pos, dir);
  if (!check_free(N, M, &newBoat, &board))
  {
    return -1;
  }

  if (dir != 'H' && dir != 'V')
  {
    return -3;
  }

  if (type != 'P' && type != 'N' && type != 'C' && type != 'S')
  {
    return -4;
  }

  //Implementar
  int boatSize = typeToSize(type);
  if (dir == 'H')
  {
    if (x1 < 0 || x1 + boatSize > N)
    {
      return -2;
    }
    for (int i = x1; i < boatSize; i++)
    {
      board->board[x1 + i][y1] = type;
      board->boats[board->numBoats] = newBoat;
      board->numBoats++;
      board->numBoatsAfloat++;
    }
  }
  else
  {
    if (y1 < 0 || y1 + boatSize > M)
    {
      return -2;
    }
    for (int i = y1; i < boatSize; i++)
    {
      board->board[x1][y1 + i] = type;
    }
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
  if (board->board[x][y] == ' ')
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
            return board->board[x][y];
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
  if (board->board[x][y] == "*" || board->board[x][y] == 'A')
  {
    return 0;
  }

  switch (checkSink)
  {
  case 'I':
    return -2;

  case 'F':
    board->board[x][y] = checkSink; // checkSink = 'F', neste caso.
    return -1;

  default:
    // Verifica se foi afundado. Se sim, coloca 'A' nas posições do barco.
    if (!targetedBoat->afloat)
    {
      for (int i = 0; i < targetedBoat->tSize; i++)
      {
        board->board[targetedBoat->coord[i].pos.x][targetedBoat->coord[i].pos.y] = 'A';
      }
      return targetedBoat->tSize;
    }
    // Caso não tenha sido afundado, coloca um asterísco na coordenada atacada.

    return 1;
    board->board[x][y] = '*';
  }
}

//int colocaNavio()
int main(void)
{
  Board brd;
  init_board(N, M, &brd);
  print_board(N, M, brd.board, 1);

  //Testes
  /* Boat boat;
  Position pos;
  pos.x = 2;
  pos.y = 4;
  init_boat(&boat, 'P', pos, 'H');
  int isFree = check_free(M, M, &boat, brd.board);

  printf("---BOAT INFO---\nafloat: %d;\ntSize: %d;\ntype: %c;\n", boat.afloat, boat.tSize, boat.type);

  for (int i = 0; i < boat.tSize; i++)
  {
    printf("Coordinates:\n\tafloat: %d;\n\tx: %d;\n\ty: %d.\n", boat.coord[i].afloat, boat.coord[i].pos.x, boat.coord[i].pos.y);
  } */

  /**Exemplo de uso da print_board e da place_boat**/
  /**Precisa de as implementar primeiro**/
  //print_board(N, M, brd.board, 0);
  //place_boat(1,3, 'H', 'P', &brd);

  return 0;
}