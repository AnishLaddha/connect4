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
//Server side

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
		bool check_connect_4();
		
};

int main(int argc, char *argv[])
{
    //for the server, we only need to specify a port number
    if(argc != 2)
    {
        cerr << "Usage: port" << endl;
        exit(0);
    }
    //grab the port number
    int port = atoi(argv[1]);
    //buffer to send and receive messages with
    char msg[1500];
     
    //setup a socket and connection tools
    sockaddr_in servAddr;
    bzero((char*)&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);
 
    //open stream oriented socket with internet address
    //also keep track of the socket descriptor
    int serverSd = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSd < 0)
    {
        cerr << "Error establishing the server socket" << endl;
        exit(0);
    }
    //bind the socket to its local address
    int bindStatus = bind(serverSd, (struct sockaddr*) &servAddr, 
        sizeof(servAddr));
    if(bindStatus < 0)
    {
        cerr << "Error binding socket to local address" << endl;
        exit(0);
    }
    cout << "Waiting for a client to connect..." << endl;
    //listen for up to 5 requests at a time
    listen(serverSd, 5);
    //receive a request from client using accept
    //we need a new address to connect with the client
    sockaddr_in newSockAddr;
    socklen_t newSockAddrSize = sizeof(newSockAddr);
    //accept, create a new socket descriptor to 
    //handle the new connection with client
    int newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
    if(newSd < 0)
    {
        cerr << "Error accepting request from client!" << endl;
        exit(1);
    }
    cout << "Connected with client!" << endl;
    //lets keep track of the session time
    struct timeval start1, end1;
    gettimeofday(&start1, NULL);
    //also keep track of the amount of data sent as well
    int bytesRead, bytesWritten = 0;
    board player2_board;
    char status;
    while(1)
    {
        //receive a message from the client (listen)
        cout << "Awaiting client response..." << endl;
        memset(&msg, 0, sizeof(msg));//clear the buffer
        bytesRead += recv(newSd, (char*)&msg, sizeof(msg), 0);
        
        if(!strcmp(msg, "exit"))
        {
            cout << "Client has quit the session" << endl;
            break;
        }

        bool val = player2_board.process_play(msg)
        if(val == false){
            if(player2_board.check_board()==true){
                status = 'L'
            }
        }
        player2_board.print_board();
        if (status == 'L')
        {
            cout << "You Lost!" << endl;
            break;
        }
        else if (player2_board.check_board() == false)
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
            if(player2_board.check_col(c) == true)
            {
                temp = true;
            }
            else
            {
                cout<< "Invalid, requre reentry"<< endl;
            }
        }

        player2_board.place_piece(player2_board.let1, stoi(data));
        
        if(player2_board.check_connect_4() == true)
        {
            cout << "you won!"<< endl;
            mes[0] = '0';
            mes[1] = '0';
            mes[2] = '0';
            mes[3] = '2';
        }
        
        data = convertToString(mes, sizeof(mes)/sizeof(char))
        memset(&msg, 0, sizeof(msg)); //clear the buffer
        strcpy(msg, data.c_str());
        if(data == "exit")
        {
            //send to the client that server has closed the connection
            send(newSd, (char*)&msg, strlen(msg), 0);
            break;
        }
        //send the message to client
        bytesWritten += send(newSd, (char*)&msg, strlen(msg), 0);
    }
    
    //we need to close the socket descriptors after we're all done
    gettimeofday(&end1, NULL);
    close(newSd);
    close(serverSd);
    cout << "********Session********" << endl;
    cout << "Bytes written: " << bytesWritten << " Bytes read: " << bytesRead << endl;
    cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec) 
        << " secs" << endl;
    cout << "Connection closed..." << endl;
    return 0;   
}
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

//prints board
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
			break;
		}
	}
	return row_val;
}

//places piece at exact location
void board::place_piece(char let, int row, int col)
{
	board_vals[row][col] = let;
}

//checks for empty spaces in col
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

//checks if there are still empty spaces on board
bool board::check_board()
{
	for(int i = 0; i <= 6; i++){
		if (board_vals[i][0] == ' '){
			return true;
		}
	}
	return false;
}

//temporary play processor, idek
bool board::process_play(string data)
{
	char let = data.at(0);
	int row = data.at(1)-'0';
	int col = data.at(2)-'0';
	char status = data.at(3);
	
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
	place_piece(let, row, col);
	print_board();
	return true;
	

}

