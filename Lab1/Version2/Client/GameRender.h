/**
\file
\brief .h file of class GameRender

definition of GameRender clas
*/


#pragma once

#include <SFML/Graphics.hpp>

#include "GameModel.h"
#include "Render.h"

namespace Docking::Client {

	/**
	\brief render class responsible for game

	Render inheritant
	*/
	class GameRender : public Render
	{
	public:
		/**
		\brief GameRender constructor

		call Restore method
		*/
		GameRender(GameModel& model);
		GameRender(const GameRender&) = delete;
		GameRender(GameRender&&) = default;
		GameRender& operator=(const GameRender&) = delete;
		GameRender& operator=(GameRender&&) = default;

	public:

		/**
		\brief draw elements on m_Window

		override Render method
		3 variants: waiting for opponent, somebody won or game proccess
		*/
		void Draw() override;

		/**
		\brief m_ElementSize getter

		\return m_ElementSize
		*/
		int GetElementSize();

		/**
		\brief set text when some player wins

		\param text string to set
		*/
		void SetEndText(const std::string& text);

		/**
		\brief restores all attributes for waiting variant
		*/
		void Restore();

	private:
		GameModel& m_GameModel;			///<logic model of game

		sf::RectangleShape m_Square;	///<square responsible for player's blocks

		sf::Text m_TextPlayers;			///<text in the top of window, names and wins of players

		sf::Text m_TextEnd;				///<text in the end of game, when somebody wins
		sf::Text m_TextWaiting;			///<text in the beginning of game, when player is waiting for opponent
		int m_ElementSize;				///<size of m_Square
	};
}
