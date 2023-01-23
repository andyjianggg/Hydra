#include "view.h"
#include "model.h"
#include "controller.h"
#include "player.h"
#include "card.h"
#include "joker.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <stdexcept>

View::View(Model * model, Controller * controller) : model{model}, controller{controller} {}

void View::printHeads() {
	std::cout << std::endl << "Heads:" << std::endl;
	for (auto & head: model->getHeads()) {
		std::cout << head.first << ": ";
		std::cout << head.second.back()->getValue();
		std::cout << " (" << head.second.size() << ")" << std::endl;
	} // for
	std::cout << std::endl;
} // printHeads()

void View::printPlayers(int playerNum, int turns) {
	std::cout << "Players:" << std::endl;
	int num = 1;
	for (auto & player: model->getPlayers()) {
		std::cout << "Player " << num << ": ";
		std::cout << player.getDrawPile().size() + player.getDiscardPile().size();
		std::cout << " (" << player.getDrawPile().size() << " draw, ";
		std::cout << player.getDiscardPile().size() << " discard)";
		if (playerNum  == num) {
			std::cout << " + 1 in hand, " << turns - 1 << " remaining, ";
			if (player.getReserve() == nullptr) {
				std::cout << "0 in reserve";
			} else {
				std::cout << "1 in reserve";
			}
		}
		std::cout << std::endl;
		num ++;
	} // for
	std::cout << std::endl;
} // printPlayers

void View::play(int player, bool testMode) {
	int turns = static_cast<int>(model->getHeads().size());
	printHeads();
	printPlayers(0, 0);
	std::cout << "Player " << player << ", it is your turn." << std::endl;
	for (int i = 0; i < turns; i++) {
		if (controller->startTurn(player)) {
			while (true) {
				printHeads();
				printPlayers(player, turns - i);
				if (testMode) {
					int rank, suit;
					View::chooseCard(rank, suit);
					controller->changeCard(player, rank, suit);
				} // if
				std::cout << "Player " << player << ", you are holding a ";
				std::cout << model->getPlayers().at(player - 1).getHand()->printCard();
				std::cout << ". Your move?" << std::endl;
				std::string input;
				std::cin >> input;
				if (std::cin.fail()) throw std::runtime_error("");
				try {
					int move = std::stoi(input);
					if (move == 0) {
						if (controller->playReserve(player)) break;
						else continue;
					} else if (move >= model->getHeads().begin()->first && move <= model->getHeads().rbegin()->first) {
						// gameState to determine if input was valid and if turn should continue
						int gameState = controller->playHead(player, move);
						if (gameState == 0) {
							controller->endTurn(player);
						       	return;
						} else if (gameState == 1) { 
							break;
						} // if
					}
					std::cerr << "Invalid move!" << std::endl;
				} catch (std::invalid_argument & e) {
					std::cerr << "Invalid move!" << std::endl;
				} // try
			} // while
		} // if
		std::cout << std::endl;
	} // for
	controller->endTurn(player);
}

int View::numPlayers() {
	while (true) {
		std::cout << "How many players?" << std::endl;
		std::string input;
		std::cin >> input;
		if (std::cin.fail()) throw std::runtime_error("");
		try {
			int players = std::stoi(input);
			if (players < 1) continue;
			else return players;
		} catch (std::invalid_argument & e) {
		}
	}
}

int View::getRank() {
	std::string input; 
	while (true) {
		std::cout << "Joker value?" << std::endl;
		std::cin >> input;
		if (std::cin.fail()) throw std::runtime_error("");
		if (input == "A") {
			return 1;
		} else if (input == "K") {
			return 13;
		} else if (input == "Q") {
			return 12;
		} else if (input == "J") {
			return 11;
		} else {
			try {
				int rank = std::stoi(input);
				if (rank >= 2 && rank <= 10) {
					return rank;
				} else {
					std::cerr << "Invalid value!" << std::endl;
				} // if
			} catch (std::invalid_argument & e) {
				std::cerr << "Invalid value!" << std::endl;
			} // try
		} // if
	} // while
} // getRank

void View::winGame(int player) {
	std::cout << "Player " << player << " wins!" << std::endl;
	throw std::runtime_error("");
} // winGame

void View::chooseCard(int & rank, int & suit) {
	std::string input;
	while (true) {
		std::cout << "Card value?" << std::endl;
		std::cin >> input;
		if (std::cin.fail()) throw std::runtime_error("");
		if (input == "A") {
		       	rank = 1;
		} else if (input == "K") {
			rank = 13;
		} else if (input == "Q") {
			rank = 12;
		} else if (input == "J") {
			rank = 11;
		} else if (input == "Joker") {
			rank = 2;
			suit = 4;
			break;
		} else {
			try {
				int value = std::stoi(input);
				if (value >= 2 && value <= 10) rank = value;
				else continue;
			} catch (std::invalid_argument & e) { continue; }
		} // if
		std::cout << "Suit?" << std::endl;
		std::cin >> input;
		if (std::cin.fail()) throw std::runtime_error("");
		if (input == "S") {
			suit = 0;
			break;
		} else if (input == "H") {
			suit = 1;
			break;
		} else if (input == "C") {
			suit = 2;
			break;
		} else if (input == "D") {
			suit = 3;
			break;
		} // if
	} // while
} // chooseCard
