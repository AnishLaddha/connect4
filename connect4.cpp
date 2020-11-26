/*
 * connect4.cpp
 * Copyright 2020
 */


#include <iostream>
#include <string>

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
		board(char usr_board[6][7])
		{
			let1 = 'x';
			let2 = 'o';
			let_emp = ' ';
			for(int i = 0; i<6; i++)
			{
				for(int j = 0; j<7; j++)
				{
					board_vals[i][j] = usr_board[i][j];
				}
			}
		}
		void init_board();
		void print_board();
		int place_piece(char let, int col);
		void place_piece(char let, int row, int col);
		bool check_col(int col);
		bool check_board();
		void process_play(string data);
		
};



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
			cout<< " " << board_vals[i][j] << " |";
			
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

int board::place_piece(char let, int col)
{
	int row_val;
	for(int i = 5; i>-1; i--)
	{
		if(board_vals[i][col] == ' ')
		{
			row_val = i;
			board_vals[i][col] = let;
			break;
		}
	}
	return row_val;
}

void board::place_piece(char let, int row, int col)
{
	board_vals[row][col] = let;
}

bool board::check_col(int col)
{

	for(int i = 0; i< 6; i++)
	{
		if(board_vals[i][col] == ' '){
			return true;
		}
	}
	return false;
}

bool board::check_board()
{
	for(int i = 0; i <= 6; i++){
		if (board_vals[i][0] == ' '){
			return true;
		}
	}
	return false;
}

bool board::process_play(string data)
{
	char let = data.at(0);
	int row = data.at(1)-'0';
	int col = data.at(2)-'0';
	char status = data.at(3);
	place_piece(let, row, col);
	if(status == '1'){
		print_board();
		cout << "DRAW!!"<<endl;
		return false;
	} else if(status == '2')
	{
		print_board();
		cout << "YOU LOSE!!"<<endl;
		return false;
	}
	return true;
	

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
	board new_board;
	//new_board.init_board();
	new_board.place_piece('x', 3);
	new_board.place_piece('o', 3);
	new_board.place_piece('x', 2);
	
	new_board.print_board();
	return 0;
}
