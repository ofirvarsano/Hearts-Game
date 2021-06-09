#ifndef _ROUND_H_
#define _ROUND_H_
#include "player.h"

/* Description:
function creates a new round by creating a new deck,
shuffles it and deals it to the players
destroys deck at the end
input- poniter to pointer to player, int size
output- ADTErr
errors- ERR_NOT_INITIALIZED if deck or players array is NULL*/
ADTErr RoundCreate(Player** _playerArr,int _size);

/* Description:
function starts a new round, and handle its flow
input-  poniter to pointer to player, int number of players,
int round number,pointer to int maximum score
output- ADTErr
errors- ERR_NOT_INITIALIZED if max score or players array is NULL
ERR_OK if succeed */
ADTErr StartRound(Player** _playerArr, int _numOfPlayers, int _roundNumber, int* _maxScore);

/* Description:
real player chooses a card according to the rules
input - pointer to player, int size, pointer to int for card index which will be chosen, suit, int is hearts allowed
output - ADTErr
errors - ERR_NOT_INITIALIZED if player or card index pointer NULL
ERR_OK if succeed */
ADTErr ChooseCard(Player* _player, int _handSize, int* _cardIndex, Suit _seriesNumber, int _isHeartsAllowed);

/* Description:
bot player chooses a card automaticly according to the rules and the strategy 
strategy descritpion below.
input - pointer to player, int size, pointer to int for card index which will be chosen, suit, int is hearts allowed
output - ADTErr
errors - ERR_NOT_INITIALIZED if player or card index pointer NULL
ERR_OK if succeed */
ADTErr AutoChooseCard(Player* _player, int _handSize, int* _cardIndex, Suit _seriesNumber, int _isHeartsAllowed);

/* STRATEGY: 
for passing cards at the beginning : first pass the hearts if do have, others if do not.
for choosing a card to throw :
1. if there is no leading series : 
	1.1 if hearts aren't allowed : choose the minimum card which isn't a heart.
	1.2 if hearts allowed / you only have hearts :
		choose the minimum heart card / minimum card from another series if do not have heart
2. if series is set :
	2.1 choose the minimum card from the given series.
	2.3 if series is set but you do not have a suitable card :
		2.3.1 choose the maximum heart card
		2.3.2 if do not have a heart, choose maximum card from another series
*/

#endif


