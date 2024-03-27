/**
\file
\brief .cpp file of class ClientController

implementation of ClientController class
*/

#include "ClientController.h"
#include "SignController.h"
#include "LeadersController.h"
#include "GameController.h"
#include "MenuController.h"

namespace Docking::Client {
	void ClientController::Run() {
		GameController gameController;
		LeadersController leadersController;
		MenuController menuController;
		SignController signController;
		Code code = signController.Run(m_Player);
		while (true) {
			switch (code) {
			case Code::Exit: {
				sf::Packet closed;
				closed << static_cast<int>(ClientCode::ClosedWindow);
				NetworkManager::Get().Send(closed);
				Render::GetWindow().close();
				return;
			}
			case Code::Menu: {
				code = menuController.Run();
				break;
			}
			case Code::PlayGame: {
				gameController.Restore();
				code = gameController.Run();
				break;
			}
			case Code::Leaders: {
				leadersController.SetPlayer(m_Player);
				code = leadersController.Run();
				break;
			}
			}
		}
	}
}