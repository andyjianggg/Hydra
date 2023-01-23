#include "card.h"

Card::Card(int suitValue, int rankValue) {
	switch(suitValue) {
		case 0: suit = "S"; break;
		case 1: suit = "H"; break;
		case 2: suit = "C";  break;
		case 3: suit = "D"; break;
		case 4: suit = "J"; break;
	} // switch
	rank = rankValue;
} // constructor

Card::~Card() {}

std::string Card::printCard() {
	std::string reStr;
	switch(rank) {
		case 1: reStr = "A"; break;
		case 11: reStr = "J"; break;
		case 12: reStr = "Q"; break;
		case 13: reStr = "K"; break;
		default: reStr = std::to_string(rank); break;
	} // switch
	return reStr + suit;		
} // printCard

int Card::getRankDraw() {
	return rank;
} // getRankDraw

int Card::getRankHead() {
	if (rank == 1) return 14;
	return rank;
} // getRankDiscard

std::string Card::getSuit() const {
	return suit;
} // getSuit

std::string Card::getValue() {
	std::string reStr;
	switch(rank) {
		case 1: reStr = "A"; break;
		case 11: reStr = "J"; break;
		case 12: reStr = "Q"; break;
		case 13: reStr = "K"; break;
		default: reStr = std::to_string(rank); break;
	} // switch
	return reStr + suit;	
} // getSuit
