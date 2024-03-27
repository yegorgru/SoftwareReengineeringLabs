/**
\file
\brief .cpp file of class MenuRender

implementation of MenuRender class
*/

#include "MenuRender.h"
#include "Assets.h"

namespace Docking::Client {
	MenuRender::MenuRender() :
		m_Rectangle(sf::Vector2f(200, 70)) 
	{
		m_TextPlay = sf::Text("Play", Assets::Get().GetFont(), 20);
		m_TextLeaders = sf::Text("Leaders", Assets::Get().GetFont(), 20);
		m_TextExit = sf::Text("Exit", Assets::Get().GetFont(), 20);
		m_TextPlay.setPosition(30, 100);
		m_TextLeaders.setPosition(30, 300);
		m_TextExit.setPosition(30, 500);
		m_Rectangle.setFillColor(sf::Color(169, 126, 109));
	}

	void MenuRender::Draw()
	{
		auto& window = Render::GetWindow();
		window.clear(sf::Color(223, 236, 157));
		
		for (int i = 1; i <= 5; i += 2) {
			m_Rectangle.setPosition(20, i*100-20);
			window.draw(m_Rectangle);
		}

		window.draw(m_TextPlay);
		window.draw(m_TextLeaders);
		window.draw(m_TextExit);

		window.display();
	}
}