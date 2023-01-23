#ifndef __MODEL_H__
#define __MODEL_H__
#include <vector>
#include <map>
#include <memory>
#include "player.h"

class Player;
class Card;

class Model {
	std::vector<Player> players;
	std::map<int, std::vector<std::shared_ptr<Card>>> heads;
	bool testMode;
    public:
	Model(int numPlayers, int numSuits, int numRank, bool testMode);
	
	// changes player's hand to a new card
	void changeCard(int player, int rank, int suit);

	// moves the card in player's hand to the selected head
	void updateHead(int player, int head);

	// inserts oldest head and reserve card into player's discard pile
	void cutOffHead(int player);

	// adds the top 2 cards from player's draw pile to the vector of heads
	void makeHeads(int player); 
	
	// moves card from draw pile to hand for player
	bool drawCard(int player);

	// moves the reserve card to the discard pile
	void discardReserve(int player);

	// swaps the hand and reserve card for player
	void swapReserve(int player);

	// moves the hand to reserve for player
	void moveReserve(int player);

	// returns players
	const std::vector<Player> & getPlayers() const;

	// returns heads
	const std::map<int, std::vector<std::shared_ptr<Card>>> & getHeads() const;

	// returns rank of the head
	int getRankHead(int head);

	// returns the rank of the player's hand
	int getRankDraw(int head);	
};

#endif
