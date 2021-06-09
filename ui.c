#include "ui.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../vector/vector.h"
#include "card.h"
#include "utilFuncs.h"
#define NO_CARD	-1
#define SPACE_SIZE	5
/* colors */
#define NORMAL "\x1B[0m"
#define BLACK "\x1b[30m"
#define RED "\x1B[31m"

/* cards suites symbols */
#define HEART_SYMBOL "\xE2\x99\xA5"
#define SPADE_SYMBOL "\xE2\x99\xA0"
#define DIAMOND_SYMBOL "\xE2\x99\xA6"
#define CLUB_SYMBOL "\xE2\x99\xA3"

void UIPrintHand(Vector* _hand)
{
	int i, temp;
	int handSize;
	VectorItemsNum(_hand, &handSize);
	for(i = 0; i < handSize; ++i)
	{
		printf("(%d) ",i);
	}
	printf("\n");
	for(i = 0; i < handSize; ++i)
	{
		VectorGet(_hand, i, &temp);
		UIPrintCard(temp);
	}
	printf("\n");
}

void UIPrintCard(int _card)
{
	int kind, number;
	char* c;
	char* color;
	char sign[20];
	color = NORMAL;
	kind = CALC_SUIT(_card);
	number = CALC_CARDNUM(_card);
	if(_card == NO_CARD)
	{
		printf(" ");
		return;
	}
	switch(kind)
	{
		case HEART: c = HEART_SYMBOL;
					color = RED;
					break;
		case SPADE: c = SPADE_SYMBOL; break;
		case DIAMOND: c = DIAMOND_SYMBOL;
					color = RED;
					break;
		case CLUB: c = CLUB_SYMBOL; break;
	}
	switch(number)
	{
		case JACK: strcpy(sign,"J"); break;
		case QUEEN: strcpy(sign,"Q"); break;
		case KING: strcpy(sign,"K"); break;
		case ACE: strcpy(sign,"A"); break;
		default: strcpy(sign,"");
				MyItoa(number + 2, sign);
				break;
	}
	printf("%s%s%s%s  ", color, sign, c, NORMAL);
}

void UIWannaExit(int* _exit)
{
	char choise[20];
	printf("\nPlay another round ? (y / n)\n");
	scanf("%s",choise);
	if(strcmp(choise,"y") != 0)
	{
		*_exit = 1;
	}
	else
	{
		*_exit = 0;
	}
}

void UIPrintScore(char* _name,int _score)
{
	printf("Player %s Score: %d\n", _name, _score);
}

void UIPrintSeries(int _series[], int _size)
{
	int i;
	for(i = 0; i < SPACE_SIZE; ++i)
	{
		printf(" ");
	}
	UIPrintCard(_series[2]);
	printf("\n\n");
	UIPrintCard(_series[1]);
	for(i = 0; i < 2 * SPACE_SIZE - 1; ++i)
	{
		printf(" ");
	}
	UIPrintCard(_series[3]);
	printf("\n\n");
	for(i = 0; i < SPACE_SIZE; ++i)
	{
		printf(" ");
	}
	UIPrintCard(_series[0]);
	printf("\n--------------");
	printf("\n");
}

void UICleanScreen()
{
	system("clear");
}

void UIPrintByeBye()
{
	printf("--------\n");
	printf("Bye Bye\n");
	printf("--------\n");
}

void UISleep(int _sec)
{
	sleep(_sec);
}

void UIChoose2Club(int* _cardIndex)
{
	do
	{
		printf("choose card (2 CLUB)\n");
		scanf("%d",_cardIndex);
	}while(*_cardIndex < 0 || *_cardIndex > 12);
}

void UIChooseCard(int* _cardIndex, Suit _suitNumber)
{
	char* c;
	switch(_suitNumber)
	{
		case HEART: c = HEART_SYMBOL; break;
		case SPADE: c = SPADE_SYMBOL; break;
		case DIAMOND: c = DIAMOND_SYMBOL; break;
		case CLUB: c = CLUB_SYMBOL; break;
		default: c = "";break;
	}
	do
	{
		printf("choose card %s\n",c);
		scanf("%d",_cardIndex);
	}while(*_cardIndex < 0 || *_cardIndex > 12);
}


