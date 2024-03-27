/**
\file
\brief .cpp file of class Assets

implementation of Assets class
*/

#include "Assets.h"

#include <stdexcept> 

namespace Docking::Client{
	Assets::Assets() {
		if (!m_Font.loadFromFile("sansation.ttf")) {
			throw std::runtime_error("Failed to load font");
		}
	}

	sf::Font& Assets::GetFont()
	{
		return m_Font;
	}
}
