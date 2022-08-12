#include <iostream>
#include "Game2048.h"
#include <vector>
#include <ctime>
#include <random>
#include <iostream>

using std::cout;		using std::cin;

int main()
{
	// initialize
	Game2048 game = Game2048();
	cout << "welcome to the game of 2048!\n";
	char move_c;

	// game-ing
	while (game.Moveable()) {
		game.Display();
		move_c = game.Move(cin);
		if (move_c == 'q') {
			break;
		}
		else if (move_c == '?') {
			continue;
		}
		else {
			game.Merge(move_c);
			game.Add();
		}
	}

	// game over
	game.Display();
	cout << "\n\nGAME OVER.  Your score is " << game.Score() << " !\n";

	return 0;
}

