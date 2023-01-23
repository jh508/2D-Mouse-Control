#include <iostream>

#include "GameClasses.h"

int main() {


	//Initialize srand
	std::srand(static_cast<unsigned>(time(NULL)));

	// Instantiate Game Window
	Game game;

	//Game Loop
	while (game.getWindowIsOpen())
	{

		// Update
		game.Update();


		// Render
		game.Render();
	}
	// End of Application


	return 0;
}