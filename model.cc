#include "model.h"
#include "view.h"
#include "player.h"
#include "card.h"
#include "joker.h"
#include <algorithm>
#include <random>
#include <chrono>

Model::Model(int numPlayers, int numSuits, int numRank, bool testMode) : testMode{testMode} {
	int totalCards = numSuits * numRank + 2;
	auto tmpDeck = std::vector<std::shared_ptr<Card>>();
	// add a full deck for each player
	for (int i = 0; i < numPlayers; i++) {
		// loop for each suit
		for (int j = 0; j < numSuits; j++) {
			// loop for each rank
			for (int k = 1; k < numRank + 1; k++) {
				tmpDeck.emplace_back(std::make_shared<Card>(j, k));
			} // for
		} // for
		tmpDeck.emplace_back(std::make_shared<Joker>(4, 2));
		tmpDeck.emplace_back(std::make_shared<Joker>(4, 2));
	} // for
	// random shuffling taken from cplusplus.com/reference/algorithm/shuffle
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(tmpDeck.begin(), tmpDeck.end(), std::default_random_engine(seed));
	// distribute 54 (normal) cards to each player
	for (int i = 0; i < numPlayers; i++) {
		auto playerDeck = std::vector<std::shared_ptr<Card>>();
		// players.emplace_back(std::vector<std::shared_ptr<Card>>());
		for (int j = 0; j < totalCards; j++) {
			playerDeck.emplace_back(std::move(tmpDeck.at(totalCards * i + j)));
			// players.back().getDrawPile().emplace_back(std::move(tmpDeck.at(54 * i + j)));
		}
		players.emplace_back(playerDeck);
	}
	// make first move for player 1
	heads[1] = std::vector<std::shared_ptr<Card>>();
	players.front().drawCard(1);
	if (testMode) {
		int rank, suit;
		View::chooseCard(rank, suit);
		changeCard(1, rank, suit);
	} // if
	heads[1].emplace_back(players.front().getHand());
	players.front().resetHand();
} // constructor

void Model::changeCard(int player, int rank, int suit) {
	players.at(player - 1).changeHand(rank, suit);
} // changeCard

// moves the card in player's hand to the selected head
void Model::updateHead(int player, int head) {
	auto tmpCard = players.at(player - 1).getHand();
	heads[head].emplace_back(tmpCard);
	players.at(player - 1).resetHand();
} // updateHeads

// inserts oldest head, reserve, and hand into player's discard pile
void Model::cutOffHead(int player) {
	players.at(player - 1).insertDiscard(heads.begin()->second);
	players.at(player - 1).discardReserve();
	players.at(player - 1).discardHand();
} // cutOffHead

// adds the top 2 cards from player's draw pile to the vector of heads
// and removes the oldest head
void Model::makeHeads(int player) {
	for (int i = 0; i < 2; i++) {
		players.at(player - 1).drawCard(player);
		if (testMode) {
			int rank, suit;
			View::chooseCard(rank, suit);
			changeCard(player, rank, suit);
		} // if
		int headNum = heads.rbegin()->first + 1;
		heads[headNum] = std::vector<std::shared_ptr<Card>>();
		heads[headNum].emplace_back(players.at(player - 1).getHand());
		players.at(player - 1).resetHand();
	} // for
	heads.erase(heads.begin());
} // makeHeads

bool Model::drawCard(int player) {
	return players.at(player - 1).drawCard(player);
}

void Model::discardReserve(int player) {
	players.at(player - 1).discardReserve();
} // discardReserve

void Model::swapReserve(int player) {
	players.at(player - 1).swapReserve();
}

void Model::moveReserve(int player) {
	players.at(player - 1).moveReserve();
}

// returns players
const std::vector<Player> & Model::getPlayers() const {
	return players;
} // getPlayers

// return heads
const std::map<int, std::vector<std::shared_ptr<Card>>> & Model::getHeads() const {
	return heads;
} // getHeads

int Model::getRankHead(int head) {
	return heads[head].back()->getRankHead();
}

int Model::getRankDraw(int player) {
	return players.at(player - 1).getRankDraw();
}
