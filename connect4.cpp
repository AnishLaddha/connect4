/*
 * connect4.cpp
 * Copyright 2020  <pi@raspberrypi>
 */


#include <iostream>

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
		void place_piece();
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

void board:: place_piece(char let, int col)
{
	bool flag = false;
	int place;
}

int main()
{
	char temp_board[6][7] = {
		{'x','x','x','x','x','x','x'},
		{'x','x','x','x','x','x','x'},
		{'x','x','x','x','x','x','x'},
		{'x','x','x','x','x','x','x'},
		{'x','x','x','x','x','x','x'},
		{'x','x','x','x','x','x','x'},
	};
	board new_board(temp_board);
	
	new_board.print_board();
	return 0;
}
