/**
\file
\brief .h file of class LeadersController

definition of LeadersController class
*/

#pragma once

#include "LeadersRender.h"
#include "NetworkManager.h"
#include "EnumCode.h"
#include "Controller.h"

namespace Docking::Client {

	/**
	\brief controller class responsible for leaders board

	Controller inheritant
	*/
	class LeadersController : public Controller
	{
	public:
		/**
		\brief LeadersController constructor

		initiaize attriutes with their Get() methods
		*/
		LeadersController();
		LeadersController(const LeadersController&) = delete;
		LeadersController(LeadersController&&) = default;
		LeadersController& operator=(const LeadersController&) = delete;
		LeadersController& operator=(LeadersController&&) = default;

	public:
		/**
		\brief run LeadersController method

		override Controller method
		\return Code of controller to launch next or Code::Exit
		*/
		Code Run() override;

		void SetPlayer(const Player& player);

	private:
		LeadersRender m_Render;				///<responsible for draw of window
		NetworkManager& m_NetworkManager;	///<responsible for communication with Server side
	};
}
