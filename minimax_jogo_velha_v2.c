/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <iostream>
using namespace std;

struct Move 
{ 
	int row, col; 
}; 

char adversary = 'x', player = 'o'; 

// This function returns true if there are moves 
// remaining on the board. It returns false if 
// there are no moves left to play. 
bool isMovesLeft(char board[3][3]) 
{ 
	for (int i = 0; i<3; i++) 
		for (int j = 0; j<3; j++) 
			if (board[i][j]=='_') 
				return true; 
	return false; 
} 


int evaluate(char b[3][3]) 
{ 
	// Checking for Rows (victory). 
	for (int row = 0; row<3; row++) 
	{ 
		if (b[row][0]==b[row][1] && 
			b[row][1]==b[row][2]) 
		{ 
			if (b[row][0]==adversary) 
				return +10; 
			else if (b[row][0]==player) 
				return -10; 
		} 
	} 

	// Checking for Columns (victory). 
	for (int col = 0; col<3; col++) 
	{ 
		if (b[0][col]==b[1][col] && 
			b[1][col]==b[2][col]) 
		{ 
			if (b[0][col]==adversary) 
				return +10; 

			else if (b[0][col]==player) 
				return -10; 
		} 
	} 

	// Checking for Diagonals (victory). 
	if (b[0][0]==b[1][1] && b[1][1]==b[2][2]) 
	{ 
		if (b[0][0]==adversary) 
			return +10; 
		else if (b[0][0]==player) 
			return -10; 
	} 

	if (b[0][2]==b[1][1] && b[1][1]==b[2][0]) 
	{ 
		if (b[0][2]==adversary) 
			return +10; 
		else if (b[0][2]==player) 
			return -10; 
	} 

	// Else if none of them have won then return 0 
	return 0; 
} 

// This is the minimax function. It considers all 
// the possible ways the game can go and returns 
// the value of the board 
int minimax(char board[3][3], int depth, bool isMax) 
{ 
	int score = evaluate(board); 

	// If Maximizer has won the game return his/her 
	// evaluated score 
	if (score == 10) 
		return score; 

	// If Minimizer has won the game return his/her 
	// evaluated score 
	if (score == -10) 
		return score; 

	// If there are no more moves and no winner then 
	// it is a tie 
	if (isMovesLeft(board)==false) 
		return 0; 

	// If this maximizer's move 
	if (isMax) 
	{ 
		int best = -1000; 

		// Traverse all cells 
		for (int i = 0; i<3; i++) 
		{ 
			for (int j = 0; j<3; j++) 
			{ 
				// Check if cell is empty 
				if (board[i][j]=='_') 
				{ 
					// Make the move 
					board[i][j] = adversary; 

					// Call minimax recursively and choose 
					// the maximum value 
					best = max( best, 
						minimax(board, depth+1, !isMax) ); 

					// Undo the move 
					board[i][j] = '_'; 
				} 
			} 
		} 
		return best; 
	} 

	// If this minimizer's move 
	else
	{ 
		int best = 1000; 

		// Traverse all cells 
		for (int i = 0; i<3; i++) 
		{ 
			for (int j = 0; j<3; j++) 
			{ 
				// Check if cell is empty 
				if (board[i][j]=='_') 
				{ 
					// Make the move 
					board[i][j] = player; 

					// Call minimax recursively and choose 
					// the minimum value 
					best = min(best, 
						minimax(board, depth+1, !isMax)); 

					// Undo the move 
					board[i][j] = '_'; 
				} 
			} 
		} 
		return best; 
	} 
} 

// This will return the best possible move for the adversary 
Move findBestMove(char board[3][3]) 
{ 
	int bestVal = -1000; 
	Move bestMove; 
	bestMove.row = -1; 
	bestMove.col = -1; 

	// Traverse all cells, evaluate minimax function for 
	// all empty cells. And return the cell with optimal 
	// value. 
	for (int i = 0; i<3; i++) 
	{ 
		for (int j = 0; j<3; j++) 
		{ 
			// Check if cell is empty 
			if (board[i][j]=='_') 
			{ 
				// Make the move 
				board[i][j] = adversary; 

				// compute evaluation function for this 
				// move. 
				int moveVal = minimax(board, 0, false); 

				// Undo the move 
				board[i][j] = '_'; 

				// If the value of the current move is 
				// more than the best value, then update 
				// best/ 
				if (moveVal > bestVal) 
				{ 
					bestMove.row = i; 
					bestMove.col = j; 
					bestVal = moveVal; 
				} 
			} 
		}
	} 

	//printf("Value of the best Move : %d\n\n", 
	//		bestVal); 

	return bestMove; 
}


void showBoard(char board_s[3][3])
{
        	for (int i = 0; i<3; i++) 
        	{ 
        		for (int j = 0; j<3; j++) 
        		{
        		    if (j==0){
        		        printf("{ %c , ", board_s[i][j]);
        		    }
        		    if (j==1){
        		        printf(" %c , ", board_s[i][j]);
        		    }
        		    if (j==2){
        		        printf(" %c } \n", board_s[i][j]);
        		    }
        		}
        	}
}



// Main Code
int main() 
{ 
	char board[3][3] = 
	{ 
		{ '_', '_', '_' }, 
		{ '_', '_', '_' }, 
		{ '_', '_', '_' } 
	};
	
	int l, c, empty_cont=-1, computer_row=-1, computer_col=-1;
	
	while (empty_cont != 0)
	{
	        
	        // Board presentation
	        showBoard(board);
            usleep(2000000);
	        
	        // Player data entry
	        cout << "\n\n********* You **********\n";
        	cout << "Type the COL:";
        	cin >> c;
        	cout << "Type the ROW:";
        	cin >> l;     
        	cout << "************************\n";
        	usleep(1000000);
        	std::cout << "\033c";
        	
        	l = l-1;
        	c = c-1;
        	
	        // Board filling
        	for (int k = 0; k<3; k++) 
        	{ 
        		for (int m = 0; m<3; m++) 
        		{
        		    if (k == l && m == c)
        		    {
        		        board[k][m] = 'o';
        		    }
        		}
        	}
        	
        	// Board presentation
            showBoard(board);
            usleep(2000000);
            std::cout << "\033c";
            
        	empty_cont = 0;
			for (int k = 0; k<3; k++) 
        	{ 
        		for (int m = 0; m<3; m++) 
        		{
        		    if (board[k][m]=='_')
        		    {
        		        empty_cont = empty_cont + 1;
        		    }
        		}
        	}
        	
        	if (empty_cont != 0)
        	{
        	        Move bestMove = findBestMove(board);
        	        computer_row = bestMove.row+1;
        	        computer_col = bestMove.col+1;
        	        
        	        // Computer action
                    printf("####### Computer #######\n");
        	        printf("COL: %d ", computer_col);
        	        printf("ROW: %d \n", computer_row);
        			printf("########################\n");
        			usleep(2000000);
        			std::cout << "\033c";
        			
        			// Board filling
        			for (int k = 0; k<3; k++) 
                	{ 
                		for (int m = 0; m<3; m++) 
                		{
                		    if (k == bestMove.row && m == bestMove.col)
                		    {
                		        board[k][m] = 'x';
                		    }
                		}
                	}
                	
        	}
        	
    
	}
	
    usleep(10000000);
		
    return 0; 
} 


