#ifndef PLAYER_H
#define PLAYER_H

#include "SgGame.h"
#include "SgHashTable.h"
//----------------------------------------------------------------------------
template<class Game, class Search> // here search is decltype(out created search)
class SgPlayer {					// it with the MoveType
public:
	SgPlayer() = default;

	SgPlayer(const SgGame<typename Game::StateType, typename Game::MoveType>& game, SgBlackWhite color, 
		SgSearch<typename Game::StateType, typename Game::MoveType, typename Search::HashDataType>* se,
		bool is_stat = false, bool is_hash = false)
		: m_extern_game(game), m_color(color), m_search(se),
		m_hash((is_hash) ?
						((is_stat) 
							? (new SgHashTable<typename Search::HashDataType>(new SgHashStatistics()))
							: (new SgHashTable<typename Search::HashDataType>()))
						: 0), m_time(0) { 
		if (color == SG_BLACK)
			m_search->setBlackHash(m_hash);
		else
			m_search->setWhiteHash(m_hash);
	}

	~SgPlayer() {
		delete m_intern_game; // the intern game created by last generateMove
		delete m_hash; // hash is in charge of deleting its own stat if there is
		delete m_search; // it's player's duty to delete search create by engine on heap
	}

	SgHashTable<typename Search::HashDataType>* getHash() {
		return m_hash; // if 0, no hash
	}

	double getAllSearchTime() const {
		return m_time;
	}

	typename Game::MoveType generateMove() {
		delete m_intern_game;
		m_intern_game = m_extern_game.copy();
		m_search->setSnap(m_intern_game);
		typename Game::MoveType move = m_search->generateMove();
		m_time += m_search->getSerachDuration();
		return move;
	}

private:
	const SgGame<typename Game::StateType, typename Game::MoveType>& m_extern_game;
	SgGame<typename Game::StateType, typename Game::MoveType>* m_intern_game;
	SgBlackWhite m_color;
	SgHashTable<typename Search::HashDataType>* m_hash;
	// here we can put base pointer or directly SearchType pointer
	SgSearch<typename Game::StateType, typename Game::MoveType, 
		typename Search::HashDataType>* m_search;
	double m_time;
};

//----------------------------------------------------------------------------
#endif // PLAYER_H