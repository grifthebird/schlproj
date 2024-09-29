/*
 SolitairePoker.c
 
 Notes: The 52 cards of a deck are represented as integers: 0 .. 51
 0..12 are clubs Ace, 2, ..., King
 13..25 are diamonds Ace, 2, ..., King
 26..38 are hearts Ace, 2, ..., King
 39..51 are spades Ace, 2, ..., King

 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

//do not remove
#include "include.code" //Include custom header file (it contains necessary functions)
//A version of the file:include.code is available from the assignment page
//as studentinclude.code which you should save locally as include.code
//include.code contains implementations for seed, instructions, and private_nextcard(int)
//used by shuffle and next card.
//The version used during testing is slightly different but will not affect your efforts.
//For testing you may modify studentinclude.code -- it will not be part of your submission.


// Function to shuffle the deck
//you should call this before each deal (including the first)
void shuffle() {
    private_nextcard(1); // Call a custom function to shuffle
}

// Function to get the next card to be dealt
//call this to deal a card. Do not call rand().
int nextcard() {
    return private_nextcard(0); // Call a custom function to get the next card
}

// Enumeration for different poker hands
enum hands { UNKNOWN, HIGHCARD, PAIR, TWOPAIR, TRIPS, STRAIGHT,
    FLUSH, FULLHOUSE, QUADS, STRAIGHTFLUSH, ROYALFLUSH };
char * handNames[] ={ "UNKNOWN", "HIGHCARD", "PAIR", "TWOPAIR", "TRIPS", "STRAIGHT",
    "FLUSH", "FULLHOUSE", "QUADS", "STRAIGHTFLUSH", "ROYALFLUSH" }; // Names of each hand

// Enumeration for card suits
enum suits {CLUB, DIAMOND, HEART, SPADE};
char * suitNames[] ={ "CLUB", "DIAMOND", "HEART", "SPADE"}; // Names of card suits

// Enumeration for card ranks
enum ranks {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
char * rankNames[] ={ "ACE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN",
    "EIGHT", "NINE", "TEN", "JACK", "QUEEN", "KING"}; // Names of card ranks

//FUNCTION PROTOTYPES: YOU MUST IMPLEMENT THESE FUNCTIONS

// Function to get the rank of a card
enum ranks getrank(int card);

// Function to get the suit of a card
enum suits getsuit(int card);

// Function to evaluate the poker hand
enum hands eval(int []);

// Function to check for a royal flush
int royalflush(int []);

// Function to check for a straight flush
int straightflush(int []);

// Function to check for four of a kind
int fourofkind(int []);

// Function to check for a full house
int fullhouse(int []);

// Function to check for a flush
int flush(int []);

// Function to check for a straight
int straight(int []);

// Function to check for three of a kind
int threekind(int []);

// Function to check for two pairs
int twopair(int []);

// Function to check for a pair
int pair(int []);


int main(int argc, char ** argv) {
    //do not remove
    seed(argc, argv); // Seed the random number generator
    instructions(); // Display game instructions

    //TODO:
        //WRITE CODE TO PLAY 10 HANDS OF POKER
            //DEAL 5 CARDS
            //SHOW DEALT HAND
            //DRAW UP TO 3 CARDS
            //SHOW FINAL HAND
            //EVAL REPPORT AND SAVE INFO FOR LATER
        //GENERATE SCORESHEET USING INFO

    // array for hand values
    int allScores[10] = {0};
    int allCards[50] = {0};
    char allNames[10][50];
    int handValues[11] = {0, 1, 3, 7, 11, 17, 26, 32, 40, 45, 50};
    int total = 0;
    for (int h = 0; h < 10; h++)
    {
    	// shuffle before dealing
    	shuffle();
	
    	// deal a hand of 5 cards
    	int hand[5] = {0};
    	for (int i = 0; i < 5; i++) // get hand of cards
    	{
		    hand[i] = nextcard();
	    	printf("%s-%s\t", suitNames[getsuit(hand[i])], rankNames[getrank(hand[i])]);
    	}
    	printf("\n");
	
    	// replace cards (if chosen)
    	printf("Select up to three cards to replace[1-5] and press enter\n");
	
    	for (int i = 0; i < 5; i++)
    	{
		    printf("%s-%s\t", suitNames[getsuit(hand[i])], rankNames[getrank(hand[i])]);
    	}
    	printf("\n");
	
    	char replaceInput[50];
    	fgets(replaceInput, 50, stdin);
    	for (int i = 0; i < strlen(replaceInput); i++)
    	{
		    if (isdigit(replaceInput[i]))
	    	{
			    hand[atoi(&replaceInput[i]) - 1] = nextcard(); 
	    	}
    	}
	
    	// print new hand
    	for (int i = 0; i < 5; i++)
    	{
		    printf("%s-%s\t", suitNames[getsuit(hand[i])], rankNames[getrank(hand[i])]);
		    allCards[i + (h * 5)] = hand[i];
    	}
	
    	printf("\n");
	
    	// print score for round
    	printf("Hand  %d: Score: %d %s\n", (h + 1), handValues[eval(hand)], handNames[eval(hand)]);
	total += handValues[eval(hand)];
	allScores[h] = handValues[eval(hand)];
	strcpy(allNames[h], handNames[eval(hand)]);
	printf("\n\n");
    }

    // print the scoresheet
    // header
    printf("********************************************************************************\n");
    printf("***                         S C O R E S H E E T                              ***\n");
    printf("********************************************************************************\n");
    
    // data section
    for (int i = 0; i < 10; i++)
    {
	    printf("Hand %d: Score: %d %s ", (i + 1), allScores[i], allNames[i]);
	    printf("[");
	    printf("%d %s-%s ", allCards[(i * 5)], suitNames[getsuit(allCards[(i * 5)])], rankNames[getrank(allCards[(i * 5)])]);
	    printf("%d %s-%s ", allCards[(i * 5) + 1], suitNames[getsuit(allCards[(i * 5) + 1])], rankNames[getrank(allCards[(i * 5) + 1])]);
	    printf("%d %s-%s ", allCards[(i * 5) + 2], suitNames[getsuit(allCards[(i * 5) + 2])], rankNames[getrank(allCards[(i * 5) + 2])]);
	    printf("%d %s-%s ", allCards[(i * 5) + 3], suitNames[getsuit(allCards[(i * 5) + 3])], rankNames[getrank(allCards[(i * 5) + 3])]);
	    printf("%d %s-%s", allCards[(i * 5) + 4], suitNames[getsuit(allCards[(i * 5) + 4])], rankNames[getrank(allCards[(i * 5) + 4])]);
	    printf("]\n");
    }

    // footer
    printf("==============================================================================\n");
    printf("Total points:\t%d\n", total);
    printf("==============================================================================\n");

    return 0;
}

//TODO:
//THE FOLLOWING STUBS NEED TO BE IMPLEMENTED CORRECTLY

// Function to get the suit of a card
enum suits getsuit(int card){
    return (card / 13);
}

// Function to get the rank of a card
enum ranks getrank(int card){
    return (card % 13);
}
// Function to evaluate the poker hand
enum hands eval(int hand[]){
	if (royalflush(hand))
	{
		return 10;
	}
	else if (straightflush(hand))
	{
		return 9;
	}
	else if (fourofkind(hand))
	{
		return 8;
	}
	else if (fullhouse(hand))
	{
		return 7;
	}
	else if (flush(hand))
	{
		return 6;
	}
	else if (straight(hand))
	{
		return 5;
	}
	else if (threekind(hand))
	{
		return 4;
	}
	else if (twopair(hand))
	{
		return 3;
	}
	else if (pair(hand))
	{
		return 2;
	}
	else
	{
		return 1;
	}
}

// Function to check for a royal flush
int royalflush(int hand[]){
	// get suits of cards
	int handSuit[5] = {0};
	for (int i = 0; i < 5; i++)
	{
		handSuit[i] = getsuit(hand[i]);
	}

	// check if they match
	for (int i = 0; i < 5; i++)
	{
		if (handSuit[0] != handSuit[i])
		{
			return 0;
		}
	}

	// check for a flush
	int flushEnum[5] = {0, 9, 10, 11, 12};
	for (int i = 0; i < 5; i++)
	{
		int count = 0;
		for (int j = 0; j < 5; j++)
		{
			if (flushEnum[j] == getrank(hand[i]))
			{
				count++;
			}
		}

		if (count == 0)
		{
			return 0;
		}
	}

	return 1;
}

// Function to check for a straight flush
int straightflush(int hand[]){
	// get suits of cards
	int handSuit[5] = {0};
	for (int i = 0; i < 5; i++)
	{
		handSuit[i] = getsuit(hand[i]);
	}

	// check if they match
	for (int i = 0; i < 5; i++)
	{
		if (handSuit[0] != handSuit[i])
		{
			return 0;
		}
	}

	// check for a straight
	int min = getrank(hand[0]);
	for (int i = 0; i < 5; i++)
	{
		if (getrank(hand[i]) < min)
		{
			min = getrank(hand[i]);
		}
	}

	for (int i = 0; i < 5; i++)
	{
		int count = 0;
		for (int j = 0; j < 5; j++)
		{
			if (getrank(hand[j]) == min)
			{
				count++;
			}
		}
		if (count == 0)
		{
			return 0;
		}
		min++;
	}
	return 1;
}

// Function to check for a flush
int flush(int hand[]){
	// get suits of cards
	int handSuit[5] = {0};
	for (int i = 0; i < 5; i++)
	{
		handSuit[i] = getsuit(hand[i]);
	}

	// check if they match
	for (int i = 0; i < 5; i++)
	{
		if (handSuit[0] != handSuit[i])
		{
			return 0;
		}
	}
	return 1;
}

// Function to check for a straight
int straight(int hand[]){
	// check for a straight
	int min = getrank(hand[0]);
	for (int i = 0; i < 5; i++)
	{
		if (getrank(hand[i]) < min)
		{
			min = getrank(hand[i]);
		}
	}

	for (int i = 0; i < 5; i++)
	{
		int count = 0;
		for (int j = 0; j < 5; j++)
		{
			if (getrank(hand[j]) == min)
			{
				count++;
			}
		}
		if (count == 0)
		{
			return 0;
		}
		min++;
	}
	return 1;
}

// Function to check for four of a kind
int fourofkind(int hand[]){
	int rankCount[13] = {0};
	for (int i = 0; i < 5; i++)
	{
		rankCount[getrank(hand[i])]++;
	}

	for (int i = 0; i < 13; i++)
	{
		if (rankCount[i] == 4)
		{
			return 1;
		}
	}
	return 0;
}

// Function to check for a full house
int fullhouse(int hand[]){
	int rankCount[13] = {0};
	int count3 = 0;
	int count2 = 0;
	for (int i = 0; i < 5; i++)
	{
		rankCount[getrank(hand[i])]++;
	}

	for (int i = 0; i < 13; i++)
	{
		if (rankCount[i] == 2)
		{
			count2++;
		}
		else if (rankCount[i] == 3)
			count3++;
	}

	if (count2 && count3)
	{
		return 1;
	}
    return 0;
}

// Function to check for three of a kind
int threekind(int hand[]){
	int rankCount[13] = {0};
	for (int i = 0; i < 5; i++)
	{
		rankCount[getrank(hand[i])]++;
	}

	for (int i = 0; i < 13; i++)
	{
		if (rankCount[i] == 3)
		{
			return 1;
		}
	}

    return 0;
}

// Function to check for two pairs
int twopair(int hand[]){
	int rankCount[13] = {0};
	int count = 0;
	for (int i = 0; i < 5; i++)
	{
		rankCount[getrank(hand[i])]++;
	}

	for (int i = 0; i < 13; i++)
	{
		if (rankCount[i] == 2)
		{
			count++;
		}
	}

	if (count == 2)
	{
		return 1;
	}
    return 0;
}

// Function to check for a pair
int pair(int hand[]){
	int rankCount[13] = {0};
	for (int i = 0; i < 5; i++)
	{
		rankCount[getrank(hand[i])]++;
	}

	for (int i = 0; i < 13; i++)
	{
		if (rankCount[i] == 2)
		{
			return 1;
		}
	}
    return 0;
}
