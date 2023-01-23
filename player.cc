#include "player.h"
#include "view.h"
#include "joker.h"
#include <algorithm>
#include <random>
#include <chrono>

Player::Player(std::vector<std::shared_ptr<Card>> deck) : drawPile{deck}, reserve{nullptr}, hand{nullptr} {}

bool Player::drawCard(int player) {
	if (drawPile.size() != 0) {
		hand = drawPile.back();
		drawPile.pop_back();
		return true;
	} else if (discardPile.size() != 0) {
		drawPile = std::move(discardPile);
		// taken from cplusplus.com/reference/algorithm/shuffle
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		shuffle(drawPile.begin(), drawPile.end(), std::default_random_engine(seed));
		hand = drawPile.back();
		drawPile.pop_back();
		return true;
	} else if (reserve != nullptr) {
		return false; 
	} else {
		// win game
		View::winGame(player);
		return false; 
	} // if
} // drawCard()

void Player::resetHand() {
	hand = nullptr;
} // resetHand

void Player::changeHand(int rank, int suit) {
	resetHand();
	if (suit == 4) hand = std::make_shared<Joker>(suit, rank);
	else hand = std::make_shared<Card>(suit, rank);
} // changeHand

void Player::swapReserve() {
	std::swap(hand, reserve);
} // swapReserve

void Player::moveReserve() {
	reserve = std::move(hand);
	resetHand();
} // moveReserve

const std::vector<std::shared_ptr<Card>> & Player::getDrawPile() const {
	return drawPile;
} // getDrawPile

// inserts cards into discard pile
void Player::insertDiscard(std::vector<std::shared_ptr<Card>> & cards) {
	discardPile.insert(discardPile.end(), cards.begin(), cards.end());
} // insertDiscard

const std::vector<std::shared_ptr<Card>> & Player::getDiscardPile() const {
	return discardPile;
} // getDiscardPile

void Player::discardReserve() {
	if (reserve != nullptr) {
		discardPile.emplace_back(std::move(reserve));
		reserve = nullptr;
	} // if
} // discardReserve

void Player::discardHand() {
	if (hand != nullptr) {
		discardPile.emplace_back(std::move(hand));
		hand = nullptr;
	} // if
} // discardHand

std::shared_ptr<Card> Player::getReserve() const {
	return reserve;
} // getReserve

std::shared_ptr<Card> Player::getHand() const {
	return hand;
} // getHand

int Player::getRankDraw() const {
	return hand->getRankDraw();
} // gerRankDraw

