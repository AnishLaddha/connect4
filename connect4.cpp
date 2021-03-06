/*
 * connect4.cpp
 * Copyright 2020
 */


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class board
{
	public:
		char let1;
		char let2;
		char let_emp;
		char board_vals[6][7];
		
		board()
		{
			let1 = 'x';
			let2 = 'o';
			let_emp = ' ';
			init_board();
		}
		// board(char usr_board[6][7])
		// {
		// 	let1 = 'x';
		// 	let2 = 'o';
		// 	let_emp = ' ';
		// 	for(int i = 0; i<6; i++)
		// 	{
		// 		for(int j = 0; j<7; j++)
		// 		{
		// 			board_vals[i][j] = usr_board[i][j];
		// 		}
		// 	}
		// }
		void init_board();
		void print_board();
		void print_board2();
		int place_piece(char let, int col);
		void place_piece(char let, int row, int col);
		bool check_col_emp(int col);
		bool check_board();
		bool check_win(int row, int col);
		bool check_row(int row);
		bool check_col(int col);
		bool check_diag(int row, int col);
		bool check_forward_diag(int row, int col);
		bool check_backward_diag(int row, int col);
};


//initializes board
void board::init_board()
{
	int i, j = 0;
	int row =6;
	int col = 7;
	
	for(i = 0; i<row;i++)
	{
		for(j = 0; j<col; j++)
		{
			board_vals[i][j] = let_emp;
		}
	}
}

//prints board, num above
void board::print_board()
{
	int i, j = 0;
	int row =6;
	int col = 7;
	
	for(i = 0; i<row;i++)
	{
		if(i ==0)
		{
			cout<< " ";
			for(j=0; j<col; j++)
			{
				cout<< "   "<< j+1<< "";
			}
			cout<< endl;
			cout << "  -";
			for(j=0; j<col; j++)
			{
				cout<< "----";
			}
			cout<< endl;
		}
		for(j = 0; j<col; j++)
		{
			if(j == 0)
			{
				cout << i+1<< " |";
			}
			if(board_vals[i][j] == 'x')
			{
				cout<< " " <<"\033[1;31m"<< board_vals[i][j] << "\033[0m"<< " |";
			} else if(board_vals[i][j] == 'o')
			{
				cout<< " " <<"\033[1;33m"<< board_vals[i][j] << "\033[0m"<< " |";
			} else
			{
				cout<< " " << board_vals[i][j] << " |";
			}
			
			
			
		}
		cout<< endl;
		cout << "  -";
		for(j = 0; j< col; j++)
		{
			cout<< "----";		
		}
		cout << endl;
	}
}

//prints board, num under
void board::print_board2()
{
	int i, j = 0;
	int row =6;
	int col = 7;
	
	for(i = 0; i<row;i++)
	{
		if(i==0)
		{
			cout<<"  ";
			for(j=0; j<col; j++)
			{
				cout<< "----";
			}
			cout<<"-"<<endl;

		}
		for(j = 0; j<col; j++)
		{
			if(j == 0)
			{
				cout << i+1<< " |";
			}
			cout<< " " << board_vals[i][j] << " |";
			
		}
		cout<< endl;
		cout << "  -";
		for(j = 0; j< col; j++)
		{
			cout<< "----";		
		}
		cout << endl;
		if(i ==row-1)
		{
			cout<< " ";
			for(j=0; j<col; j++)
			{
				cout<< "   "<< j+1<< "";
			}
			cout<< endl;
			

			
		}
	}
}
//places peice within a column
int board::place_piece(char let, int col)
{
	int row_val;
	for(int i = 5; i>-1; i--)
	{
		if(board_vals[i][col] == ' ')
		{
			row_val = i;
			board_vals[i][col] = let;
			return row_val;

		}
	}
	return 0;
}

//places piece at exact location
void board::place_piece(char let, int row, int col)
{
	board_vals[row][col] = let;
}

//checks for empty spaces in col
bool board::check_col_emp(int col)
{

	for(int i = 0; i< 6; i++)
	{
		if(board_vals[i][col] == ' '){
			return true;
		}
	}
	return false;
}

//checks if there are still empty spaces on board
bool board::check_board()
{
	for(int i = 0; i <= 6; i++){
		if (board_vals[0][i] == ' '){
			return true;
		}
	}
	return false;
}

bool board::check_win(int row, int col)
{
	
	return (check_row(row) || check_col(col) || check_diag(row, col));
}
bool board::check_row(int row)
{
	
	char val = board_vals[row][0];
	int count = 0;
	for(int i=0; i<7;i++)
	{	
		
		if(val == board_vals[row][i] && val != ' ')
		{
			count++;
		}
		else
		{
			val = board_vals[row][i];
			count=1;
		}
		if(count==4)
		{
			return true;
		}
	}
	return false;
}
bool board::check_col(int col)
{
	char val = board_vals[0][col];
	int count = 0;
	for(int i=0; i<7;i++)
	{
		if(val == board_vals[i][col] && val != ' ')
		{
			count++;
		}
		else
		{
			val = board_vals[i][col];
			count=1;
		}
		if(count==4)
		{
			return true;
		}
	}
	return false;
}
bool board::check_diag(int row, int col)
{
	
	return (check_forward_diag(row, col) || check_backward_diag(row,col));
}
bool board::check_backward_diag(int row, int col)
{
	vector<char> backward_bottom;
	int i = row;
	int j = col;
	while(i < 6 && j <7)
	{
		backward_bottom.push_back(board_vals[i][j]);
		i++;
		j++;
	}
	
	
	vector<char> backward_top;
	i = row;
	j = col;
	while(i>=0 && j>= 0)
	{
		backward_top.push_back(board_vals[i][j]);
		i--;
		j--;
	}
	reverse(backward_top.begin(), backward_top.end());
	vector<char> backward;
	backward.reserve(backward_top.size()+backward_bottom.size());
	backward.insert(backward.end(), backward_top.begin(), backward_top.end());
	backward.insert(backward.end(), backward_bottom.begin(), backward_bottom.end());
	char val = backward[0];
	int count=0;
	for(int a = 0; a<backward.size(); a++)
	{
		if(val==backward[a] && val!=' ')
		{
			count++;
		}
		else
		{
			val = backward[a];
			count = 1;
		}
		if(count == 5)
		{
			return true;
		}
	}
	
	return false;
}
bool board::check_forward_diag(int row, int col)
{
	vector<char> forward_top;
	int i = row;
	int j = col;
	while(i>=0 && j<7)
	{
		forward_top.push_back(board_vals[i][j]);
		i--;
		j++;
	}
	
	vector<char> forward_bottom;
	i=row;
	j=col;
	while(i<6 && j>=0)
	{
		forward_bottom.push_back(board_vals[i][j]);
		i++;
		j--;
	}
	reverse(forward_bottom.begin(), forward_bottom.end());
	vector<char> forward;
	forward.reserve(forward_top.size()+forward_bottom.size());
	forward.insert(forward.end(), forward_bottom.begin(), forward_bottom.end());
	forward.insert(forward.end(), forward_top.begin(), forward_top.end());
	char val = forward[0];
	int count = 0;
	for(int a=0; a<forward.size();a++)
	{
		if(val == forward[a] && val!=' ')
		{
			count++;
		}
		else
		{
			val = forward[a];
			count =1;
		}
		if(count == 5)
		{
			return true;
		}
		cout<<count<< endl;
	}
	
	return false;
}

void Clear()
{
	system("clear");
}

void game()
{
	int usr_col;
	int usr_row;
	Clear();
	cout<<"Welcome to Connect4. Player 1 will be x, and Player 2 will be o."<< endl;
	bool col_works = false;
	board game_board;
	game_board.init_board();
	bool game_cont = true;
	char game_stat;
	bool first = true;
	//game stat: 1 - p1 win; 2 - p2 win; d - draw;
	while(game_cont == true){
		if(first)
		{
			first = false;
		}
		else
		{
			Clear();
		}
		
		game_board.print_board();
		col_works=false;
		while(!col_works){
			cout << "Player 1: Enter a valid column: ";
			while (!(cin >> usr_col))
			{
				cout << "Wrong input. Please, try again: ";
				cin.clear();
			}
			usr_col--;
			if(game_board.check_col_emp(usr_col))
			{
				col_works=true;
			}
		}
		
		usr_row = game_board.place_piece(game_board.let1, usr_col);
		if (game_board.check_win(usr_row, usr_col))
		{
			game_stat = '1';
			game_cont = false;
			break;
		}

		if(!game_board.check_board())
		{
			game_stat = 'd';
			game_cont = false;
			break;
		}

		Clear();

		game_board.print_board();
		col_works=false;
		while(!col_works){
			cout << "Player 2: Enter a valid column: ";
			while (!(cin >> usr_col))
			{
				cout << "Wrong input. Please, try again: ";
				cin.clear();
			}
			usr_col--;
			if(game_board.check_col_emp(usr_col))
			{
				col_works=true;
			}
		}
		usr_row = game_board.place_piece(game_board.let2, usr_col);
		if (game_board.check_win(usr_row, usr_col))
		{
			game_stat = '2';
			game_cont = false;
			break;
		}
		if(!game_board.check_board())
		{
			game_stat = 'd';
			game_cont = false;
			break;
		}
	}
	Clear();
	game_board.print_board();
	if(game_stat == '1')
	{
		cout <<"\033[1;31m" <<"Player 1 wins!"<< "\033[0m\n";
	}
	else if(game_stat == '2')
	{
		cout<< "\033[1;33m"<< "Player 2 wins!" << "\033[0m\n";
	}
	else
	{
		cout<< "Draw!"<<endl;
	}

}

int main()
{
	// char temp_board[6][7] = {
	// 	{'x','x','x','x','x','x','x'},
	// 	{'x','x','x','x','x','x','x'},
	// 	{'x','x','x','x','x','x','x'},
	// 	{'x','x','x','x','x','x','x'},
	// 	{'x','x','x','x','x','x','x'},
	// 	{'x','x','x','x','x','x','x'},
	// };
	// board new_board;
	// new_board.init_board();
	// new_board.place_piece('x', 3);
	// new_board.place_piece('o', 3);
	// new_board.place_piece('x', 2);
	
	// new_board.print_board();

	
	char cont='y';
	while(cont=='y'||cont == 'Y')
	{
		
		game();
		cout<< "Play Again? (Y/N)?: ";
		cin>>cont;
	}
	

	return 0;
}
