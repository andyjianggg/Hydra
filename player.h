#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <vector>
#include <memory>
#include "card.h"

class Player {
	std::vector<std::shared_ptr<Card>> drawPile;
	std::vector<std::shared_ptr<Card>> discardPile;
	std::shared_ptr<Card> reserve;
	std::shared_ptr<Card> hand;

    public:
	Player(std::vector<std::shared_ptr<Card>> deck);
	
	// moves card at start of drawPile to hand
	bool drawCard(int player);
	
	// sets hand to nullptr
	void resetHand(); 

	// changes the current card in hand to a new card
	void changeHand(int rank, int suit);

	// returns false if swapped card in hand and reserve
	void swapReserve();

	// moves card from hand to reserve
	void moveReserve();

	// returns drawPile
	const std::vector<std::shared_ptr<Card>> & getDrawPile() const;
	
	// inserts cards into discard pile
	void insertDiscard(std::vector<std::shared_ptr<Card>> & cards);

	// returns discardPile
	const std::vector<std::shared_ptr<Card>> & getDiscardPile() const;

	// moves reserve card to discard pile
	void discardReserve();
	
	// moves hand card to discard pile
	void discardHand();

	// returns reserve
	std::shared_ptr<Card> getReserve() const;

	// returns hand
	std::shared_ptr<Card> getHand() const;

	// returns the rank of the card in hand
	int getRankDraw() const;
};

#endif
