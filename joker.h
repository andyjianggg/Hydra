#ifndef __JOKER_H__
#define __JOKER_H__
#include "card.h"

class View;

class Joker: public Card {
	
    public:
	Joker(int suitValue, int rankValue);

	// returns the string "Joker"
	std::string printCard() override;
	
	// calls view to get a rank, and return it
	int getRankDraw() override;
};

#endif