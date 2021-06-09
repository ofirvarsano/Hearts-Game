#include "game.h"
#include <stdlib.h>
#define NUM_OF_PLAYERS	4
#define MAX_SCORE	100

int main()
{
	Game* game = NULL;
	game = GameCreate(NUM_OF_PLAYERS, MAX_SCORE);
	if(game != NULL)
	{
		StartGame(game);
		GameDestroy(game);
	}
	
	return 0;
}
