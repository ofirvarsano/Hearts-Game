#include "deck.h"
#include "../vector/vector.h"
#include <time.h>
#define DECK_SIZE	52
#define BLOCK_SIZE	4

static ADTErr FillDeck(Vector* _deck);

Vector* DeckCreate()
{
	Vector* deck = VectorCreate(DECK_SIZE, BLOCK_SIZE);
	if(deck == NULL)
	{
		return NULL;
	}
	FillDeck(deck);
	return deck;
}

void DeckDestroy(Vector* _dec)
{
	if(_dec)
	{
		VectorDestroy(_dec);
	}
}

static ADTErr FillDeck(Vector* _deck)
{
	int i;
	ADTErr err;
	if(_deck == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	for(i = 0; i < DECK_SIZE; ++i)
	{
		err = VectorAddEnd(_deck, i);
		if(err != ERR_OK)
		{
			return err;
		}
	}
	return ERR_OK;
}

ADTErr Shuffle(Vector* _deck)
{
	int i,j,temp,temp2;
	if(_deck == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	srand(time(NULL));
	for(i = 0; i < DECK_SIZE; ++i)
	{
		j = rand() % DECK_SIZE;
		VectorGet(_deck, j, &temp);
		VectorGet(_deck, i, &temp2);
		
		VectorSet(_deck, j, temp2);
		VectorSet(_deck, i, temp);
	}
	return ERR_OK;
}

ADTErr DealCard(Vector* _deck, int* _temp)
{
	if(_deck == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	return VectorDeleteEnd(_deck, _temp);
}	
		
		
		
		
		
		
