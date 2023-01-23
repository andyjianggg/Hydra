#include "joker.h"
#include "view.h"

Joker::Joker(int suitValue, int rankValue) : Card(suitValue, rankValue) {}

std::string Joker::printCard() {
	return "Joker";
} // printCard

int Joker::getRankDraw() {
	rank = View::getRank();
	return rank;
}