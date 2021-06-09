#ifndef _GAME_H_
#define _GAME_H_

typedef struct Game Game;

/* Description:
function creates a new game and set its values,
creates a new array of pointers to players
fill players array (create players)
input- int numer of players to create, int maximum score for game
output- returns a pointer to a game
errors- no errors - return NULL if allocation not succeed */
Game* GameCreate(int _numOfPlayers, int _maxScore);

/* Description:
destroys game and players array
and free all its memory
input- pointer to game
output- none
errors- none */
void GameDestroy(Game* _game);

/* Description:
function starts a new game.
creates a round and start it untill player wants to exit or maximum score has been reached
creates a new array of pointers to players
fill players array (create players)
input- ipointer to game
output- none
errors- none */
void StartGame(Game* _game);

#endif
