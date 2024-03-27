/**
\file
\brief .h file of class SignController

definition of SignController class
*/

#pragma once

#include "SignRender.h"
#include "EnumCode.h"
#include "NetworkManager.h"
#include "Player.h"
#include "Controller.h"

namespace Docking::Client {

	/**
	\brief controller class responsible for sign in/sign up

	Controller inheritant
	*/
	class SignController : public Controller
	{
	public:
		/**
		\brief SignController constructor

		initiaize attriutes with their Get() methods
		*/
		SignController();
		SignController(const SignController&) = delete;
		SignController(SignController&&) = default;
		SignController& operator=(const SignController&) = delete;
		SignController& operator=(SignController&&) = default;

	public:
		/**
		\brief run SignController method

		override Controller method
		\return Code of controller to launch next or Code::Exit
		*/
		Code Run() override;

		/**
		\brief more useful for this class run method

		\param player reference to player, information after signing in/up will be write in it
		\return Code of controller to launch next or Code::Exit
		*/
		Code Run(Player& player);

	private:
		SignRender m_Render;				///<responsible for draw of window
		NetworkManager& m_NetworkManager;	///<responsible for communication with Server side
	};
}