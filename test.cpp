#include "TofeGame.h"

#include <iostream>

using std::cout;
using std::cin;

int main() {
	TofeGame game(4, 4, SG_WHITE);
	char m;
	TofeMove move;
	while (true) {
		game.Print(cout);
		cin >> m;
		if (m == 'w')
			move = TofeMove(TofeMove::TOFE_UP);
		if (m == 's')
			move = TofeMove(TofeMove::TOFE_DOWN);
		if (m == 'a')
			move = TofeMove(TofeMove::TOFE_LEFT);
		if (m == 'd')
			move = TofeMove(TofeMove::TOFE_RIGHT);
		game.Play(move);	
		game.Play(TofeMove(game.PickOneRandomEmptyPos(), 2));
	}

	return 0;
}