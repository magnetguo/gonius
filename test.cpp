#include "./TofeGame/TofeGame.h"
#include "./TofeGame/TofeHeuristic/TofeHeuristic.h"
#include "Searchs/AlphaBetaSearch.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main() {
	freopen("result.txt", "w", stdout);
	TofeGame game(4, 4, SG_WHITE);
	//char m;
	//TofeMove move;
	while (!game.endOfGame()) {
		game.print(cout);
		//std::vector<TofeMove> moves;
		//game.generate(moves);
		AlphaBetaSearch<TofeState, TofeMove>se(*game.copy(), 29);
		/** recommendation module, for human interface
		switch (se.generateMove().getMovement()) {
		case TofeMove::TOFE_UP:
			cout << "TOFE_UP" << endl; break;
		case TofeMove::TOFE_DOWN:
			cout << "TOFE_DOWN" << endl; break;
		case TofeMove::TOFE_LEFT:
			cout << "TOFE_LEFT" << endl; break;
		case TofeMove::TOFE_RIGHT:
			cout << "TOFE_RIGHT" << endl; break;
		default:
			cout << "No recommendation!" << endl;
		}**/
		cout << game.evaluate() << endl;
		/** human input module
		cin >> m;
		if (m == 'w')
			move = TofeMove(TofeMove::TOFE_UP);
		if (m == 's')
			move = TofeMove(TofeMove::TOFE_DOWN);
		if (m == 'a')
			move = TofeMove(TofeMove::TOFE_LEFT);
		if (m == 'd')
			move = TofeMove(TofeMove::TOFE_RIGHT); 
		if(!game.play(move)) continue;
		**/
		TofeMove move = se.generateMove();
		if (move.isNullMove())
			break;
		game.play(TofeMove(move.getMovement()));
		
		//game.generate(moves);
		game.play(TofeMove(game.pickOneRandomEmptyPos(), 2));
	}
	cout << "end of game!" << endl;
	cout << "the max is " << game.getMaxBlock() << endl;
	return 0;
}