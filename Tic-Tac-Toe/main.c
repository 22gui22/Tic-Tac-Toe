#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define MAXCHAR 1000

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"
#define BOLD_ON       "\x1b[1m"


int logincheck = 0;
char nomeglobal[50] = "";
char nomepass[80] = "";
char nomeadversario[50] = "computador";
char jogador1[50] = "";
char jogador2[50] = "";

//Guardar jogos



/////////////////

char casatabuleiro(int i) {
    switch(i) {
        case -1:
            return 'X';
        case 0:
            return ' ';
        case 1:
            return 'O';
    }
}
void espera(int segundos){
	clock_t endwait;
	endwait=clock()+segundos*CLOCKS_PER_SEC;
	while (clock()<endwait);
}
int guardarjogo(int resultado,int player,int tabuleiro[9])
{
    int i=0;
    char str[100]="";
    char *temp[100];
    //nome|password|adversario|resultado|playerx ou 0|0|1|2|3|4|5|6|7|8|
    strcat(str, nomepass);
    strcat(str, "|");
    strcat(str, nomeadversario);
    strcat(str, "|");
    sprintf(temp, "%d", resultado);
    strcat(str, temp);
    strcat(str, "|");
    sprintf(temp, "%d", player);
    strcat(str, temp);
    while(i<9){
        strcat(str, "|");
        sprintf(temp, "%d", tabuleiro[i]);
        strcat(str, temp);
        i++;
    }

    FILE * fp = fopen ("jogos.txt","a+");
    fprintf (fp, "%s\n",str);
    fclose (fp);



}
int lerjogos()
{
    char str[MAXCHAR];
    int i = 0,num;
    char *jogo[15][256];
    const char s[2] = "|";
    char *token;

    FILE * fp = fopen("jogos.txt", "r");
    if (fp == NULL){
        printf("Nao foi possivel abrir o ficheiro dos jogos");
    }
    while (fgets(str, MAXCHAR, fp) != NULL){
        if(strstr(str,nomepass) != NULL){
                /* Vai buscar o primeiro token */
                token = strtok(str, s);
                /* Vai buscar todos os outros tokens */
                i = 0;
                while( token != NULL || i < 14 ) {
                    strcpy(jogo[i], token);
                    i++;
                    token = strtok(NULL, s);
                }

                //gui|22gui22|adversario|1|1|0|0|0|0|0|0|0|0

                printf("%-10s +-------------------------------------------------+\n"," ");
                printf("%-10s %s %-47s %s\n"," ","|"," ","|");
                if (atoi(jogo[4]) == 1){
                    printf("%-10s %-10s %-1s %-8s %-21s %-10s\n"," ","|",jogo[0],"(X)  vs  (O)",jogo[2],"|");
                }else{
                    printf("%-10s %-10s %-1s %-8s %-21s %-10s\n"," ","|",jogo[0],"(O)  vs  (X)",jogo[2],"|");
                }
                printf("%-10s %s %-47s %s\n"," ","|"," ","|");
                printf("%-10s %-20s %c | %c | %-20c %s\n"," ","|",casatabuleiro(atoi(jogo[5])),casatabuleiro(atoi(jogo[6])),casatabuleiro(atoi(jogo[7])),"|");
                printf("%-10s %-19s %-29s %s\n"," ","|","---+---+---","|");
                printf("%-10s %-20s %c | %c | %-20c %s\n"," ","|",casatabuleiro(atoi(jogo[8])),casatabuleiro(atoi(jogo[9])),casatabuleiro(atoi(jogo[10])),"|");
                printf("%-10s %-19s %-29s %s\n"," ","|","---+---+---","|");
                printf("%-10s %-20s %c | %c | %-20c %s\n"," ","|",casatabuleiro(atoi(jogo[11])),casatabuleiro(atoi(jogo[12])),casatabuleiro(atoi(jogo[13])),"|");
                printf("%-10s %s %-47s %s\n"," ","|"," ","|");
                if (atoi(jogo[4]) == 1){
                    if(atoi(jogo[3]) == 1){
                        printf("%-10s %-12s %-2s %-25s %-10s\n"," ","|","Vencedor: ",jogo[2],"|");
                    }
                    if(atoi(jogo[3]) == -1){
                        printf("%-10s %-12s %-2s %-25s %-10s\n"," ","|","Vencedor: ",jogo[0],"|");
                    }
                    if(atoi(jogo[3]) == 0){
                        printf("%-10s %-22s %-26s %-10s\n"," ","|","Empate","|");
                    }
                }
                if (atoi(jogo[4]) == 2){
                    if(atoi(jogo[3]) == -1){
                        printf("%-10s %-12s %-2s %-25s %-10s\n"," ","|","Vencedor: ",jogo[2],"|");
                    }
                    if(atoi(jogo[3]) == 1){
                        printf("%-10s %-12s %-2s %-25s %-10s\n"," ","|","Vencedor: ",jogo[0],"|");
                    }
                    if(atoi(jogo[3]) == 0){
                        printf("%-10s %-22s %-26s %-10s\n"," ","|","Empate","|");
                    }
                }
                printf("%-10s %s %-47s %s\n"," ","|"," ","|");
                printf("%-10s +-------------------------------------------------+\n"," ");

        }
    }
    printf("\n\n");
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s %-10s %-38s %s\n"," ","|","1. Voltar Estatisticas","|");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s %-10s %-38s %s\n"," ","|","2. Voltar ao menu","|");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("\n");
    estat:
    printf("%-10s O que fazer?(1/2)?\n"," ");
    printf("%-10s "," ");
    scanf("%d",&num);

    if (num == 1){
        system("CLS");
        estatisticas();
    }else if (num == 2){
        system("CLS");
        main();
    }else{
        goto estat;
    }

}
void estatisticas() {
    int num,jogos = 0,victorias = 0, derrotas = 0,empates = 0,i = 0,pontos = 0;
    char stri[MAXCHAR];
    char *stats[6][256];
    const char s[2] = "|";
    char *token;




    FILE * fp = fopen("contas.txt", "r");
    if (fp == NULL){
        printf("Nao foi possivel abrir o ficheiro %s","contas.txt");
    }
    while (fgets(stri, MAXCHAR, fp) != NULL){
        if(strstr(stri,nomepass) != NULL){
            /* Vai buscar o primeiro token */
            token = strtok(stri, s);
            /* Vai buscar todos os outros tokens */
            while( token != NULL || i < 5 ) {
                strcpy(stats[i], token);
                i++;
                token = strtok(NULL, s);
            }

            jogos = atoi(stats[2]);
            victorias = atoi(stats[3]);
            derrotas = atoi(stats[4]);
            empates = atoi(stats[5]);
        }
    }
    fclose(fp);


    pontos = (victorias * 3) + empates;



    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s %-14s %-47s %-10s\n"," ","|",BOLD_ON COLOR_CYAN"E S T A T I S T I C A S"COLOR_RESET,"|");
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s %-10s %-1s %-23d %s\n"," ","|",BOLD_ON COLOR_MAGENTA"Jogos Totais: "COLOR_RESET,jogos,"|");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s %-10s %-1s %-26d %s\n"," ","|",BOLD_ON COLOR_GREEN"Victorias: "COLOR_RESET,victorias,"|");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s %-10s %-1s %-27d %s\n"," ","|",BOLD_ON COLOR_RED"Derrotas: "COLOR_RESET,derrotas,"|");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s %-10s %-1s %-28d %s\n"," ","|","Empates: "COLOR_RESET,empates,"|");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s %-10s %-2s %-29d %s\n"," ","|",BOLD_ON COLOR_YELLOW"Pontos: "COLOR_RESET,pontos,"|");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s %-10s %-38s %s\n"," ","|","1. Mais detalhes","|");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s %-10s %-38s %s\n"," ","|","2. Voltar ao menu","|");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("\n");
    estat:
    printf("%-10s O que fazer?(1/2)?\n"," ");
    printf("%-10s "," ");
    scanf("%d",&num);

    if (num == 1){
        system("CLS");
        lerjogos();
    }else if (num == 2){
        system("CLS");
        main();
    }else{
        goto estat;
    }



}
int editstats(int j, int v, int d, int e)
{
    // Nome | Password |J Jogos |V Victorias |D Derrotas |E Empates |F
    // Nome | Password |J0|V0|D0|E0|F
    char stri[MAXCHAR];
    int i = 0;
    char linha[256]="";
    char *stats[6][256];
    const char s[2] = "|";
    char *token;

    FILE * fp = fopen("contas.txt", "r+");
    FILE * fp2 = fopen("contas_temp.txt", "w");
    if (fp == NULL){
        printf("Nao foi possivel abrir o ficheiro %s","contas.txt");
    }
    while (fgets(stri, MAXCHAR, fp) != NULL){
        if(strstr(stri,nomepass) != NULL){
                /* Vai buscar o primeiro token */
                token = strtok(stri, s);
                /* Vai buscar todos os outros tokens */
                while( token != NULL || i < 5 ) {
                    strcpy(stats[i], token);
                    i++;
                    token = strtok(NULL, s);
                }

                int jogos = atoi(stats[2]);
                jogos = jogos + j;
                int victorias = atoi(stats[3]);
                victorias = victorias + v;
                int derrotas = atoi(stats[4]);
                derrotas = derrotas + d;
                int empates = atoi(stats[5]);
                empates = empates + e;

                strcat(linha, stats[0]);
                strcat(linha, "|");
                strcat(linha, stats[1]);
                strcat(linha, "|");
                sprintf(stats[2], "%d", jogos);
                strcat(linha, stats[2]);
                strcat(linha, "|");
                sprintf(stats[3], "%d", victorias);
                strcat(linha, stats[3]);
                strcat(linha, "|");
                sprintf(stats[4], "%d", derrotas);
                strcat(linha, stats[4]);
                strcat(linha, "|");
                sprintf(stats[5], "%d", empates);
                strcat(linha, stats[5]);

                fprintf (fp2, "%s\n",linha);


        }else{
            fprintf (fp2, "%s",stri);

        }

    }

        fclose(fp);
        fclose(fp2);
        remove("contas.txt");
        rename("contas_temp.txt","contas.txt");

}
int login()
{
    char *nome[50];
    char *nomelog[50];
    char *password[30];
    system("CLS");
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s %-22s %-26s %-10s\n"," ","|","Login","|");
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s %s"," ","Nome: ");
    scanf("%s" , nome);
    strcpy(nomelog, nome);
    printf("%-10s %s"," ","Password: ");
    scanf("%s" , password);
    strcat(nome, "|");
    strcat(nome, password);
    strcpy(nomepass, nome);

    FILE * fp;
    char stri[MAXCHAR];
    char* filename = "contas.txt";

    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Nao foi possivel abrir o ficheiro %s",filename);
    }
    while (fgets(stri, MAXCHAR, fp) != NULL){
        if(strstr(stri,nome) != NULL){
        printf("%-10s %s"," ","Login realizado com sucesso");
        logincheck = 1;
        strcpy(nomeglobal, nomelog);
        fclose(fp);
        espera(1);
        system("CLS");
        main();
        }


    }

    fclose(fp);
}
int reg()
{
    // Nome | Password |J Jogos |V Victorias |D Derrotas |E Empates |F
    // Nome | Password |J0|V0|D0|E0|F
    char *nome[50];
    char *password[30];
    char *txt[800];
    system("CLS");
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s %-22s %-26s %-10s\n"," ","|","Registar","|");
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s %s"," ","Nome: ");
    scanf("%s" , nome);
    printf("%-10s %s"," ","Password: ");
    scanf("%s" , password);
    strcat(nome, "|");
    strcat(nome, password);
    strcat(nome, "|0|0|0|0");
    FILE * fp;
       /* open the file for writing*/
       fp = fopen ("contas.txt","a+");

       /* write 1 lines of text into the file stream*/
           fprintf (fp, "%s\n",nome);

       /* close the file*/
       fclose (fp);
       printf("%-10s %s"," ","Registado com sucesso");
       espera(1);
       login();

}
int logreg()
{
    if(logincheck == 0){
        int resposta;
        start:
        system("CLS");
        printf("%-10s +-------------------------------------------------+\n"," ");
        printf("%-10s %-9s %-39s %-10s\n"," ","|","Fazer login(1) ou registar(2)?","|");
        printf("%-10s %-19s %-29s %-10s\n"," ","|","Sair(99)","|");
        printf("%-10s +-------------------------------------------------+\n"," ");
        printf("%-10s "," ");
        scanf("%d" , &resposta);
        if(resposta == 99){
            system("CLS");
            main();
        }
        if(resposta == 2){
            system("CLS");
            reg();
        }
        if(resposta == 1){
            system("CLS");
            login();
        }else{
            goto start;
        }
    }else{

        char res,lixo;
        start2:
        system("CLS");
        printf("%-10s +-------------------------------------------------+\n"," ");
        printf("%-10s %-2s %-24s %-10s\n"," ","|","Ja tem o login feito deseja fazer logout?(s/n)","|");
        printf("%-10s +-------------------------------------------------+\n"," ");
        printf("%-10s "," ");
        scanf("%c%c" ,&lixo, &res);
        if(res == 's'){
            logincheck = 0;
            strcpy(nomeglobal, "");
            strcpy(nomepass, "");
            system("CLS");
            logreg();
        }
        if(res == 'n'){
            system("CLS");
            main();
        }else{
            goto start2;
        }
    }

}
void desenhar(int casa[9]) {
    system("CLS");
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s %-20s %c | %c | %-20c %s\n"," ","|",casatabuleiro(casa[0]),casatabuleiro(casa[1]),casatabuleiro(casa[2]),"|");
    printf("%-10s %-19s %-29s %s\n"," ","|","---+---+---","|");
    printf("%-10s %-20s %c | %c | %-20c %s\n"," ","|",casatabuleiro(casa[3]),casatabuleiro(casa[4]),casatabuleiro(casa[5]),"|");
    printf("%-10s %-19s %-29s %s\n"," ","|","---+---+---","|");
    printf("%-10s %-20s %c | %c | %-20c %s\n"," ","|",casatabuleiro(casa[6]),casatabuleiro(casa[7]),casatabuleiro(casa[8]),"|");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s +-------------------------------------------------+\n"," ");
}

int win(const int tabuleiro[9]) {
    //determines if a player has won, returns 0 otherwise.
    unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i = 0; i < 8; ++i) {
        if(tabuleiro[wins[i][0]] != 0 &&
           tabuleiro[wins[i][0]] == tabuleiro[wins[i][1]] &&
           tabuleiro[wins[i][0]] == tabuleiro[wins[i][2]])
            return tabuleiro[wins[i][2]];
    }
    return 0;
}

int minimax(int tabuleiro[9], int player) {
    //How is the position like for player (their turn) on tabuleiro?
    int winner = win(tabuleiro);
    if(winner != 0) return winner*player;

    int move = -1;
    int score = -2;//Losing moves are preferred to no move
    int i;
    for(i = 0; i < 9; ++i) {//For all moves,
        if(tabuleiro[i] == 0) {//If legal,
            tabuleiro[i] = player;//Try the move
            int thisScore = -minimax(tabuleiro, player*-1);
            if(thisScore > score) {
                score = thisScore;
                move = i;
            }//Pick the one that's worst for the opponent
            tabuleiro[i] = 0;//Reset tabuleiro after try
        }
    }
    if(move == -1) return 0;
    return score;
}

void jogadapc(int tabuleiro[9]) {
    int move = -1;
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i) {
        if(tabuleiro[i] == 0) {
            tabuleiro[i] = 1;
            int tempScore = -minimax(tabuleiro, -1);
            tabuleiro[i] = 0;
            if(tempScore > score) {
                score = tempScore;
                move = i;
            }
        }
    }
    //returns a score based on minimax tree at a given node.
    tabuleiro[move] = 1;
}
void jogadapc2(int tabuleiro[9]) {
    int move = -1;
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i) {
        if(tabuleiro[i] == 0) {
            tabuleiro[i] = -1;
            int tempScore = -minimax(tabuleiro, 1);
            tabuleiro[i] = 0;
            if(tempScore > score) {
                score = tempScore;
                move = i;
            }
        }
    }
    //returns a score based on minimax tree at a given node.
    tabuleiro[move] = -1;
}
void pcestupido2(int tabuleiro[9]) {
    int move = 0;
    do {
    start:
    srand(time(NULL));
    move =rand()%9;
    if(tabuleiro[move] != 0) {
    goto start;
    }
    printf("\n");
    } while (move >= 9 || move < 0 && tabuleiro[move] == 0);
    tabuleiro[move] = -1;
}
void pcestupido(int tabuleiro[9]) {
    int move = 0;
    do {
    start:
    srand(time(NULL));
    move =rand()%9;
    if(tabuleiro[move] != 0) {
    goto start;
    }
    printf("\n");
    } while (move >= 9 || move < 0 && tabuleiro[move] == 0);
    tabuleiro[move] = 1;
}
void jogadaplayer2(int tabuleiro[9]) {
    int move = 0;
    do {
    start:
    printf("\n%s(O) Escolhe a casa ([0..8]) ou sair(99): ",jogador2);
    scanf("%d", &move);
    if(move == 99){
        system("CLS");
        main();
    }
    if(move < 0 || move >8){
        printf("\nValor invalido");
        goto start;
    }
    if(tabuleiro[move] != 0) {
    printf("Casa ja ocupada!");
    goto start;
    }
    printf("\n");
    } while (move >= 9 || move < 0 && tabuleiro[move] == 0);
    tabuleiro[move] = 1;
}
void jogadaplayer(int tabuleiro[9]) {
    int move = 0;
    do {
    start:
    printf("\n%s(X) Escolhe a casa ([0..8]) ou sair(99): ",jogador1);
    scanf("%d", &move);
    if(move == 99){
        system("CLS");
        main();
    }
    if(move < 0 || move >8){
        printf("\nValor invalido");
        goto start;
    }
    if(tabuleiro[move] != 0) {
    printf("Casa ja ocupada!");
    goto start;
    }
    printf("\n");
    } while (move >= 9 || move < 0 && tabuleiro[move] == 0);
    tabuleiro[move] = -1;
}
int jj() {
    char lixo,resposta;
    int tabuleiro[9] = {0,0,0,0,0,0,0,0,0};
    int player=0;
    unsigned turn;
    //computer squares are 1, player squares are -1.
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s %-22s %-26s %-10s\n"," ","|","Jogador1: X","|");
    printf("%-10s %-22s %-26s %-10s\n"," ","|","Jogador2: O","|");
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s %-3s %-45s %-10s\n"," ","|","Queres ser o jogador(1) ou jogador(2)?","|");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s "," ");
    scanf("%d",&player);
    printf("\n");
    if(player == 1){
        strcpy(jogador1, nomeglobal);
        strcpy(jogador2, nomeadversario);
    }else{
        strcpy(jogador1, nomeadversario);
        strcpy(jogador2, nomeglobal);
    }
    if (player == 1){
        for(turn = 0; turn < 9 && win(tabuleiro) == 0; ++turn) {
        if((turn+player) % 2 == 0){
            desenhar(tabuleiro);
            jogadaplayer2(tabuleiro);
        }else {
            desenhar(tabuleiro);
            jogadaplayer(tabuleiro);
        }
        }
    }
    if (player == 2){
        for(turn = 0; turn < 9 && win(tabuleiro) == 0; ++turn) {
        if((turn+player) % 2 == 0){
            desenhar(tabuleiro);
            jogadaplayer(tabuleiro);
        }else {
            desenhar(tabuleiro);
            jogadaplayer2(tabuleiro);
        }
        }
    }
    guardarjogo(win(tabuleiro),player,tabuleiro);
    switch(win(tabuleiro)) {
        case 0:
            desenhar(tabuleiro);
            printf("Empate.\n");
            editstats(1, 0, 0, 1);
            break;
        case 1:
            desenhar(tabuleiro);
            printf("%s Ganhou o jogo!\n",jogador2);
            if (player == 1){
                editstats(1, 0, 1, 0);
            }else{
                editstats(1, 1, 0, 0);
            }
            break;
        case -1:
            desenhar(tabuleiro);
            printf("%s Ganhou o jogo!\n",jogador1);
            if (player == 1){
                editstats(1, 1, 0, 0);
            }else{
                editstats(1, 0, 1, 0);
            }
            break;
    }
    pdnovo:
        printf("Jogar de novo(s/n)?");
        scanf("%c%c",&lixo,&resposta);
        if(resposta == 's'){
            system("CLS");
            adver();
        }
        if(resposta == 'n'){
            system("CLS");
            main();
        }else{
            goto pdnovo;
        }
}
int adver() {
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s %-3s %-45s %-10s\n"," ","|","Como se chama o segundo jogador?","|");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s "," ");
    scanf("%s",&nomeadversario);
    jj();
}
int jcfacil() {
    int tabuleiro[9] = {0,0,0,0,0,0,0,0,0};
    int player=0;
    char resposta,lixo;
    unsigned turn;
    strcpy(nomeadversario, "computador-facil");
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s %-22s %-26s %-10s\n"," ","|","1º Jogador: X","|");
    printf("%-10s %-22s %-26s %-10s\n"," ","|","2º Jogador: O","|");
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s %-3s %-45s %-10s\n"," ","|","Queres comecar em primeiro(1) ou segundo(2)?","|");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s "," ");
    scanf("%d",&player);
    printf("\n");
    if (player == 1){
        for(turn = 0; turn < 9 && win(tabuleiro) == 0; ++turn) {
        if((turn+player) % 2 == 0){
            desenhar(tabuleiro);
            espera(1);
            pcestupido(tabuleiro);
        }else {
            desenhar(tabuleiro);
            jogadaplayer(tabuleiro);
        }
        }
    }
    if (player == 2){
        for(turn = 0; turn < 9 && win(tabuleiro) == 0; ++turn) {
        if((turn+player) % 2 == 0){
            desenhar(tabuleiro);
            espera(1);
            pcestupido2(tabuleiro);
        }else {
            desenhar(tabuleiro);
            jogadaplayer2(tabuleiro);
        }
        }
    }
    guardarjogo(win(tabuleiro),player,tabuleiro);
    switch(win(tabuleiro)) {
        case 0:
            desenhar(tabuleiro);
            printf("Empate!\n");
            editstats(1, 0, 0, 1);
            break;
        case 1:
            desenhar(tabuleiro);
            if (player == 1){
                editstats(1, 0, 1, 0);
                printf("Perdeste!\n");
            }else{
                editstats(1, 1, 0, 0);
                printf("Ganhaste!\n");
            }
            break;
        case -1:
            desenhar(tabuleiro);
            if (player == 1){
                editstats(1, 1, 0, 0);
                printf("Ganhaste!\n");
            }else{
                editstats(1, 0, 1, 0);
                printf("Perdeste!\n");
            }
            break;
    }
        pdnovo:
        printf("Jogar de novo(s/n)?");
        scanf("%c%c",&lixo,&resposta);
        if(resposta == 's'){
            system("CLS");
            jcfacil();
        }
        if(resposta == 'n'){
            system("CLS");
            main();
        }else{
            goto pdnovo;
        }

}
int jcmedia() {
    int tabuleiro[9] = {0,0,0,0,0,0,0,0,0};
    int player=0;
    char resposta,lixo;
    unsigned turn;
    int majog=0;
    srand(time(NULL));
    strcpy(nomeadversario, "computador-medio");
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s %-22s %-26s %-10s\n"," ","|","1º Jogador: X","|");
    printf("%-10s %-22s %-26s %-10s\n"," ","|","2º Jogador: O","|");
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s %-3s %-45s %-10s\n"," ","|","Queres comecar em primeiro(1) ou segundo(2)?","|");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s "," ");
    scanf("%d",&player);
    printf("\n");
    if (player == 1){
        for(turn = 0; turn < 9 && win(tabuleiro) == 0; ++turn) {
        if((turn+player) % 2 == 0){
            desenhar(tabuleiro);
            espera(1);
            if(majog == 0){
                pcestupido(tabuleiro);
                majog = rand()%3;
            }else{
                jogadapc(tabuleiro);
                majog = rand()%3;
            }
        }else {
            desenhar(tabuleiro);
            jogadaplayer(tabuleiro);
        }
        }
    }
    if (player == 2){
        for(turn = 0; turn < 9 && win(tabuleiro) == 0; ++turn) {
        if((turn+player) % 2 == 0){
            desenhar(tabuleiro);
            espera(1);
            if(majog == 0){
                pcestupido2(tabuleiro);
                majog = rand()%3;
            }else{
                jogadapc2(tabuleiro);
                majog = rand()%3;
            }
        }else {
            desenhar(tabuleiro);
            jogadaplayer2(tabuleiro);
        }
        }
    }
    guardarjogo(win(tabuleiro),player,tabuleiro);
    switch(win(tabuleiro)) {
        case 0:
            desenhar(tabuleiro);
            printf("Empate!\n");
            editstats(1, 0, 0, 1);
            break;
        case 1:
            desenhar(tabuleiro);
            if (player == 1){
                editstats(1, 0, 1, 0);
                printf("Perdeste!\n");
            }else{
                editstats(1, 1, 0, 0);
                printf("Ganhaste!\n");
            }
            break;
        case -1:
            desenhar(tabuleiro);
            if (player == 1){
                editstats(1, 1, 0, 0);
                printf("Ganhaste!\n");
            }else{
                editstats(1, 0, 1, 0);
                printf("Perdeste!\n");
            }
            break;
    }
        pdnovo:
        printf("Jogar de novo(s/n)?");
        scanf("%c%c",&lixo,&resposta);
        if(resposta == 's'){
            system("CLS");
            jcfacil();
        }
        if(resposta == 'n'){
            system("CLS");
            main();
        }else{
            goto pdnovo;
        }

}
int jc() {
    int tabuleiro[9] = {0,0,0,0,0,0,0,0,0};
    int player=0;
    char resposta,lixo;
    unsigned turn;
    strcpy(nomeadversario, "computador-dificil");
    //computer squares are 1, player squares are -1.
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s %-22s %-26s %-10s\n"," ","|","1º Jogador: X","|");
    printf("%-10s %-22s %-26s %-10s\n"," ","|","2º Jogador: O","|");
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s %-3s %-45s %-10s\n"," ","|","Queres comecar em primeiro(1) ou segundo(2)?","|");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s "," ");
    scanf("%d",&player);
    printf("\n");
    if (player == 1){
        for(turn = 0; turn < 9 && win(tabuleiro) == 0; ++turn) {
        if((turn+player) % 2 == 0){
            desenhar(tabuleiro);
            espera(1);
            jogadapc(tabuleiro);
        }else {
            desenhar(tabuleiro);
            jogadaplayer(tabuleiro);
        }
    }
    }
    if (player == 2){
        for(turn = 0; turn < 9 && win(tabuleiro) == 0; ++turn) {
        if((turn+player) % 2 == 0){
            desenhar(tabuleiro);
            espera(1);
            jogadapc2(tabuleiro);
        }else {
            desenhar(tabuleiro);
            jogadaplayer2(tabuleiro);
        }
    }
    }
    guardarjogo(win(tabuleiro),player,tabuleiro);
    switch(win(tabuleiro)) {
        case 0:
            desenhar(tabuleiro);
            printf("Empate!\n");
            editstats(1, 0, 0, 1);
            break;
        case 1:
            desenhar(tabuleiro);
            if (player == 1){
                editstats(1, 0, 1, 0);
                printf("Perdeste!\n");
            }else{
                editstats(1, 1, 0, 0);
                printf("Ganhaste!\n");
            }
            break;
        case -1:
            desenhar(tabuleiro);
            if (player == 1){
                editstats(1, 1, 0, 0);
                printf("Ganhaste!\n");
            }else{
                editstats(1, 0, 1, 0);
                printf("Perdeste!\n");
            }
            break;
    }
        pdnovo:
        printf("Jogar de novo(s/n)?");
        scanf("%c%c",&lixo,&resposta);
        if(resposta == 's'){
            system("CLS");
            jc();
        }
        if(resposta == 'n'){
            system("CLS");
            main();
        }else{
            goto pdnovo;
        }

}
int cc() {
    int tabuleiro[9] = {0,0,0,0,0,0,0,0,0};
    int player=0;
    int majog=0;
    char resposta;
    unsigned turn;
    //computer squares are 1, player squares are -1.
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s %-22s %-26s %-10s\n"," ","|","Computador (1): X","|");
    printf("%-10s %-22s %-26s %-10s\n"," ","|","Computador (2): O","|");
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s %-3s %-45s %-10s\n"," ","|","Quem começa primeiro (1) ou (2)?","|");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s "," ");
    scanf("%d",&player);
    printf("\n");
    for(turn = 0; turn < 9 && win(tabuleiro) == 0; ++turn) {
        if((turn+player) % 2 == 0){
            desenhar(tabuleiro);
            if (player == 2 && majog == 0){
                majog = 1;
                espera(1);
                pcestupido(tabuleiro);
            }else{
                espera(1);
                jogadapc(tabuleiro);
            }

        }else {
            desenhar(tabuleiro);
            if (player == 1 && majog == 0){
                majog = 1;
                espera(1);
                pcestupido2(tabuleiro);
            }else{
                espera(1);
                jogadapc2(tabuleiro);
            }

        }
    }
    int resul = win(tabuleiro);
        if (win(tabuleiro) == -1){
            r1:
            desenhar(tabuleiro);
            printf("Ganhou o Computador(1)!\n");
            printf("Jogar de novo?(s/n)");
            scanf("%c",&resposta);
            if (resposta == 's'){
                system("CLS");
                cc();
            }
            if (resposta == 'n'){
                system("CLS");
                main();
            }else{
                goto r1;
            }
            }
        if (win(tabuleiro) == 0){
            r2:
            desenhar(tabuleiro);
            printf("Empate.\n");
            printf("Jogar de novo?(s/n)");
            scanf("%c",&resposta);
            if (resposta == 's'){
                system("CLS");
                cc();
            }
            if (resposta == 'n'){
                system("CLS");
                main();
            }else{
                goto r2;
            }
            }
        if (win(tabuleiro) == 1){
            r3:
            desenhar(tabuleiro);
            printf("Ganhou o Computador(2)!\n");
            printf("Jogar de novo?(s/n)");
            scanf("%c",&resposta);
            if (resposta == 's'){
                system("CLS");
                cc();
            }
            if (resposta == 'n'){
                system("CLS");
                main();
            }else{
                goto r3;
            }
            }

}
int jogadorvspc()
{
    int num;
    system("CLS");
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s %-12s %-36s %-10s\n"," ","|","Escolhe a dificuldade","|");
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s %-10s %-51s %s\n"," ","|",BOLD_ON COLOR_GREEN"1. Facil"COLOR_RESET,"|");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s %-10s %-51s %s\n"," ","|",BOLD_ON COLOR_YELLOW"2. Media"COLOR_RESET,"|");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s %-10s %-51s %s\n"," ","|",BOLD_ON COLOR_RED"3. Dificil"COLOR_RESET,"|");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("\n");
    printf("%-10s Que dificuldade escolhes?(1/2/3)?\n"," ");
    printf("%-10s "," ");
    scanf("%d",&num);
    switch (num)
    {
    case 1:
        system("CLS");
        jcfacil();
        break;
    case 2:
        system("CLS");
        jcmedia();
        break;
    case 3:
        system("CLS");
        jc();
        break;
    default:
        system("CLS");
        jogadorvspc();
        break;
    }

}
int main()
{
    SetConsoleTitle("Jogo do Galo do Guilherme");
    int num;
    system("CLS");
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s %-22s %-39s %-10s\n"," ","|",BOLD_ON COLOR_CYAN"M E N U"COLOR_RESET,"|");
    printf("%-10s +-------------------------------------------------+\n"," ");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s %-10s %-38s %s\n"," ","|","0. Registo / Login","|");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s %-10s %-38s %s\n"," ","|","1. Jogador vs Jogador","|");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s %-10s %-38s %s\n"," ","|","2. Jogador vs Computador","|");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s %-10s %-38s %s\n"," ","|","3. Computador vs Computador","|");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s %-10s %-38s %s\n"," ","|","4. Estatisticas","|");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s %-10s %-38s %s\n"," ","|","5. Fechar o jogo","|");
    printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    printf("%-10s +-------------------------------------------------+\n"," ");
    if(logincheck == 1){
        printf("%-10s %-10s %-1s %-27s %-10s\n"," ","|",BOLD_ON COLOR_GREEN"Bem vindo "COLOR_RESET BOLD_ON COLOR_YELLOW,nomeglobal,COLOR_RESET"|");
        printf("%-10s +-------------------------------------------------+\n"," ");
    }else{
        //printf("%-10s %s %-47s %s\n"," ","|"," ","|");
    }
    //printf("%-10s +-------------------------------------------------+\n"," ");
    tentadenovo:
    printf("\n");
    printf("%-10s O que pretende fazer?(0/1/2/3/4/5)?\n"," ");
    printf("%-10s "," ");
    scanf("%d",&num);
    if (logincheck == 0 && num != 0 && num != 5){
            printf("%-10s Tens que fazer login para jogares\n"," ");
            goto tentadenovo;
    }
    switch (num)
    {
    case 0:
        system("CLS");
        logreg();
        break;
    case 1:
        system("CLS");
        adver();
        break;
    case 2:
        system("CLS");
        jogadorvspc();
        break;
    case 3:
        system("CLS");
        cc();
        break;
    case 4:
        system("CLS");
        estatisticas();
        break;
    case 5:
        system("CLS");
        system("taskkill/IM cb_console_runner.exe");
        main();
        break;
    default:
        system("CLS");
        main();
        break;
    }

    return 0;
}
