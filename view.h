#ifndef __VIEW_H__
#define __VIEW_H__

class Controller;
class Model;

class View {
	Model * model;
	Controller * controller;
    public:
	View(Model * model, Controller * controller);
	void printHeads();
	void printPlayers(int player, int turns);
	void play(int player, bool testMode); 
	static int getRank();
	static void winGame(int player);
	static int numPlayers();
	static void chooseCard(int & rank, int & suit);
};

#endif

