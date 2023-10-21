#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <stdio.h>
#include <stdlib.h>
#include "TicTacToe.h"

static const uint16 Win[8]={14,112,146,168,292,546,584,896};//when X and O are converted from binary to decimal, these are the numbers we get in the cases of a win
static uint16 X,O; //two variables whose bits represent the moves of player 1 and player 2 respectively


void TTT_InitiateGame(void)
{
	X=0;
	O=0;
	uint8 GM;
	system("cls");
	printf("\n\t----Welcome to Tic Tac Toe----\n\n");
	printf("*************\n*How to play*\n*************\n1)First choose gamemode.\n2)On your turn click the number on your numpad corresponding to the space you want to place your X or O sign on.");
	printf("\n\nWhat each number on your numpad corresponds to in the game can be seen here:\n");
	printf("\n\t\t 7 | 8 | 9 \n\t\t-----------\n\t\t 4 | 5 | 6 \n\t\t-----------\n\t\t 1 | 2 | 3 \n");
	printf("\n[Click 1 for single player or 2 for multiplayer]\n");
	scanf("%d",&GM);
	while((GM != 1) && (GM != 2))
	{
		printf("Invalid input!-\n[Click 1 for single player or 2 for multiplayer]\n");
		scanf("%d",&GM);
	}
	if(GM==1)
		TTT_SinglePlayer();
	else
		TTT_MultiPlayer();
	
}

static void TTT_SinglePlayer(void)//Single player(X) vs computer(O)
{
	system("cls");
	printf("\n\n\t\t   |   |   \n\t\t-----------\n\t\t   |   |   \n\t\t-----------\n\t\t   |   |   \n");
	uint8 turn=1;//keeps track of turn
	uint8 state;
	uint8 place;
	uint8 corners=0;
	do
	{//alternate between player 1 and 2
		if(turn==1){//human plays first, their sign is X
			printf("\nPlayer 1's turn [X]\n[please choose where you want to play using numpad]\n");
			scanf("%d",&place);
			if(place==0)
			{
				printf("Game aborted\n");
				printf("\n\tPlay again ?[y/n]\n");
				scanf(" %c",&state);
				if(state == 'y')
				{
					TTT_InitiateGame();
				}
				else
				{
					TTT_Quit();
					return;
				}
				
				
			}
			while((place<=0) || (place > SIZE))
			{
				printf("Invalid input!\n[please choose where you want to play using numpad]\n");
				scanf("%d",&place);

			}
			while((GET_BIT(X,place)) || (GET_BIT(O,place)))
			{
				printf("Someone already played in this place, choose a free space to continue!\n[please choose where you want to play using numpad]\n");
				scanf("%d",&place);
			}
			SET_BIT(X,place);
			turn=2;
		}
		else{//AI plays second, their sign is O
			printf("\nAI's turn[O]\n");
			uint8 maxcorners=2;
			place=TTT_IsAboutToWin();
			if( place!=0 )
			{
				SET_BIT(O,place);
				
			}
			else
			{
			// two different algorithms for trying to win, 
			// depending on whether or not the centre place is busy or not
			if(!GET_BIT(X,5)) //algorithm 1 in case centre place is free
			{
				if(GET_BIT(O,5))//if ai already played the centre in a previous turn
				{//make sure human isn't about to win then start looking for free corner
					if(corners<maxcorners)
					{
						if( !( GET_BIT(X,1)||GET_BIT(O,1) ) )
						{
							SET_BIT(O,1);
							corners++;
						}
						else if( !( GET_BIT(X,3)||GET_BIT(O,3) ) )
						{
							SET_BIT(O,3);
							corners++;
						}	
						else if( !( GET_BIT(X,7)||GET_BIT(O,7) ) )
						{
							SET_BIT(O,7);
							corners++;
						}	
						else if( !( GET_BIT(X,9)||GET_BIT(O,9) ) )
						{
							SET_BIT(O,9);
							corners++;
						}	
					}
				}
				else //if ai hasn't played the centre yet
				{
					SET_BIT(O,5);
				}
			}
			else //algorithm 2: in case human has already used the centre spot
			{
				maxcorners=3;
				if(corners<maxcorners)
					{
						if( !( GET_BIT(X,1)||GET_BIT(O,1) ) )
						{
							SET_BIT(O,1);
							corners++;
						}
						else if( !( GET_BIT(X,3)||GET_BIT(O,3) ) )
						{
							SET_BIT(O,3);
							corners++;
						}	
						else if( !( GET_BIT(X,7)||GET_BIT(O,7) ) )
						{
							SET_BIT(O,7);
							corners++;
						}	
						else if( !( GET_BIT(X,9)||GET_BIT(O,9) ) )
						{
							SET_BIT(O,9);
							corners++;
						}	
					}
				
			}
			
			
			turn=1;
		}
		}
		TTT_Display();
	}while((TTT_GameState()==0));
	TTT_Display();
	state=TTT_GameState();
	
	switch(state)
	{
		case 1: printf("Player 1 has won the game !\n"); break;
		case 2: printf("Player 2 has won the game !\n"); break;
		case 3: printf("The game has reached a draw, nobody has won :S\n"); break;
	}
	
	printf("\n\tPlay again ?[y/n]\n");
	scanf(" %c",&state);
	if(state == 'y')
		TTT_InitiateGame();
	else
		TTT_Quit();
	
	
}

static void TTT_MultiPlayer(void)//Multiplayer: Player 1 vs Player 2 (BOTH HUMANS)
{
	system("cls");
	printf("\n\n\t\t   |   |   \n\t\t-----------\n\t\t   |   |   \n\t\t-----------\n\t\t   |   |   \n");
	uint8 turn=1;//keeps track of turn
	uint8 state;
	uint8 place;
	do
	{//alternate between player 1 and 2
		if(turn==1){
			printf("\nPlayer 1's turn [X]\n[please choose where you want to play using numpad]\n");
			scanf("%d",&place);
			if(place==0)
			{
				printf("Game aborted\n");
				printf("\n\tPlay again ?[y/n]\n");
				scanf(" %c",&state);
				if(state == 'y')
				{
					TTT_InitiateGame();
				}
				else
				{
					TTT_Quit();
					return;
				}
				
				
			}
			while((place<=0) || (place > SIZE))
			{
				
				printf("Invalid input!\n[please choose where you want to play using numpad]\n");
				scanf("%d",&place);

			}
			while((GET_BIT(X,place)) || (GET_BIT(O,place)))
			{
				printf("Someone already played in this place, choose a free space to continue!\n[please choose where you want to play using numpad]\n");
				scanf("%d",&place);
			}
			SET_BIT(X,place);
			turn=2;
		}
		else{
			printf("\nPlayer 2's turn[O]\n[please choose where you want to play using numpad]\n");
			scanf("%d",&place);
			if(place==0)
			{
				printf("Game aborted\n");
				printf("\n\tPlay again ?[y/n]\n");
				scanf(" %c",&state);
				if(state == 'y')
				{
					TTT_InitiateGame();
				}
				else
				{
					TTT_Quit();
					return;
				}
			}
			while((place<=0) || (place > SIZE))
			{
				printf("Invalid input!\n[please choose where you want to play using numpad]\n");
				scanf("%d",&place);
			}
			while((GET_BIT(X,place)) || (GET_BIT(O,place)))
			{
				printf("Someone already played in this place, choose a free space to continue!\n[please choose where you want to play using numpad]\n");
				scanf("%d",&place);
			}
			SET_BIT(O,place);
			turn=1;
		}
		TTT_Display();
	}while((TTT_GameState()==0));
	TTT_Display();
	state=TTT_GameState();
	
	switch(state)
	{
		case 1: printf("Player 1 has won the game !\n"); break;
		case 2: printf("Player 2 has won the game !\n"); break;
		case 3: printf("The game has reached a draw, nobody has won :S\n"); break;
	}
	
	printf("\n\tPlay again ?[y/n]\n");
	scanf(" %c",&state);
	if(state == 'y')
		TTT_InitiateGame();
	else
		TTT_Quit();
	
	
	
}



static void TTT_Display(void)
{
	system("cls");
	printf("Click 0 at any time to abort current game\n");
	printf("\n\t\t %c | %c | %c \n\t\t-----------",TTT_XorO(7),TTT_XorO(8),TTT_XorO(9));
	printf("\n\t\t %c | %c | %c \n\t\t-----------",TTT_XorO(4),TTT_XorO(5),TTT_XorO(6));
	printf("\n\t\t %c | %c | %c \n",TTT_XorO(1),TTT_XorO(2),TTT_XorO(3));
}

static void TTT_Quit(void)
{
	system("cls");
	printf("\n\t----Thank you for playing Tic Tac Toe----");
	return;
}

static uint8 TTT_GameState(void)
{
	uint8 w=0;
	if((X|O) == 1022) //1022 is the decimal we get if all bits from 1 to 9 are used (divided among the two players)
		w=3;
	for(uint8 i=0 ; i<7 ; i++)
	{
		if((X&Win[i])==Win[i])
			w=1;
		else if((O&Win[i])==Win[i])
			w=2; 
	}
	
	return w;
	//returns 0 if game still running
	//returns 1 if player 1 won
	//returns 2 if player 2 won
	//returns 3 if draw is reached
}

static uint8 TTT_XorO(uint8 pos)
{
	if(GET_BIT(X,pos))
	{
		return 'X';
	}		
	else if(GET_BIT(O,pos))
	{
		return 'O';
	}
	else 
	{
		return ' ';
	}
}

static uint8 TTT_IsAboutToWin(void)
{
	//counts moves left for Ai or human to reach a win state, returns number of remaining move if one move left for either AI or human
//returns 0 if no move found
	uint8 move=0;
	uint16 temp;
	uint16 temp2;
	uint8 count=0;

	for(uint8 i=0 ; i++ ; i<8 )//check for AI first
	{	
		
		count=0;
		temp= O^Win[i]; //xoring the AI bits with a win state should return only one set bit if one move left to win 
		count=temp&&(!(temp&(temp-1)));//equals 1 if only one set bit
		if(count==1)// one move for AI to win is found
			{
				if((X&temp)==0) //making sure move is available, isn't occupied by X
				{ 
				temp2=temp;
				while(temp2)
				{//get which bit
					temp2=temp2>>1;
					move++;
				}
				move--;
				printf("%d",move);
				return move;//exit forloop, stop searching
			}
		}
		
	}
	
	if(move==0)//no winning move found for AI, start looking for a winning move for human
	{
		for(uint8 i=0 ; i++ ; i<8 )//check for AI first
		{	
		
		count=0;
		temp= X^Win[i]; //xoring the AI bits with a win state should return only one set bit if one move left to win 
		count=temp&&(!(temp&(temp-1)));//equals 1 if only one set bit
		if(count==1)// one move for AI to win is found
			{
				if((O&temp)==0) //making sure move is available, isn't occupied by X
				{ 
				temp2=temp;
				while(temp2)
				{//get which bit
					temp2=temp2>>1;
					move++;
				}
				move--;
				printf("%d",move);
				return move;//exit forloop, stop searching
			}
		}
		}
	}
	
	return 0;

}