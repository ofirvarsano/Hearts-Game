#ifndef _DECK_H_
#define _DECK_H_
#include "../vector/vector.h"

/* Description:
function creates a new deck of cards and set up its values
fills uo the deck and suffles it
input- void
output- returns a pointer to to vector
errors- no errors - return NULL if allocation not succeed */
Vector* DeckCreate();

/* Description:
destroys deck and free its memory
input- pointer to vector
output- none
errors- none */
void DeckDestroy(Vector* _deck);

/* Description:
function shuffles the deck
input- pointer to vector
output- ADTErr error - changes the vector in place
errors- ERR_NOT_INITIALIZED if deck is NULL
ERR_OK if succeed */
ADTErr Shuffle(Vector* _deck);


/* Description:
function removes a card from the deck and puts its value to a variable
input- pointer to vector, pointer to int
output- ADTErr error
errors- ERR_NOT_INITIALIZED if deck is NULL
ERR_UNDERFLOW if deck is empty
ERR_OK if succeed */
ADTErr DealCard(Vector* _deck, int* _temp);

#endif
