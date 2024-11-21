#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include "ouri.h"

int board[2][7];
int best_Move[6];
int jogada = 0;
bool endGame = false;

int main(int argc, char *argv[])
{
    for(int i = 0; i < argc; i++) {
        printf("Paramtero %d: %s\n", i, argv[i]);
    }
    if(argc > 1)
    {
        read_File(argv[1]);
    }
    else {
        reset_Board();
    }

    Chose_Mode();
    return 0;
}

void Chose_Mode()
{


    int pVSp = 0;
    while(pVSp != 1 || pVSp != 2)
    {
        printf("Para jogador VS jogador carregue 1, para jogador VS computador carregue 2: ");
        scanf("%d",&pVSp);
        if(pVSp == 1)
        {
            break;
        }
        else if(pVSp == 2)
        {
            break;
        }
    }
    if(pVSp == 1)
    {
        Player_vs_Player();
    }
    else if(pVSp== 2)
    {
        Player_vs_Computer();
    }
    else{
        printf("valor incorreto \n");
        scanf("%d",&pVSp);
    }
}

void Player_vs_Player()
{
        printf("Jogador A VS Jogador B\n");
        while(!endGame)
        {
            printf("JOGADA JOGADOR %c\n",jogada % 2 + 'A');
            print_board(board);
            Player(jogada % 2,board);
            Check_Winners(jogada % 2);
            jogada++;
            
        }
}

void Player_vs_Computer()
{
    printf("Player VS Computador\n");
    print_board(board); 
    while(!endGame)
    {
        printf("JOGADA JOGADOR %c\n",jogada % 2 + 'A');
        if(jogada % 2 == 0)
        {
            Player(jogada % 2,board);
            Check_Winners(jogada % 2,board);
        }
        else{
            Check_Best_Move(board,jogada % 2);
            Check_Winners(jogada % 2);
        }
        jogada++;
        print_board(board);
    }
}

void print_board(int board_[2][7])
{
    printf("|---------   B   ---------|\n");
    printf("|---| 6| 5| 4| 3| 2| 1|---|\n");
    printf("|---|--|--|--|--|--|--|---|\n");
    printf("|   |");
    for(int i = 6; i > 0; i--) {
        if(board_[1][i] <= 9)
        {
            printf(" %d|", board_[1][i]);
        }
        else{
            printf("%d|", board_[1][i]);
        }
    }
    printf("   |\n");
    if(board_[1][0] <= 9)
    {
        printf("|  %d|----------",board_[1][0]);
    }
    else{
        printf("| %d|----------",board_[1][0]);
    }
    if(board_[0][0] <= 9)
    {
        printf("-------|  %d|\n",board_[0][0]);
    }
    else{
        printf("-------| %d|\n",board_[0][0]);
    }
    printf("|   |");
    for(int i = 1; i < 7; i++) {
        if(board_[0][i] <= 9)
        {
            printf(" %d|", board_[0][i]);
        }
        else{
            printf("%d|", board_[0][i]);
        }
    }
    printf("   |\n");
    printf("|---|--|--|--|--|--|--|---|\n");
    printf("|---| 1| 2| 3| 4| 5| 6|---|\n");
    printf("|---------   A   ---------|\n");
    printf("\n");
}

void reset_Board()
{
    printf("Reseting board...\n");
    board[0][0] =  0;
    board[1][0] =  0;
    for(int i = 0; i < 2;i++)
    {
        for(int j = 1;j < 7;j++)
        {
            board[i][j] = 4;
        }
    }
}

void Player(int player, int board_[2][7])
{

    int current_player = player;
    int move_pos;
    printf("Jogador %c: Escolhe onde queres tirar as bolas (1-6): ", player + 'A');
    scanf("%d",&move_pos);
    if(move_pos == 0)
    {
        save_File();
        exit(0);
    }
    Play(current_player,board_,move_pos);

}

void Play(int player,int board_[2][7], int move_pos)
{
    int current_board = player;
    int count = 0;
    int play_without_capt = 0;
    int peaces = board_[current_board][move_pos];
    bool valid = Valid_Play(move_pos,peaces,player,board_);
    if(valid)
    {
        if(peaces != 0)
        {   
            board_[current_board][move_pos] = 0;
            while(peaces > 0)
            {
                if(move_pos == 6)
                {
                    if(current_board == 0)
                    {
                        current_board = 1;
                    }
                    else{
                        current_board = 0;
                    }
                    move_pos = 1;
                    Check_Winners();
                }
                else
                {
                    move_pos++;
                }
                count++;
                //12 peaces rule
                if(count % 12 != 0)
                {
                    board_[current_board][move_pos]++;
                    peaces--;
                }
            }
            //capturar peças
            if(current_board != player)
            {
                if(board_[current_board][move_pos] == 2 || board_[current_board][move_pos] == 3)
                {
                    for(int i = move_pos; i > 0; i--)
                    {
                        if(board_[current_board][i] == 2 || board_[current_board][i] == 3){
                            board_[player][0] += board_[current_board][i];
                            board_[current_board][i] = 0;
                        }
                        else{
                            break;
                        }
                    }
                    play_without_capt = 0;
                }
                else{
                    play_without_capt++;
                }
            }
        }
    }
    else
    {
        jogada--;
        printf("Jogada invalida -> Jogador %c: move %d\n",player + 'A',move_pos);
    }
    if(play_without_capt == 10)
    {
        Check_Winners_from_Move(board_);
    }
}

void Copy_Board(int board_in[2][7],int board_out[2][7])
{
    for(int i = 0; i < 2;i++)
    {
        for(int j = 0; j < 7; j++)
        {
            board_out[i][j] = board_in[i][j];
        }
    }
}

void Check_Best_Move(int board_[2][7], int player)
{
    int best_move_ = -10000;
    int index = 1;
    int copy_B[2][7];
    int other_player;

    if(player == 0)
    {
        other_player = 1;
    }
    else{
        other_player = 0;
    }
    for(int i = 1; i < 7; i++)
    {
        int penalty = 0;
        Copy_Board(board_,copy_B);
        bool valid = Valid_Play(i,copy_B[player][i],player,copy_B);
        if(valid)
        {
            Play(player, copy_B, i);
            int soma_J1 = 0;
            int soma_J2 = 0;
            for(int j = 1; j < 7; j++)
            {
                soma_J1 += copy_B[0][j];
                soma_J2 += copy_B[1][j];

                //penalisa se as casas do jogador tiver 1 ou 2 peças
                if(copy_B[player][j] == 1 || copy_B[player][j] == 2)
                {
                    penalty += 500;
                }

                //benifica se as casas dos outros jogadores tiverem 1 ou 2 peças
                if(copy_B[other_player][j] == 1 || copy_B[other_player][j] == 2)
                {
                    penalty -= 500;
                }
                //benifica se o o outro jogador tiver casas com 0
                if(copy_B[player][j] >= 10)
                {
                    for(int h = 1; h < 7; h++)
                    {
                        if(copy_B[other_player][h] == 0)
                        {
                            penalty += -100;
                        }
                        else
                        {
                            penalty += 600;
                        }
                    }
                }
                if(copy_B[player][j] == 1 || copy_B[player][j] == 0)
                {
                    penalty += -100000  ;
                }
            }
            best_Move[i - 1] = (1000 * (copy_B[player][0]-board[other_player][0])) + (10 * (soma_J2 - soma_J1)) - (penalty * 10);
        }
        else{
            best_Move[i - 1] = -1000;
        }
    }

    for(int i = 0; i < 6; i++)
    {
        if(best_Move[i] > best_move_)
        {
            best_move_ = best_Move[i];
            index = i + 1;
        }
    }

    Play(player,board_,index);
}

void Check_Winners(int player)
{
    int soma;
    int current_player = player; 
    if(board[0][0] >= 25)
    {
        printf("Jogador A ganhou\n");
        endGame = true;
        print_board(board);
        exit(0);
    }
    else if(board[1][0] >= 25)
    {
        printf("jogador B ganhou\n");
        endGame = true;
        print_board(board);
        exit(0);
    }   
}

void Check_Winners_from_Move(int board[2][7])
{
    for(int i = 1; i < 7; i++)
    {
        board[0][0] += board[0][i];
        board[0][i] = 0;
    }
    for(int i = 1; i < 7; i++)
    {
        board[1][0] += board[1][i];
        board[1][i] = 0;
    }
    print_board(board);


    if(board[0][0] > board[1][0])
    {
        printf("PLAYER A GANHOU");
        exit(0);
    }
    else if(board[1][0] > board[0][0])
    {
        printf("PLAYER B GANHOU");
        exit(0);
    }
    else{
        printf("EMPATE");
        exit(0);
    }
}

bool Valid_Play(int move_pos, int peaces,int player,int board[2][7])
{
    bool valid = true;
    int invalid = 0;
    int current_board, soma = 0;
    int other_player;

    // ver se a casa tem 1 ou mais bolas
    if(move_pos > 0 && move_pos < 7)
    {
        if(peaces > 0){valid = true;}
        else{valid = false;}
    }else{valid = false;}

    //saber que jogador esta a jogar
    if(player == 0){other_player = 1;}
    else{other_player = 0;}

    for(int i = 1; i < 7; i++){soma += board[other_player][i];}

    //ver se o outro jogador tem peças em cada casa
    if(soma == 0)
    {
        for(int j = 1; j < 7;j++)
        {
            if(j + board[player][j] >= 7){valid = true; break;}
            else{valid = false;invalid++;}
        }
    }
    if(invalid == 6){Check_Winners_from_Move(board);}
    invalid = 0;

    // ver se existem casa com mais do que 1 peça
    if(board[player][move_pos] == 1)
    {
        for(int i = 1; i <7;i++)
        {
            if(board[player][i] > 1){valid = false;}
        }
    }
    return valid;
}

void save_File(int player)
{
    char data[1000];
    FILE * fPtr;

    printf("Em qual ficheiro queres guardar: ");
    scanf("%s",data);
    printf("A escrever no ficheiro %s\n",data);

    fPtr = fopen(data, "w+");

    if(fPtr == NULL)
    {
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }

    sprintf(data,"%d\n",board[1][0]);
    fputs(data, fPtr);

    for(int i = 6; i > 0; i--)
    {
        sprintf(data,"%d ", board[1][i]);
        fputs(data,fPtr);
    }

    sprintf(data,"\n%d\n",board[0][0]);
    fputs(data, fPtr);

    for(int i = 1; i < 7; i++) {
        sprintf(data,"%d ", board[0][i]);
        fputs(data,fPtr);
    }
    fclose(fPtr);
}

void read_File(char * file_name)
{
    FILE *fPtr;
    char *data;
    size_t len = 0;
    ssize_t read = 0;
    int i = 0;
    int player = 1;

    fPtr = fopen(file_name, "r");

    if(fPtr == NULL)
    {
        printf("Unable to read file.\n");
        exit(EXIT_FAILURE);
    }
    printf("reading file %s\n", file_name);
    char c;
    bool new_number = true;
    do 
    {
        c = (char)fgetc(fPtr);
        int c_int = c - '0';

        if(c_int >= 0 && c_int <= 9)
        {
            new_number = false;
            
            if(i == 7)
            {
                player = 0;
                i = 0;
            }
            if(player == 1 && i != 0)  {board[player][7 - i] = board[player][7 - i] * 10 + c_int;}
            else {board[player][i] = board[player][i] * 10 + c_int;}
        }
        else if(!new_number) {
            i++;
            new_number = true;
        }
    } while(c != EOF);

    printf("------------------------------\n");
    fclose(fPtr);
}