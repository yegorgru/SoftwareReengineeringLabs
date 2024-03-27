/**
\file
\brief .cpp file of class GameRender

implementation of GameRender class
*/

#include "GameRender.h"
#include "Assets.h"


namespace Docking::Client {
	GameRender::GameRender(GameModel& model) :
		m_GameModel(model),
		m_Square(sf::Vector2f(75, 75))
	{
		Restore();
	}

	void GameRender::Draw()
	{
		auto& window = Render::GetWindow();
		window.clear(sf::Color(223, 236, 157));
		if (m_GameModel.GetPlayers().size() < 2) {
			window.draw(m_TextWaiting);
		}
		else if (m_TextEnd.getString().getSize() > 0) {
			window.draw(m_TextEnd);
		}
		else {
			const auto& players = m_GameModel.GetPlayers();
			std::string playersStr = players[0].GetName();
			while (playersStr.size() < 10) {
				playersStr += '.';
			}
			playersStr += ".........." + std::to_string(players[0].GetWins());
			playersStr += "                                  ";
			playersStr += std::to_string(players[1].GetWins()) + "..........";
			for (size_t i = 0; i < 10 - players[1].GetName().size(); i++) {
				playersStr += '.';
			}
			playersStr += players[1].GetName();
			m_TextPlayers.setString(playersStr);
			window.draw(m_TextPlayers);
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++)
				{
					m_Square.setPosition(i * m_ElementSize, 50 + j * m_ElementSize);

					if (m_GameModel.GetElement({ i, j }) == 1) {
						m_Square.setFillColor(sf::Color(153, 255, 204));
					}
					else if (m_GameModel.GetElement({ i, j }) == 2) {
						m_Square.setFillColor(sf::Color(0, 76, 153));
					}

					if (m_GameModel.GetElement({ i, j })) {
						window.draw(m_Square);
					}
				}
			}
		}

		window.display();
	}

	int GameRender::GetElementSize() {
		return m_ElementSize;
	}

	void GameRender::SetEndText(const std::string& text) {
		m_TextEnd.setString(text);
	}

	void GameRender::Restore() {
		m_Square.setOutlineThickness(5);
		m_Square.setOutlineColor(sf::Color::Black);
		m_ElementSize = 80;
		m_TextWaiting = sf::Text("Waiting for opponent", Assets::Get().GetFont(), 50);
		m_TextWaiting.setPosition(50, 300);
		m_TextPlayers = sf::Text("", Assets::Get().GetFont(), 30);
		m_TextPlayers.setPosition(30, 10);
		m_TextPlayers.setFillColor(sf::Color::Black);
		m_TextEnd = sf::Text("", Assets::Get().GetFont(), 50);
		m_TextEnd.setPosition(100, 300);
		m_TextEnd.setFillColor(sf::Color::Red);
	}
}