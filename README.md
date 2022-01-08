# Trabalho Prático - Programação

## Hiperligações essenciais
- [Enunciado](https://moodle.ubi.pt/pluginfile.php/531717/mod_resource/content/1/BatalhaNaval.pdf);
- [Código base](https://moodle.ubi.pt/pluginfile.php/531716/mod_resource/content/1/BatalhaNaval.c);
- [Repositório do trabalho](https://github.com/pedro742k2/naval-battle);
- [Ficheiro fonte README.md](https://hackmd.io/@pedro742k2/batalha-naval) (Para o GitHub).

## Elementos do grupo
|            Nome            | Número |
|:--------------------------:|:------:|
| Pedro Manuel Peres Batista | a48389 |
|  Afonso Marques Ferreira   | a48277 |

## Condições do trabalho

### Submissão do trabalho:

- [ ] O nome do ficheiro deve ser constituído pelos números dos elementos do grupo, separados pelo caracter "_" (underscore), neste caso "a48277_a48389.c";
- [ ] Os elementos de grupo devem ser identificados no início do ficheiros;
- [ ] Os trabalhos não devem conter erros ou avisos de compilação, caso contrário será atribuída nota zero;

### Desenvolvimento do programa:

- [ ] As assinaturas das funções devem permanecer tal como estão no código base;
- [ ] Se usar outras funções auxiliares, as mesmas devem estar dentro das funções iniciais;
- [ ] As funções para as quais não é indicado input/output, não devem ter input/output;
- [ ] As estruturas (*structs*) no código base devem ser utilizadas, não sendo permitida qualquer alteração nas mesmas;

## Funcionamento

### Regras gerais:

- Para cada posição do tabuleiro é representada uma coordenada (x, y);
- O "jogador1" coloca os navios e, posteriormente, o "jogador2" ataca, trocando a ordem no fim da partida;
- Navios a serem colocados:
    - **1** Porta-aviões (**5** posições cada);
    - **1** Navio-tanque (**4** posições cada);
    - **2** Contratorpedeiros (**3** posições cada);
    - **2** Submarinos (**2** posições cada);
    - **Obs:** A alteração do número e tipo de navíos não deve afetar o funcionamento do programa.
- O jogador que ataca tem, no máximo, 40 jogadas disponíveis;
- O jogo termina quando uma das seguintes condições ocorra:
    - O jogador atacante afunda todos os barcos do seu oponente;
    - O jogador atacante gasta as 40 jogadas disponíveis;
    - **Obs**: Quando o jogo termina, uma mensagem apropriada deve ser exibida indicando que jogador ganhou a partida.

### Colocação e ataque a navios

- As posições que compõem um navio estão conectadas em linha reta;
- Os navios têm de ser colocados na sua totalidade dentro do tabuleiro;
- Os navios não se podem sobrepor;
- Representação de coordenadas:
    - Coordenadas que foram atacadas **com sucesso** são representadas por um asterisco (**\***);
    - Coordenadas que foram atacadas **sem sucesso** são representadas pela letra "**F**";
    - **Obs:** Coordenadas pertencentes a um barco afundado são representadas pela letra "**A**".
- Para cada barco colocado, será adicionado ao vetor "array board" da estrutura "Board", a primeira letra do tipo do barco nas posições que este ocupa:
    - "P" para porta-aviões;
    - "N" para navios-tanque;
    - "C" para contratorpedeiros;
    - "S" para submarinos.
- Quando um navio é afundado, uma mensagem é exibida a informar que tipo de navio afundou;

### Estruturas de dados

- As coordenadas são representadas pela estrutura "Position":
```c=
typedef struct
{
    int x;
    int y;
} Position;
```

- O estado das coordenadas de cada barco é representado pela estrutura "StateCoord":
```c=
typedef struct
{
    int afloat; // Estado da coordenada (0 = afundada).
    Position pos; // Coordenada.
} StateCoord;
```

- Cada barco é representado pela estrutura "Boat":
```c=
typedef struct
{
    int afloat; // Número de posições não afundadas.
    int tSize; // Tamanho do barco.
    StateCoord coord[5]; // Coordenadas do barco (Máx. 5 posições).
    char type; // Caracter que representa o tipo de barco.
} Boat;
```

- O tabuleiro é representado pela estrutura "Board":
```c=
typedef struct
{
    int numBoatsAfloat; // Número de barcos não afundados.
    int numBoats; // Número de barcos colocados.
    Boat boats[B]; // Vetor de barcos do tipo "Boat".
    char board[N][M]; // Matriz que contém a informação de cada posição.
} Board;
```

## Partes do trabalho

### Objetivos e classificações:
- ***Parte 1 (Obrigatória):***
    - Objetivo: Implementação das funções indicadas;
    - Classificação: Total de 15 pontos.
- ***Parte 2 (Facultativa):***
    - Objetivo: Implementação do jogo interativo;
    - Classificação: Total de 5 pontos.
