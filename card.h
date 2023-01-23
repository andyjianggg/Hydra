#ifndef __CARD_H__
#define __CARD_H__
#include <string>

class View;

class Card {
    protected:
	std::string suit;
	int rank;

    public:
	Card(int suitValue, int rankValue);

	virtual ~Card();

	// returns a string of the card value in printable form
	virtual std::string printCard();

	// returns the rank of the card in the hand
	virtual int getRankDraw();
	
	// returns the rank of the card in the head
	int getRankHead();
	
	// returns the suit of the card
	std::string getSuit() const;

	// returns a string of the card rank and suit
	std::string getValue();
};

#endif
