void Chose_Mode();
void Player_vs_Player();
void Player_vs_Computer();
void reset_Board();
void print_board(int board_[2][7]);
void Check_Winners();
bool Valid_Play(int move_pos, int peaces, int player, int board[2][7]);
void save_File();
void read_File(char * file_name);
void Copy_Board(int board_in[2][7],int board_out[2][7]);
void Player(int player,int board_[2][7]);
void Play(int player,int board[2][7], int move_pos);
void Check_Best_Move(int board[2][7], int player);
void Check_Winners_from_Move(int board[2][7]);