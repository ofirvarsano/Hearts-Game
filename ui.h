#ifndef _UI_H_
#define _UI_H_
#include "../vector/vector.h"
#include "card.h"

/* prints a single card by its number sign and color
input - int card
output - none */
void UIPrintCard(int _card);

/* prints players hand of cards
input - pointer to vector
output - none */
void UIPrintHand(Vector* _hand);

/* asks the player if wants to play another round
input - pointer to int
output - none - puts the answer in an int pointer that was given */
void UIWannaExit(int* _exit);

/* prints player score
input - pointer to char name, int score
output - none */
void UIPrintScore(char* _name,int _score);

/* prints the series
input - int array,int size
output - none */
void UIPrintSeries(int _series[], int _size);

/* claenes screen */
void UICleanScreen();

/* prints Bye Bye */
void UIPrintByeBye();

/* sleep for x seconds
input - int sec
output - none */
void UISleep(int _sec);

/* prints choose 2 club */
void UIChoose2Club(int* _cardIndex);

/* prints choose card */
void UIChooseCard(int* _cardIndex, Suit _suitNumber);

#endif
