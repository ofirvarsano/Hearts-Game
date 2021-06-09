#include "round.h"
#include "player.h"
#include "deck.h"
#include "ui.h"
#include "card.h"
#include "../vector/vector.h"

#define DECK_SIZE	52
#define HAND_SIZE	13
#define NUM_OF_TRICKS	13
#define CARDS_TO_PASS	3
#define ARRAY_SIZE	4
#define DOWN	-1
#define UP	1

static void PassCards(Player** _playerArr,int _size, int toPass);

static void Trick(Player** _playerArr, int _size, int* _whoLost, int* _canUseHearts, int _trickNumber);

static int Search2Club(Player** _playerArr, int _numOfPlayers);

static void GetMaxScore(Player** _playerArr, int _numOfPlayers, int* _maxScore);

static void CalcScores(Player** _playerArr, int _size, int series[], int* _whoLost, Suit _seriesSuit);

static ADTErr ChooseFrom(Player* _player, int _handSize, int _from, int _to, int _jump, int* _cardIndex);

static ADTErr GetCardByRule(Player* _player, int _from, int _to, int* _cardIndex, Suit _seriesNumber);


ADTErr RoundCreate(Player** _playerArr,int _size)
{
	int card,i,j;
	Vector* deck = DeckCreate();
	if(deck == NULL || _playerArr == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	Shuffle(deck);
	for(i = 0; i < _size; ++i)
	{
		for(j = 0; j < HAND_SIZE; ++j)
		{
			DealCard(deck, &card);
			TakeCard(_playerArr[i], card);
		}
	}
	DeckDestroy(deck);
	return ERR_OK;
}

ADTErr StartRound(Player** _playerArr, int _numOfPlayers, int _roundNumber, int* _maxScore)
{
	int i;
	int canUseHeart = 0;
	int whoLost;
	int passes[] = {1, 3, 2, 0};
	int toPass = passes[_roundNumber];
	
	if(_playerArr == NULL || _maxScore == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	PassCards(_playerArr, _numOfPlayers, toPass);
	whoLost = Search2Club(_playerArr, _numOfPlayers);
	
	for(i = 0; i < NUM_OF_TRICKS; ++i)
	{
		Trick(_playerArr, _numOfPlayers, &whoLost, &canUseHeart,i);
	}
	
	PlayerPrintScores(_playerArr, _numOfPlayers);
	GetMaxScore(_playerArr, _numOfPlayers, _maxScore);
	
	return ERR_OK;
}

static void Trick(Player** _playerArr, int _size, int* _whoLost, int* _canUseHearts, int _trickNumber)
{
	int i = 0;
	int card;
	funcPointer func = NULL;
	int series[] = {-1,-1,-1,-1};
	int currentPlayer = *_whoLost;
	Suit _seriesSuit = NONE;
	
	while(i < _size)
	{
		if(_trickNumber == 0 && currentPlayer == *_whoLost)
		{
			_seriesSuit = ONLY_2CLUB;
		}
		
		func = IsReal(_playerArr[currentPlayer]) ? ChooseCard : AutoChooseCard;

		ThrowCard(_playerArr[currentPlayer], func, &card, _seriesSuit, *_canUseHearts);
		series[currentPlayer] = card;
		if(card < NUM_OF_CARDS)
		{
			*_canUseHearts = 1;
		}
		if(i == 0)
		{
			_seriesSuit = CALC_SUIT(card);
		}
		
		UICleanScreen();
		UIPrintSeries(series, _size);
		UISleep(1.5);
		currentPlayer = (currentPlayer + 1) % _size;
		++i;
	}
	CalcScores(_playerArr,_size, series, _whoLost, _seriesSuit);
}

static void GetMaxScore(Player** _playerArr, int _numOfPlayers, int* _maxScore)
{
	int i;
	for(i = 0; i < _numOfPlayers; ++i)
	{
		if(PlayerGetScore(_playerArr[i]) > *_maxScore)
		{
			*_maxScore = PlayerGetScore(_playerArr[i]);
		}
	}
}

static void CalcScores(Player** _playerArr, int _size, int series[], int* _whoLost, Suit _seriesSuit)
{
	int i;
	int trickScore = 0;
	int maxCard = 0;
	for(i = 0; i < _size; ++i)
	{
		if(series[i] == SPADE * NUM_OF_CARDS + QUEEN)
		{
			trickScore += NUM_OF_CARDS;
		}
		else if(series[i] < NUM_OF_CARDS)
		{
			trickScore++;
		}
		
		if(CALC_SUIT(series[i]) == _seriesSuit)
		{
			if(series[i] > maxCard)
			{
				maxCard = series[i];
				*_whoLost = i;
			}
		}
	}
	PlayerAddToScore(_playerArr[*_whoLost],trickScore);
}

static int Search2Club(Player** _playerArr, int _numOfPlayers)
{
	int i = -1;
	int index;
	for(i = 0; i < _numOfPlayers; ++i)
	{
		if(FindCard(_playerArr[i],NUM_OF_CARDS * CLUB,&index))
		{
			return i;
		}
	}
	return i;
}

/* passes cards from players to the matching players according to the round number
real players chooses which cards to pass, bot players passes the hearts first if got */
static void PassCards(Player** _playerArr, int _size, int _toPass)
{
	int i,k;
	int tempCard;
	int tempHeartsBroken = 1;
	int cardsToPass[ARRAY_SIZE][CARDS_TO_PASS];
	funcPointer func = NULL;
	if(_toPass == 0)
	{
		return;
	}
	for(i = 0; i < _size; ++i)
	{
		func = IsReal(_playerArr[i]) ? ChooseCard : AutoChooseCard;
		
		for(k = 0; k < CARDS_TO_PASS; ++k)
		{
			ThrowCard(_playerArr[i], func, &tempCard, NONE, tempHeartsBroken);
			cardsToPass[i][k] = tempCard;
		}
	}
	for(i = 0; i < _size; ++i)
	{
		for(k = 0; k < CARDS_TO_PASS; ++k)
		{
			tempCard = cardsToPass[i][k];
			TakeCard(_playerArr[(i+_toPass)%_size], tempCard);
		}
	}
}

/* Real player chooses a card according to the rules */
ADTErr ChooseCard(Player* _player, int _handSize, int* _cardIndex, Suit _seriesNumber, int _isHeartsAllowed)
{
	int from, to, card;
	ADTErr err;
	if(_player == NULL || _cardIndex == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_handSize == 0)
	{
		return ERR_UNDERFLOW;
	}
	PlayerPrintHand(_player);
	/* case only 2 club is allowed */
	if(_seriesNumber == ONLY_2CLUB)
	{
		do
		{
			UIChoose2Club(_cardIndex);
			PlayerGetCardAtIndex(_player,*_cardIndex,&card);
		}while(card != NUM_OF_CARDS * CLUB);
		return ERR_OK;
	}
	if(_seriesNumber == NONE)
	{
		/* case no series and hearts aren't allowed */
		if(_isHeartsAllowed == 0)
		{
			if(GetCardByRule(_player,NUM_OF_CARDS, NUM_OF_CARDS * NUM_OF_SUITES,_cardIndex,_seriesNumber) == ERR_OK)
			{
				return ERR_OK;
			}
		}
		/* case no series and hearts are allowed */
		GetCardByRule(_player, 0, NUM_OF_CARDS * NUM_OF_SUITES, _cardIndex, _seriesNumber);
		return ERR_OK;
	}
	/* case series is set */
	from = _seriesNumber * NUM_OF_CARDS;
	to = from + NUM_OF_CARDS;
	err = GetCardByRule(_player, from, to, _cardIndex, _seriesNumber);
	if(err == ERR_OK)
	{
		return ERR_OK;
	}
	/* case series is set but you don't have a suitable card */
	GetCardByRule(_player, 0, NUM_OF_CARDS * NUM_OF_SUITES, _cardIndex, _seriesNumber);

	return ERR_OK;
}

static ADTErr GetCardByRule(Player* _player, int _from, int _to, int* _cardIndex, Suit _seriesNumber)
{
	int i, card, index;
	for(i = _from; i < _to; ++i)
	{
		if(FindCard(_player, i, &index))
		{
			do
			{
				UIChooseCard(_cardIndex, _seriesNumber);
				PlayerGetCardAtIndex(_player,*_cardIndex,&card);
			}while(card < _from || card >= _to);

			return ERR_OK;
		}
	}
	return ERR_WRONG_INDEX;
}

/* bot player chooses a card automaticly according to the rules and the strategy */
ADTErr AutoChooseCard(Player* _player, int _handSize, int* _cardIndex, Suit _seriesNumber, int _isHeartsAllowed)
{
	ADTErr err;
	int from,to;
	if(_player == NULL || _cardIndex == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_handSize == 0)
	{
		return ERR_UNDERFLOW;
	}
	/* case only 2 club is allowed */
	if(_seriesNumber == ONLY_2CLUB)
	{
		return ChooseFrom(_player, _handSize, NUM_OF_CARDS * CLUB, NUM_OF_CARDS * CLUB + 1, UP, _cardIndex);
	}
	if(_seriesNumber == NONE)
	{
		/* case no series and hearts aren't allowed */
		if(!_isHeartsAllowed)
		{
			if(ChooseFrom(_player, _handSize, NUM_OF_CARDS, NUM_OF_CARDS * NUM_OF_SUITES, UP, _cardIndex) == ERR_OK)
			{
				return ERR_OK;
			}
		}
		/* case no series and you have only hearts */
		if(ChooseFrom(_player, _handSize, 0, NUM_OF_CARDS * NUM_OF_SUITES, UP, _cardIndex) != ERR_OK)
		{
			return ERR_OK;
		}
	}
	from = _seriesNumber * NUM_OF_CARDS;
	to = from + NUM_OF_CARDS;
	
	/* case series is set */
	err = ChooseFrom(_player, _handSize, from, to , UP, _cardIndex);
	if(err != ERR_OK)
	{
		/* case series is set but you don't have a suitable card */
		if(ChooseFrom(_player, _handSize, NUM_OF_CARDS -1 , -1, DOWN , _cardIndex) != ERR_OK)
		{
			ChooseFrom(_player, _handSize, NUM_OF_CARDS * NUM_OF_SUITES -1, -1 , DOWN, _cardIndex);
		}
	}
	return ERR_OK;
}

static ADTErr ChooseFrom(Player* _player, int _handSize, int _from, int _to, int _jump, int* _cardIndex)
{
	int i, index;
	for(i = _from; i != _to; i += _jump)
	{
		if(FindCard(_player, i, &index))
		{
			*_cardIndex = index;
			return ERR_OK;
		}
	}
	return ERR_WRONG_INDEX;
}




