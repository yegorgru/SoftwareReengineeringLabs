/**
\file
\brief .h file of class MenuRender

definition of MenuRender clas
*/

#pragma once

#include <SFML/Graphics.hpp>

#include "Render.h"

namespace Docking::Client {

	/**
	\brief render class responsible for menu

	Render inheritant
	*/
	class MenuRender : public Render
	{
	public:
		/**
		\brief MenuRender constructor
		*/
		MenuRender();
		MenuRender(const MenuRender&) = delete;
		MenuRender(MenuRender&&) = default;
		MenuRender& operator=(const MenuRender&) = delete;
		MenuRender& operator=(MenuRender&&) = default;

	public:
		/**
		\brief draw elements on m_Window

		override Render method
		*/
		void Draw() override;

	private:
		sf::RectangleShape m_Rectangle;		///<rectangle for buttons

		sf::Text m_TextPlay;				///<text for play button
		sf::Text m_TextLeaders;				///<text for leaders button
		sf::Text m_TextExit;				///<text for exit button
	};
}
