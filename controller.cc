#include "controller.h"
#include "model.h"
#include "player.h"
#include "card.h"
#include "joker.h"
#include "view.h"

Controller::Controller(Model * model) : model{model} {}

bool Controller::startTurn(int player) {
	return model->drawCard(player);
} // startTurn

void Controller::changeCard(int player, int rank, int value) {
	model->changeCard(player, rank, value);
} // changeCard

bool Controller::playReserve(int player) {
	if (model->getHeads().size() == 1) return false;
	if (model->getPlayers().at(player - 1).getReserve() != nullptr) {
		model->swapReserve(player);
		return false;
	} else {
		model->moveReserve(player);
		return true;
	} // if
} // playReserve

int Controller::playHead(int player, int head) {
	int headRank = model->getRankHead(head);
	int handRank = model->getRankDraw(player);
	int totalCards = model->getPlayers().at(player - 1).getDrawPile().size() + 
		model->getPlayers().at(player - 1).getDiscardPile().size();
	// check if hand value is less than head value, update state and continue turn if so
	if (handRank < headRank) {
		if (totalCards == 0 && model->getPlayers().at(player - 1).getReserve() == nullptr) View::winGame(player);
		model->updateHead(player, head);
		if (handRank == 1 && headRank == 14) return 0;
		return 1;
	// check if hand value is equal to head value, update state and end turn if so
	} else if (handRank == headRank) {
		if (totalCards == 0 && model->getPlayers().at(player - 1).getReserve() == nullptr) View::winGame(player);
		model->updateHead(player, head);
		return 0;
	// check if player wants to cut off head
	} else if (head == model->getHeads().begin()->first) {
		if (model->getPlayers().at(player - 1).getHand()->getSuit() == "J") return -1;
		for (auto & head : model->getHeads()) {
			if (handRank <= head.second.back()->getRankHead()) return -1;
		} // for
		model->cutOffHead(player);
		model->makeHeads(player);
		return 0;
	} else { // invalid move
		return -1;
	} // if
} // playHead

void Controller::endTurn(int player) {
	model->discardReserve(player);
} // endTurn
