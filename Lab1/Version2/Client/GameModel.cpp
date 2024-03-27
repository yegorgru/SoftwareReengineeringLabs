/**
\file
\brief .cpp file of class GameModel

implementation of GameModel class
*/

#include "GameModel.h"

namespace Docking::Client {
	namespace {
		const int FirstPlayerElement = 1;
		const int SecondPlayerElement = 2;
		const int EmptyElement = 0;
	}

	GameModel::GameModel():
		m_Map(),
		m_Winner(0) 
	{
	}

	void GameModel::Restore()
	{
		for (size_t i = 0; i < m_Map.size(); i++) {
			for (size_t j = 0; j < m_Map.size(); j++)
			{
				if ((i == 0 || i == m_Map.size() - 1) && j > 1 && j < m_Map.size() - 2) {
					m_Map[i][j] = FirstPlayerElement;
				}
				else if ((j == 0 || j == m_Map.size() - 1) && i > 1 && i < m_Map.size() - 2) {
					m_Map[i][j] = SecondPlayerElement;
				}
				else {
					m_Map[i][j] = EmptyElement;
				}
			}
		}
		m_Winner = 0;
	}

	void GameModel::SetElement(int element, Position newPos, Position oldPos) {
		if (!(oldPos == Position{-1, -1})) {
			m_Map[oldPos.x][oldPos.y] = EmptyElement;
		}
		m_Map[newPos.x][newPos.y] = element;
	}

	void GameModel::SetWinner(int winner){
		m_Winner = winner;
	}

	int GameModel::GetElement(Position pos) {
		return m_Map[pos.x][pos.y];
	}

	int GameModel::GetWinner() {
		return m_Winner;
	}

	void GameModel::AddPlayer(const Player& player) {
		m_Players.push_back(player);
	}

	GameModel::Players& GameModel::GetPlayers()
	{
		return m_Players;
	}

	bool operator==(const GameModel::Position& left, const GameModel::Position& right) {
		return left.x == right.x && left.y == right.y;
	}
}