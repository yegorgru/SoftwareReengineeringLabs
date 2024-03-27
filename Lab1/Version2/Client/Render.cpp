/**
\file
\brief .cpp file of class Render

implementation of Render class
*/

#include "Render.h"

namespace Docking::Client {
	sf::RenderWindow& Render::GetWindow() {
		static sf::RenderWindow m_Window = sf::RenderWindow(sf::VideoMode(640, 690), "Docking", sf::Style::Titlebar | sf::Style::Close);
		return m_Window;
	}
}