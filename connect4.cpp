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
		board(char usr1, char usr2, char emp)
		{
			let1 = usr1;
			let2 = usr2;
			let_emp = emp;
		}
		void init_board();
		void print_board();
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


int main()
{
	char usr1, usr2,empty;
	
	board new_board('a', 'b', ' ');
	new_board.init_board();
	new_board.print_board();
	return 0;
}
