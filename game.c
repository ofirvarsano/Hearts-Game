#include "ui.h"
#include "round.h"
#include "player.h"
#include "game.h"
#include "../vector/vector.h"
#include <stdlib.h>
#define MAGIC 12345

struct Game
{
	Player** m_players;
	int m_numOfPlayers;
	int m_maxScore;
	int m_whoStarts;
	int m_magic;
};

static ADTErr FillPlayers(int _numOfPlayers, Game* _newGame);

Game* GameCreate(int _numOfPlayers, int _maxScore)
{
	Game* newGame = (Game*)calloc(1,sizeof(Game));
	if(newGame == NULL)
	{
		return NULL;
	}
	newGame->m_players = (Player**)malloc(_numOfPlayers * sizeof(Player*));
	if(newGame->m_players == NULL)
	{
		free(newGame);
		return NULL;
	}
	newGame->m_numOfPlayers = _numOfPlayers;
	newGame->m_maxScore = _maxScore;
	newGame->m_magic = MAGIC;
	
	if(FillPlayers(_numOfPlayers, newGame) != ERR_OK)
	{
		return NULL;
	}
	return newGame;
}

static ADTErr FillPlayers(int _numOfPlayers, Game* _newGame)
{
	int i,j;
	int isReal = 1;
	for(i = 0; i < _numOfPlayers; ++i)
	{
		_newGame->m_players[i] = PlayerCreate(i,isReal);
		isReal = 0;
		if(_newGame->m_players[i] == NULL)
		{
			for(j = 0; j < i; ++j)
			{
				PlayerDestroy(_newGame->m_players[j]);
			}
			free(_newGame->m_players);
			free(_newGame);
			return ERR_ALLOCATION_FAILED;
		}
	}
	return ERR_OK;
}

void GameDestroy(Game* _game)
{
	int i;
	if(_game && _game->m_magic == MAGIC)
	{
		if(_game->m_players)
		{
			for(i = 0; i < _game->m_numOfPlayers; ++i)
			{
				PlayerDestroy(_game->m_players[i]);
			}
			free(_game->m_players);
		}
		_game->m_magic = 0;
		free(_game);
	}
}

void StartGame(Game* _game)
{
	int roundNumber = 0;
	int maxScore = 0;
	int exit = 0;

	while(maxScore < _game->m_maxScore && exit != 1)
	{
		UICleanScreen();
		if(RoundCreate(_game->m_players, _game->m_numOfPlayers) != ERR_OK)	
		{
			return;
		}
		StartRound(_game->m_players, _game->m_numOfPlayers,roundNumber,&maxScore);
		roundNumber = (roundNumber + 1) % _game->m_numOfPlayers;

		UIWannaExit(&exit);
		UICleanScreen();
	}
	UIPrintByeBye();
}








