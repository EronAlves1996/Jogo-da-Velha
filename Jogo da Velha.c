#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Variáveis globais, representadas no placar, controlam todo o jogo e estão 
visíveis em 95% do jogo */

char Player1[20] = {0}, Player2[20] = {0}, jogada[2] = {0}, 
                                vitoriaUlt[20] = "NINGUEM";

int pontuacao[3] = {0}, velha = 0, rodada = 0;

/* Função para resetar o tabuleiro do jogo.
O tabuleiro do jogo foi idealizado como uma disposição de matrizes do 
caractere 'I' (I maiúsculo). Reset necessário no início e no recomeço de 
rodadas */

void reset(char jg[][3])
{
    int i = 0, j = 0;
    for(i = 0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            jg[i][j] = 'I';
        }
    }
}

/* Função responsável por mostrar o cabeçalho do jogo e o tabuleiro.
O cabeçalho inclui: placar, quantas rodadas se passasaram e último jogador 
vitorioso */

void cabecalho(char jg[][3]){
    system("clear");
    sleep(1);
    int i = 0, j = 0, indice = 0;
    printf("Player\tNome\t\tPontuacao\tJogada\n");
    for(indice=0;indice<2;indice++)
    {
        if(indice == 0){
            printf("%d\t%s\t\t%d\t\t%c\n", indice+1, Player1, pontuacao[indice], 
                                                                jogada[indice]);
        }
        else
        {
            printf("%d\t%s\t\t%d\t\t%c\n", indice+1, Player2, pontuacao[indice],
                                                                jogada[indice]);
        }
    }
    printf("3\tVELHA\t\t%d\n", pontuacao[2]);
    printf("Rodada = %d\n", rodada);
    printf("Vitoria da última rodada = %s", vitoriaUlt);
    printf("\n_______________________________________________\n\n");
    for(i = 0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            printf("%c\t", jg[i][j]);
        }
        printf("\n");
    }
}

/* O jogo da velha possui condição onde nenhum dos jogadores ganha. Essa Função
irá fazer esta verificação todo final de rodada */

int verificavelha(char jg[][3])
{
    int i = 0, j = 0, soma = 0;
    for(i = 0;i<3;i++){
        for(j = 0;j<3;j++)
        {
            if(jg[i][j] == 'I')
            {
                return 0;
            }
        }
    }
    velha = 1;
    return 1;
}

/* Função para verificar vitória de qualquer um dos jogadores. Irá rodar todo final
de rodada */

int verificavitoria(char jg[][3]){
    int i = 0, j = 0;
    for(i = 0;i<3;i++)
    {
        if(jg[i][0] == jg[i][1] && jg[i][1] == jg[i][2] && jg[i][0] != 'I')
        {
            return 1;
        }
    }
    for(j = 0; j<3;j++)
    {
        if(jg[0][j] == jg[1][j] && jg[1][j] == jg[2][j] && jg[0][j] != 'I')
        {
            return 1;
        }
    }
    if((jg[0][0] == jg[1][1] && jg[1][1] == jg[2][2] && jg[0][0] !='I') || 
        (jg[0][2] == jg[1][1] && jg[1][1] == jg[2][0] && jg[0][2] != 'I'))
    {
        return 1;
    }
    else
    {
        return verificavelha(jg);
    }
    return 0;
}

/* Função responsável pelo andamento do jogo, coração de todo este código.
Esta função vai controlar: a atualização do cabeçalho todo final de jogada,
receber as entradas para processar jogadas, verificar se a jogada é permitida, 
rodar as funções de verificação de vitória e velha */

int jogar(char jg[][3], int vez){
    cabecalho(jg);
    int i = 0, j = 0, controle = 0;
    if (vez==0){
        printf("É a vez de %s\n", Player1);
    }
    else
    {
        printf("É a vez de %s\n", Player2);
    }
    do{
        printf("Informe a linha da jogada: ");
        scanf("%d", &i);
        printf("\nInforme a coluna da jogada: ");
        scanf("%d", &j);
        if (jg[i-1][j-1] != 'I' || i>3 || j>3)
        {
            printf("Jogada não permitida! Gentileza jogar novamente\n");
            controle = 1;
        }
        else
        {
            jg[i-1][j-1] = jogada[vez];
            controle = 0;
        }
    }while(controle == 1);
    return verificavitoria(jg);
}

/* Função main, dá start no jogo */

int main()
{
    /* Aqui declarei o esqueleto do tabuleiro como matriz 3 x 3 e algumas
    variáveis de controle */
    
    char jogo[3][3]={0};
    int vitoria = 0, vez = 0, aux = 0;
    
    /* Boas vindas e instruções do jogo */
    
    printf("Bem vindo ao jogo da velha!\n");
    printf("Neste jogo, ganha quem vencer cinco rodadas, ou se encerra se der ");
    printf("velha 5 vezes!");
    sleep(2);
    
    /* Inserção do nome dos jogadores */
    
    printf("\nEste é um jogo para dois jogadores, por isso, insira o nome do ");
    printf("primeiro jogador: ");
    sleep(2);
    setbuf(stdin, NULL);
    fgets(Player1, 20, stdin);
    Player1[strcspn(Player1, "\n")] = 0;
    printf("Insira o nome do segundo jogador: ");
    setbuf(stdin, NULL);
    fgets(Player2, 20, stdin);
    Player2[strcspn(Player2, "\n")] = 0;
    
    /* Aqui, cada jogador deve escolher sua 'peça' para fazer sua jogada.
    Foram utilizadas as peças clássicas do jogo da velha, pretendo mudar isso.
    A estrutura de repetição e o switch case só foram colocados para cercar erros */
    
    printf("%s, Escolha as opções abaixo para representar suas ", Player1);
    printf("jogadas\n 1 - X \n 2 - O\n");
    do{
        scanf("%d", &aux);
        switch(aux){
            case 1:
                jogada[0] = 'X';
                jogada[1] = 'O';
                break;
            case 2:
                jogada[0] = 'O';
                jogada[1] = 'X';
                break;
            default:
                printf("Erro!!, gentileza inserir novamente!!!\n");
        }
    }while(aux!=1 && aux!=2);
    
    /* A partir daqui o jogo se inicia e se volta em loop até acabar. 
    O jogo só vai acabar no momento que um dos jogadores fizer 5 pontos ou se 
    der velha 5 vezes */
    
    while(pontuacao[0] != 5 || pontuacao[1] != 5 || pontuacao[3] != 5){
        reset(jogo);
        while(vitoria==0){
            if(vez==0){
                vitoria = jogar(jogo, vez);
                vez = 1;
            }
            else
            {
                vitoria = jogar(jogo, vez);
                vez = 0;
            }
        }
        if(velha == 1){
            system("clear");
            printf("Esse jogo deu velha!");
            pontuacao[3]++;
            velha = 0;
        }
        else
        {
            switch(vez)
            {
                case 1:
                    printf("\n%s venceu esta rodada!", Player1);
                    pontuacao[0]++;
                    strcpy(vitoriaUlt, Player1);
                    break;
                case 0:
                    printf("\n%s venceu esta rodada!", Player2);
                    pontuacao[1]++;
                    strcpy(vitoriaUlt, Player2);
                    break;
                default:
                    printf("erro!!!");
            }
        }
        sleep(2);
        rodada++;
        vitoria = 0;
    }
}










