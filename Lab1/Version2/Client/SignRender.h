/**
\file
\brief .h file of class SignRender

definition of SignRender clas
*/

#pragma once

#include <SFML/Graphics.hpp>

#include <string>

#include "Render.h"

namespace Docking::Client {

	/**
	\brief render class responsible for sign in/sign up

	Singleton<SignRender>, Render inheritant
	*/
	class SignRender : public Render
	{
	public:
		/**
		\brief SignRender constructor
		*/
		SignRender();
		SignRender(const SignRender&) = delete;
		SignRender(SignRender&&) = default;
		SignRender& operator=(const SignRender&) = delete;
		SignRender& operator=(SignRender&&) = default;

	public:

		/**
		\brief draw elements on m_Window

		override Render method
		*/
		void Draw() override;

		/**
		\brief sets focus on name/password field input

		\param focus if it==false, focus will be set on name field, else on password field
		*/
		void SetFocus(bool focus);

		/**
		\brief adds letter to field whith focus

		size of text can't be bigger than 10 letters
		\param letter added letter
		*/
		void AddLetter(char letter);

		/**
		\brief erases letter from field with focus
		*/
		void EraseLetter();

		/**
		\brief m_TextName text getter

		\return m_TextName text
		*/
		std::string GetName();

		/**
		\brief m_TextPassword text getter

		\return m_TextPassword text
		*/
		std::string GetPassword();

		/**
		\brief called in case of incorrect sign in/sign up

		clears m_TextName and draw borders of m_RectangleName in red
		*/
		void IncorrectSign();

	private:
		sf::RectangleShape m_RectangleName;		///<rectangle of name input
		sf::RectangleShape m_RectanglePassword;	///<rectangle of password input
		sf::RectangleShape m_RectangleSign;		///<rectangle of sign in/up buttons

		sf::Text m_TextName;					///<text of name input
		sf::Text m_TextPassword;				///<text of password input (represented with '*')
		sf::Text m_TextSignUp;					///<text of sign up button
		sf::Text m_TextSignIn;					///<text of sign in button
		sf::Text m_TextNameTitle;				///<text of title of name input
		sf::Text m_TextPasswordTitle;			///<text of title of password input

		bool m_Focus;							///<focus input (name/password)

		std::string m_Password;					///<entered password
	};
}

