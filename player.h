#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "../vector/vector.h"
#include "card.h"

typedef struct Player Player;

typedef ADTErr(*funcPointer)(Player*, int, int*, Suit, int);

/* Description:
function creates a new player and set its values (including creating his hand of cards - vector)
input- int index of player , int is real player
output- returns a pointer to player
errors- no errors - return NULL if allocation not succeed */
Player* PlayerCreate(int _index, int _isReal);

/* Description:
destroys player and free its memory
input- pointer to player
output- none
errors- none */
void PlayerDestroy(Player* _player);

/* Description:
function returns if player is real or not
input- pointer to player
output- int
errors- none - returns 0 if NULL*/
int IsReal(Player* _player);

/* Description:
function gets a player, suit, a flag for hearts allowed or not, a pointer to int card, and a pointer to strategy function that dictates the strategy for choosing a card based on player is real or not, and removing the card from players hand. putting it in pointer to int card that was given.
input- pointer to player, pointer to strategy function, pointer to int card, suit, int flag is hearts allowed.
output- ADTErr
errors- ERR_NOT_INITIALIZED if player or card pointer is NULL
ERR_OK is succeed */
ADTErr ThrowCard(Player* _player, funcPointer _func, int* _card, Suit _seriesNumber, int _isHeartsAllowed);

/* Description:
function gets a card and add it to the players hand - vector,
and sorts the hand
input- pointer to player, int card
output- ADTErr
errors- ERR_NOT_INITIALIZED if player is NULL 
ERR_OK is succeed */
ADTErr TakeCard(Player* _player, int _card);

/* Description:
function gets a player and a card and returns if player has the card or not, and the index of the card if found
input - pointer to player, int card
output - 0 if does not have the card or if player is NULL
errors- none - returns 0 if NULL*/
int FindCard(Player* _player, int _card, int* _index);

/* Description:
function gats a player and sort its hand (vector) using quick sort by suit and card number
input - pointer to player
output - none
errors - none */
void SortHand(Player* _player);

/* Description:
function gets a player and index and returns the card in that index to a pointer
input - pointer to player, int index of card, pointer to int for the result card
output - ADTErr
errors - ERR_NOT_INITIALIZED if player is NULL 
ERR_WRONG_INDEX if index is not found
ERR_OK is succeed */
ADTErr PlayerGetCardAtIndex(Player* _player, int _index, int* _card);

/* Description:
function adds the given score to the players score
input - pointer to player, int score
output - none
errors - none - does not add the score if player is NULL */
void PlayerAddToScore(Player* _player, int _score);

/* Description:
function returns player score
input - pointer to player
output - int score
errors - none - return -1 if player is NULL */
int PlayerGetScore(Player* _player);

/* sends the players hand to UI for printing */
void PlayerPrintHand(Player* _player);

/* sends all players names and scores to UI for printing 
input - array of players , int size of array
output - none */
void PlayerPrintScores(Player** _playerArr, int _size);

#endif
