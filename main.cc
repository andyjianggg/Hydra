#include "model.h"
#include "controller.h"
#include "view.h"

int main(int argc, char * argv[]) {
	// default values with no command line arguments
	bool testMode = false;
	int numSuits = 4;
	int numRank = 13;
	// handle command line arguments
	for (int i = 1; i < argc; i++) {
		std::string arg{argv[i]};
		if (arg == "-testing") testMode = true;
		if (arg[0] == '-') {
			if (arg[1] == 's') numSuits = std::stoi(arg.substr(2));
			else if (arg[1] == 'r') numRank = std::stoi(arg.substr(2));
		} // if
	} // for
	int numPlayers;
        try {
		numPlayers = View::numPlayers();
	} catch (std::runtime_error & e) {
		return 0;
	} // try
	Model model(numPlayers, numSuits, numRank, testMode);
	Controller controller(&model);
	View view(&model, &controller);
	try {
		int player = 1;
		while (true) {
			if (player == numPlayers) player = 1;
			else player++;
			view.play(player, testMode);
		} // while
	} catch (std::runtime_error & e) {
		return 0; 
	} // try
} // main
