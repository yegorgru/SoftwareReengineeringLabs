/**
\file
\brief .h file of class Server

definition of Server class
*/

#pragma once

#include <unordered_map>
#include <map>

#include <SFML/Network.hpp>

#include "Game.h"
#include "Player.h"
#include "PlayersStorage.h"

namespace Docking::Server {

    /**
    \brief main class that controls everything on Server side
    */
    class Server {
    public:
        /**
        \brief default server constructor

        creates NetworkManager, TcpSelector, TcpListener, first Game
        m_IsRunning == false
        */
        Server();

        /**
        \brief default destructor
        */
        virtual ~Server() noexcept = default;

    public:
        /**
        \brief run Server method

        launch main loop of server
        */
        void Run();
    
    private:
        using Players = std::unordered_map<int, Player>;
        using Games = std::unordered_map<int, Game>;
    private:
        bool m_IsRunning;                           ///<is server running bool

        PlayersStorage m_PlayersStorage;            ///<players storage
        Players m_Players;                          ///<connected players
        Games m_Games;                              ///<active games
       
        size_t m_UncompletedGame;                   ///<current uncompleted game

        NetworkManager<int>& m_NetworkManager;      ///<reference to NetworkManager<int>

        int m_NextIdPlayer;                         ///<id of next connected player
    };
}