#include "./TofeGame/TofeGame.h"
#include "./TofeGame/TofeHeuristic/TofeHeuristic.h"
#include "./Searchs/AlphaBetaSearch.h"
#include "./Searchs/RandomSearch.h"
#include <iostream>
#include <random>

using std::cout;
using std::cin;
using std::endl;

int main() {
	TofeGame game(4, 4, SG_WHITE);
	std::random_device rd;
	std::uniform_int_distribution<int> uni(0, 1);

	while (!game.endOfGame()) {
#ifdef HUMAN		
		game.print(cout);
#endif

	AlphaBetaSearch<TofeState, TofeMove>se(*game.copy(), 3);
	RandomSearch<TofeState, TofeMove>re(*game.copy());

#ifdef HUMAN		
		/** recommendation module, for human interface */
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
		}
		// cout << game.evaluate() << endl;
		/** human input module */
		char m;
		TofeMove move;
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
#endif	
#ifdef TEST	
		//TofeMove generate_move = se.generateMove();
		TofeMove generate_move = re.generateMove();
		if (generate_move.isNullMove())
			break;
		game.play(TofeMove(generate_move.getMovement()));
#endif	
		int rand = uni(rd);	
		if (rand == 0)
			game.play(TofeMove(game.pickOneRandomEmptyPos(), 2));
		else
			game.play(TofeMove(game.pickOneRandomEmptyPos(), 4));
	}
#ifdef HUMAN	
	cout << "end of game!" << endl;
	cout << "the max is " << game.getMaxBlock() << endl;
#endif
#ifdef TEST
	cout << game.getMaxBlock() << endl;
#endif
	return 0;
}