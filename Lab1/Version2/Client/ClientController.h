/**
\file
\brief .h file of class ClientController

definition of ClientController clas
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

namespace Docking::Client {

	/**
	\brief main controller class on client side

	launch other controllers
	*/
	class ClientController
	{		
	public:
		/**
		\brief ClientController constructor

		\param window reference to window of application
		*/
		ClientController() = default;
		ClientController(const ClientController&) = delete;
		ClientController(ClientController&&) = default;
		ClientController& operator=(const ClientController&) = delete;
		ClientController& operator=(ClientController&&) = default;

		/**
		\brief run application method

		launch Run() methods of other controllers
		*/
		void Run();

	private:
		Player m_Player;			///<information about player who launch application
	};
}
