#include "./TofeGame/TofeGame.h"
#include "./TofeGame/TofeHeuristic/TofeHeuristic.h"
#include "./Searchs/AlphaBetaSearch.h"
#include "./Searchs/RandomSearch.h"
#include "SgPlayer.h"
#include "SgHashTable.h"

#include <iostream>
#include <random>
#include <string>

//----------------------------------------------------------------------------

#define TEST

using std::cout;
using std::cin;
using std::endl;

int main(int argc, char const *argv[]) {
	TofeGame game(4, 4, SG_WHITE);

	int depth = std::stoi(argv[1]);
	bool is_stat = std::stoi(argv[2]);
	bool is_hash = std::stoi(argv[3]);

	AlphaBetaSearch<decltype(game)::StateType, decltype(game)::MoveType>se(depth); // here we create se with no hash table

	SgPlayer<decltype(game), decltype(se)> b_player(game, SG_BLACK, &se, is_stat, is_hash);
	SgPlayer<decltype(game), decltype(se)> w_player(game, SG_WHITE, &se, is_stat, is_hash);

	std::random_device rd;
	std::uniform_int_distribution<int> uni(0, 1);

	while (!game.endOfGame()) {
#ifdef DEBUG		
		game.print(cout);
#endif

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
		decltype(game)::MoveType generate_move = w_player.generateMove();
		//TofeMove generate_move = re.generateMove();
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
	cout << game.getMaxBlock()<< "\t" << se.getSerachDuration() << endl;
#endif

if (is_stat) {
	cout << "-----------------------------------" << endl;
	cout << "black hash stats" << endl;
	cout << *b_player.getHash()->getStatistics() << endl;
	cout << "-----------------------------------" << endl;
	cout << *w_player.getHash()->getStatistics() << endl;
}

	return 0;
}