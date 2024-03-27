/**
\file
\brief .h file of class MenuController

definition of MenuController class
*/

#pragma once
#include "MenuRender.h"
#include "EnumCode.h"
#include "NetworkManager.h"
#include "Controller.h"

namespace Docking::Client{

	/**
	\brief controller class responsible for menu

	Controller inheritant
	*/
	class MenuController : public Controller
	{
	public:
		/**
		\brief MenuController constructor

		initiaize attriutes with their Get() methods
		*/
		MenuController();
		MenuController(const MenuController&) = delete;
		MenuController(MenuController&&) = default;
		MenuController& operator=(const MenuController&) = delete;
		MenuController& operator=(MenuController&&) = default;

	public:
		/**
		\brief run MenuController method

		override Controller method
		\return Code of controller to launch next or Code::Exit
		*/
		Code Run() override;

	private:
		MenuRender m_Render;				///<responsible for draw of window
		NetworkManager& m_NetworkManager;	///<responsible for communication with Server side
	};
}

