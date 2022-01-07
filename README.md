# Trabalho Prático - Programação

## Hiperligações essenciais
- [Enunciado](https://moodle.ubi.pt/pluginfile.php/531717/mod_resource/content/1/BatalhaNaval.pdf);
- [Código base](https://moodle.ubi.pt/pluginfile.php/531716/mod_resource/content/1/BatalhaNaval.c);
- [Repositório do trabalho]().

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
