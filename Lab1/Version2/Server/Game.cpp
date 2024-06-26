/**
\file
\brief .cpp file of class Game

implementation of Game class
*/

#include "Game.h"

namespace Docking::Server {
	namespace {
		const int FirstPlayerElement = 1;
		const int SecondPlayerElement = 2;
		const int EmptyElement = 0;
	}
	
    Game::Game() :
        m_NetworkManager(NetworkManager<int>::Get()),
        m_CurrentPlayer(0),
		m_Position{-1,-1},
		m_Winner(0){
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
    }

    void Game::ConnectPlayer(Player& player) {
		if (m_Players.size() == 0) {
			m_ElementId[FirstPlayerElement] = player.GetId();
			m_IdElement[player.GetId()] = FirstPlayerElement;
		}
		else {
			m_ElementId[SecondPlayerElement] = player.GetId();
			m_IdElement[player.GetId()] = SecondPlayerElement;
		}
		m_Players.push_back(&player);
    }

    void Game::RunNetwork(sf::Packet& received, ClientCode clientCode, int playerId) {
        if (!IsActive()) throw std::invalid_argument("Not active game");
		sf::Packet answer;
		if (clientCode == ClientCode::ClosedWindow || clientCode == ClientCode::ClosedGame) {
			if (m_Players.size() == 2) {
				EndGame(m_IdElement.at(AnotherPlayerId(playerId)));
				m_Players[m_Winner - 1]->SetWins(m_Players[m_Winner - 1]->GetWins() + 1);
				answer << static_cast<int>(ServerCode::EndGame) << m_Winner;
				m_NetworkManager.Send(answer, AnotherPlayerId(playerId));
				m_Players[m_IdElement[AnotherPlayerId(playerId)]-1]->SetGame(-1);
			}
			else {
				EndGame(0);
			}
			return;
		}

		else if (m_IdElement.at(playerId) != m_CurrentPlayer) return;
		if (clientCode == ClientCode::Position) {
			received >> m_Position.x >> m_Position.y;
		}
		else {
			MakeMove(clientCode);
		}
    }

	int Game::CurrentPlayer() const {
		return m_CurrentPlayer;
	}

	int Game::GetElement(int x, int y) const {
		return m_Map[x][y];
	}

	Game::Position Game::GetPosition() const {
		return m_Position;
	}

	void Game::SetPosition(int x, int y) {
		m_Position = { x,y };
	}

	void Game::SetElement(int element, Position pos) {
		m_Map[pos.x][pos.y] = element;
	}

	int Game::GetWinnerId() const	{
		return m_ElementId.at(m_Winner);
	}

	std::string Game::GetWinnerName() const {
		if (m_Winner) {
			return m_Players[m_Winner-1]->GetName();
		}
		throw std::invalid_argument("There isn't winner");
	}

	void Game::NextTurn()
	{
		m_CurrentPlayer = m_CurrentPlayer == FirstPlayerElement ? SecondPlayerElement : FirstPlayerElement;
	}

	void Game::MakeMove(ClientCode direction)
	{
		if (!IsCorrectMove(direction)) return;
		int enemy = m_CurrentPlayer == FirstPlayerElement ? SecondPlayerElement : FirstPlayerElement;
		int ally = m_CurrentPlayer;
		Position pos = GetPosition();
		int new_pos_x = pos.x, new_pos_y = pos.y;
		switch (direction) {
		case ClientCode::Left: {
			int counter = 0;
			int copy_pos_x = pos.x;
			while (copy_pos_x >= 0) {
				if (m_Map[copy_pos_x][pos.y]) {
					counter++;
				}
				copy_pos_x--;
			}
			copy_pos_x = pos.x;
			while (counter > 0) {
				if (copy_pos_x == -1 || m_Map[copy_pos_x][pos.y] == enemy) {
					counter = 0;
				}
				else if (m_Map[copy_pos_x][pos.y] == 0) {
					new_pos_x = copy_pos_x;
					counter--;
				}
				copy_pos_x--;
			}
			break;
		}
		case ClientCode::Right: {
			int counter = 0;
			int copy_pos_x = pos.x;
			while (copy_pos_x <= m_Map.size() - 1) {
				if (m_Map[copy_pos_x][pos.y]) {
					counter++;
				}
				copy_pos_x++;
			}
			copy_pos_x = pos.x;
			while (counter > 0) {
				if (copy_pos_x == m_Map.size() || m_Map[copy_pos_x][pos.y] == enemy) {
					counter = 0;
				}
				else if (m_Map[copy_pos_x][pos.y] == 0) {
					new_pos_x = copy_pos_x;
					counter--;
				}
				copy_pos_x++;
			}
			break;
		}
		case ClientCode::Up: {
			int counter = 0;
			int copy_pos_y = pos.y;
			while (copy_pos_y >= 0) {
				if (m_Map[pos.x][copy_pos_y]) {
					counter++;
				}
				copy_pos_y--;
			}
			copy_pos_y = pos.y;
			while (counter > 0) {
				if (copy_pos_y == -1 || m_Map[pos.x][copy_pos_y] == enemy) {
					counter = 0;
				}
				else if (m_Map[pos.x][copy_pos_y] == 0) {
					new_pos_y = copy_pos_y;
					counter--;
				}
				copy_pos_y--;
			}
			break;
		}
		case ClientCode::Down: {
			int counter = 0;
			int copy_pos_y = pos.y;
			while (copy_pos_y <= m_Map.size() - 1) {
				if (m_Map[pos.x][copy_pos_y]) {
					counter++;
				}
				copy_pos_y++;
			}
			copy_pos_y = pos.y;
			while (counter > 0) {
				if (copy_pos_y == 8 || m_Map[pos.x][copy_pos_y] == enemy) {
					counter = 0;
				}
				else if (m_Map[pos.x][copy_pos_y] == 0) {
					new_pos_y = copy_pos_y;
					counter--;
				}
				copy_pos_y++;
			}
			break;
		}
		default: {
			throw std::invalid_argument("Incorrect move code");
			break;
		}
		}
		if (pos.x != new_pos_x || pos.y != new_pos_y) {
			m_Map[pos.x][pos.y] = 0;
			m_Map[new_pos_x][new_pos_y] = m_CurrentPlayer;
			CheckClosed({ new_pos_x - 1, new_pos_y });
			CheckClosed({new_pos_x + 1, new_pos_y});
			CheckClosed({ new_pos_x, new_pos_y - 1 });
			CheckClosed({ new_pos_x, new_pos_y + 1 });
			IsEnd();
			m_Position = { new_pos_x,new_pos_y };

			sf::Packet answer;
			answer << static_cast<int>(ServerCode::SetPosition) <<
				m_CurrentPlayer <<
				m_Position.x << m_Position.y << pos.x << pos.y;
			m_NetworkManager.Send(answer, m_Players[0]->GetId());
			m_NetworkManager.Send(answer, m_Players[1]->GetId());
			if (!IsActive()) {
				EndGame(m_CurrentPlayer);
				m_Players[m_Winner - 1]->SetWins(m_Players[m_Winner - 1]->GetWins() + 1);
				sf::Packet packet;
				packet << static_cast<int>(ServerCode::EndGame) << m_Winner;
				m_NetworkManager.Send(packet, m_Players[0]->GetId());
				m_NetworkManager.Send(packet, m_Players[1]->GetId());
				m_Players[0]->SetGame(-1);
				m_Players[1]->SetGame(-1);
				return;
			}
			NextTurn();
			SetPosition(-1, -1);
		}
	}

	bool Game::IsEnd() {
		if (m_Winner) {
			return m_Winner;
		}
		std::set<std::pair<int, int>>elements;
		for (size_t i = 0; i < m_Map.size(); i++) {
			for (size_t j = 0; j < m_Map.size(); j++) {
				if (m_Map[i][j] == FirstPlayerElement) {
					elements.insert({ i,j });
					CheckElements({ int(i), int(j) }, FirstPlayerElement, elements);
					if (elements.size() == 8) {
						m_Winner = FirstPlayerElement;
						return true;
					}
					else {
						elements.clear();
						break;
					}
				}
			}
		}
		for (size_t i = 0; i < m_Map.size(); i++) {
			for (size_t j = 0; j < m_Map.size(); j++) {
				if (m_Map[i][j] == SecondPlayerElement) {
					elements.insert({ i,j });
					CheckElements({ int(i), int(j) }, SecondPlayerElement, elements);
					if (elements.size() == 8) {
						m_Winner = SecondPlayerElement;
						return true;
					}
					else {
						return false;
					}
				}
			}
		}
		return false;
	}

	bool Game::IsActive() const {
		return IsCompleted() && !m_Winner;
	}

	void Game::EndGame(int winner) {
		m_Winner = winner;
	}

	int Game::AnotherPlayerId(int id)
	{
		for (auto& player : m_Players) {
			if (player->GetId() != id) {
				return player->GetId();
			}
		}
		throw std::invalid_argument("Out of range");
	}

	void Game::Clear() {
		m_Players.clear();
		m_IdElement.clear();
		m_ElementId.clear();
	}

	bool Game::IsCompleted() const {
		return m_Players.size() == 2;
	}

	void Game::CheckElements(Position pos, int el, std::set<std::pair<int, int>>& elements)
	{
		if (pos.x - 1 >= 0 && m_Map[pos.x - 1][pos.y] == el && !elements.count({ pos.x - 1, pos.y })) {
			elements.insert({ pos.x - 1,pos.y });
			CheckElements({pos.x-1, pos.y}, el, elements);
		}
		if (pos.x + 1 <= 7 && m_Map[pos.x + 1][pos.y] == el && !elements.count({ pos.x + 1, pos.y })) {
			elements.insert({ pos.x + 1, pos.y });
			CheckElements({pos.x+1, pos.y}, el, elements);
		}
		if (pos.y - 1 >= 0 && m_Map[pos.x][pos.y - 1] == el && !elements.count({ pos.x, pos.y - 1 })) {
			elements.insert({ pos.x, pos.y - 1 });
			CheckElements({ pos.x, pos.y - 1 }, el, elements);
		}
		if (pos.y + 1 <= 7 && m_Map[pos.x][pos.y + 1] == el && !elements.count({ pos.x, pos.y + 1 })) {
			elements.insert({ pos.x, pos.y + 1 });
			CheckElements({ pos.x, pos.y + 1 }, el, elements);
		}
	}

	void Game::StartGame() {
		sf::Packet start;
		start << static_cast<int>(ServerCode::StartGame) << 1
			<< m_Players[0]->GetName() << m_Players[0]->GetWins() <<
			2 << m_Players[1]->GetName() << m_Players[1]->GetWins();
		m_NetworkManager.Send(start, m_Players[0]->GetId());
		m_NetworkManager.Send(start, m_Players[1]->GetId());
		m_CurrentPlayer = FirstPlayerElement;
	}

	bool Game::CheckClosed(Position pos) {
		if (pos.x >= 0 && pos.x <= 7 && pos.y >= 0 && pos.y <= 7 && m_Map[pos.x][pos.y]) {
			int enemy = m_Map[pos.x][pos.y] == 1 ? 2 : 1;
			if (pos.x - 1 >= 0 && m_Map[pos.x - 1][pos.y] != enemy) {
				return false;
			}
			if (pos.x + 1 <= 7 && m_Map[pos.x + 1][pos.y] != enemy) {
				return false;
			}
			if (pos.y - 1 >= 0 && m_Map[pos.x][pos.y - 1] != enemy) {
				return false;
			}
			if (pos.y + 1 <= 7 && m_Map[pos.x][pos.y + 1] != enemy) {
				return false;
			}
			this->m_Winner = enemy;
			return true;
		}
		return false;
	}
	
	bool Game::IsCorrectMove(ClientCode direction)
	{
		if (m_Position.x != -1) {
			if (direction == ClientCode::Left && m_Position.x > 0) {
				return true;
			}
			if (direction == ClientCode::Right && m_Position.x < 7) {
				return true;
			}
			if (direction == ClientCode::Up && m_Position.y > 0) {
				return true;
			}
			if (direction == ClientCode::Down && m_Position.y < 7) {
				return true;
			}
		}
		return false;
	}
}