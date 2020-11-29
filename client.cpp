#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
using namespace std;
//Client side
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
		bool board::check_connect_4();
};


int main(int argc, char *argv[])
{
    //we need 2 things: ip address and port number, in that order
    if(argc != 3)
    {
        cerr << "Usage: ip_address port" << endl; exit(0); 
    } //grab the IP address and port number 
    char *serverIp = argv[1]; int port = atoi(argv[2]); 
    //create a message buffer 
    char msg[1500]; 
    //setup a socket and connection tools 
    struct hostent* host = gethostbyname(serverIp); 
    sockaddr_in sendSockAddr;   
    bzero((char*)&sendSockAddr, sizeof(sendSockAddr)); 
    sendSockAddr.sin_family = AF_INET; 
    sendSockAddr.sin_addr.s_addr = 
        inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
    sendSockAddr.sin_port = htons(port);
    int clientSd = socket(AF_INET, SOCK_STREAM, 0);
    //try to connect...
    int status = connect(clientSd,
                         (sockaddr*) &sendSockAddr, sizeof(sendSockAddr));
    if(status < 0)
    {
        cout<<"Error connecting to socket!"<<endl; 
        return 0;
    }

    cout << "Connected to the server!" << endl;
    int bytesRead, bytesWritten = 0;
    struct timeval start1, end1;
    gettimeofday(&start1, NULL);
    board player1_board;
    char status;

    while(1)
    {
        player1_board.print_board();
        if (status == 'L')
        {
            cout << "You Lost!" << endl;
            break;
        }
        else if (player1_board.check_board() == false)
        {
            cout << "Draw" << endl;
            break;
        }
        string data;
        bool temp = false
        while(temp == false)
        {
            cout << " Enter column you want to place piece in>";
            cin>>data;
            if(data == "exit"){
                temp = true;
            }
            int c = stoi(data);
            if(player1_board.check_col(c) == true)
            {
                temp = true;
            }
            else
            {
                cout<< "Invalid, requre reentry"<< endl;
            }
        }

        player1_board.place_piece(player1_board.let1, stoi(data));
        char mes[4];
        memset(&msg, 0, sizeof(msg));//clear the buffer
        if(player1_board.check_connect_4() == true)
        {
            cout << "you won!"<< endl;
            mes[0] = '0';
            mes[1] = '0';
            mes[2] = '0';
            mes[3] = '2';
        }
        
        data = convertToString(mes, sizeof(mes)/sizeof(char))
        memset(&msg, 0, sizeof(msg));//clear the buffer
        strcpy(msg, data.c_str());
        bytesWritten += send(clientSd, (char*)&msg, strlen(msg), 0);
        cout << "Awaiting server response..." << endl;
        memset(&msg, 0, sizeof(msg));//clear the buffer
        bytesRead += recv(clientSd, (char*)&msg, sizeof(msg), 0);
        if(!strcmp(msg, "exit"))
        {
            cout << "Server has quit the session" << endl;
            break;
        }
        bool val = player1_board.process_play(msg)
        if(val == false){
            if(player1_board.check_board()==true){
                status = 'L'
            }
        }
    }
    gettimeofday(&end1, NULL);
    close(clientSd);
    cout << "********Session********" << endl;
    cout << "Bytes written: " << bytesWritten << 
    " Bytes read: " << bytesRead << endl;
    cout << "Elapsed time: " << (end1.tv_sec- start1.tv_sec) 
      << " secs" << endl;
    cout << "Connection closed" << endl;
    return 0;    
}
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