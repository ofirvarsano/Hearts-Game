#ifndef _CARD_H_
#define _CARD_H_
#define CALC_SUIT(i) (i / NUM_OF_CARDS)
#define CALC_CARDNUM(i) (i % NUM_OF_CARDS)

typedef enum
{
	NONE = -1,
	HEART = 0,
	SPADE,
	DIAMOND,
	CLUB,
	NUM_OF_SUITES,
	ONLY_2CLUB
}Suit;

typedef enum
{
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING,
	ACE,
	NUM_OF_CARDS
}NumCard;

#endif
