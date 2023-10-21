#ifndef TICTACTOE_H
#define TICTACTOE_H
#define SIZE 9 //the number of spaces in game grid

void TTT_InitiateGame(void);

static void TTT_SinglePlayer(void);

static void TTT_MultiPlayer(void);

static void TTT_Display(void);

static void TTT_Quit(void);

static uint8 TTT_GameState(void);

static uint8 TTT_XorO(uint8 pos);

static uint8 TTT_IsAboutToWin(void);

#endif