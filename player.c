#include "player.h"
#include "../vector/vector.h"
#include <string.h>
#include <stdlib.h>
#include "card.h"
#include "ui.h"
#include <time.h>
#define HAND_SIZE	13
#define BLOCK_SIZE	4
#define STRING_SIZE	20
#define MAGIC 23456
#include "utilFuncs.h"

struct Player
{
	Vector* m_hand;
	char m_name[STRING_SIZE];
	int m_score;
	int m_isReal;
	int m_magic;
};

Player* PlayerCreate(int _index, int _isReal)
{
	char name[STRING_SIZE];
	char s[] = "player ";
	Player* newPlayer = (Player*)calloc(1, sizeof(Player));
	if(newPlayer == NULL)
	{
		return NULL;
	}
	newPlayer->m_hand = VectorCreate(HAND_SIZE, BLOCK_SIZE);
	if(newPlayer->m_hand == NULL)
	{
		free(newPlayer);
		return NULL;
	}
	newPlayer->m_magic = MAGIC;
	
	MyItoa(_index + 1,name);
	strcpy(newPlayer->m_name,s);
	strcat(newPlayer->m_name,name);
	newPlayer->m_isReal = _isReal;
	return newPlayer;
}

void PlayerDestroy(Player* _player)
{
	if(_player && _player->m_magic == MAGIC)
	{
		if(_player->m_hand)
		{
			VectorDestroy(_player->m_hand);
		}
		_player->m_magic = 0;
		free(_player);
	}
}

int IsReal(Player* _player)
{
	if(_player == NULL)
	{
		return 0;
	}
	return _player->m_isReal;
}

int FindCard(Player* _player, int _card, int* _index)
{
	int i, temp, size;
	*_index = -1;
	if(_player != NULL && _player->m_hand != NULL)
	{
		VectorItemsNum(_player->m_hand,&size);
		for(i = 0; i < size; ++i)
		{
			VectorGet(_player->m_hand, i, &temp);
			if(temp == _card)
			{
				*_index = i;
				return 1;
			}
		}
	}
	return 0;
}

ADTErr TakeCard(Player* _player, int _card)
{
	ADTErr err;
	if(_player == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	err = VectorAddEnd(_player->m_hand, _card);
	SortHand(_player);
	
	return err;
}

void SortHand(Player* _player)
{
	int handSize;
	if(_player == NULL)
	{
		return;
	}
	VectorItemsNum(_player->m_hand,&handSize);
	if(handSize > 1)
	{
		QuickSortRec(_player->m_hand,0,handSize - 1);
	}
}

int PlayerGetScore(Player* _player)
{
	if(_player)
	{
		return _player->m_score;
	}
	return -1;
}

void PlayerAddToScore(Player* _player, int _score)
{
	if(_player)
	{
		_player->m_score += _score;
	}
}

ADTErr ThrowCard(Player* _player, funcPointer _func, int* _card, Suit _seriesNumber, int _isHeartsAllowed)
{
	ADTErr err;
	int temp1, temp2;
	int handSize;
	int cardIndex;
	if(_player == NULL || _func == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	VectorItemsNum(_player->m_hand, &handSize);
	err = (*_func)(_player, handSize, &cardIndex, _seriesNumber, _isHeartsAllowed);
	if(err != ERR_OK)
	{
		return err;
	}
	VectorGet(_player->m_hand, cardIndex, _card);
	if(handSize > 1)
	{
		VectorGet(_player->m_hand, handSize - 1, &temp2);
		VectorSet(_player->m_hand, cardIndex, temp2);
	}
	VectorDeleteEnd(_player->m_hand, &temp1);
	SortHand(_player);
	
	return ERR_OK;
}

void PlayerPrintHand(Player* _player)
{
	UIPrintHand(_player->m_hand);
}

void PlayerPrintScores(Player** _playerArr, int _size)
{
	int i;
	if(_playerArr)
	{
		for(i = 0; i < _size; ++i)
		{
			if(_playerArr[i] != NULL)
			{
				UIPrintScore(_playerArr[i]->m_name, _playerArr[i]->m_score);
			}
		}
	}
}

ADTErr PlayerGetCardAtIndex(Player* _player, int _index, int* _card)
{
	if(_player == NULL || _card == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	return VectorGet(_player->m_hand, _index, _card);
}


