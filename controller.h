#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

class Model;

class Controller {
	Model * model;
    public:
	// constructor
	Controller(Model * model);

	// returns true if the player has enough cards to draw, and draws a card
	// returns false if player has no more cards to draw but does not win
	bool startTurn(int player);
	
	// changes card in player's hand to a new card
	void changeCard(int player, int rank, int suit);

	// returns true if reserve was empty and hand was moved to reserve
	// returns false if reserve had a card, so the hand and reserve were swapped
	bool playReserve(int player);

	// returns true if given a valid move, and updates the model state
	// returns false if move was not valid
	int playHead(int player, int head);

	// performs the action at the end of the term, which is discard the
	// reserve if there is one
	void endTurn(int player);
};

#endif

