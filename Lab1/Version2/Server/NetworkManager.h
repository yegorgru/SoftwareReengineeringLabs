/**
\file
\brief .h file of class NetworkManager<T>

definition and implementation of NetworkManager<T> class
*/

#pragma once

#include <iostream>
#include <fstream>

#include <SFML/Network.hpp>

#include "Singleton.h"

namespace Docking::Server {

    /**
    \brief manager class responsible for communication with Clients

    Id - for connection between player's id and its socket
    connecting to Client side, sending/receiving packets
    Singleton<NetworkManager<Id>> inheritant
    */
    template <typename Id>
    class NetworkManager : public Singleton<NetworkManager<Id>> {
    public:
        /**
        \brief checks if there is packet from player

        \param id expected player's id
        \return bool true if there is packet
        */
        bool IsReady(Id id);

        /**
        \brief connects player

        \param id player's id
        \param socket reference to player's socket
        */
        void ConnectPlayer(Id id, sf::TcpSocket& socket);

        /**
        \brief Semds packet to all players

        \param packet reference to packet to send
        */
        void Send(sf::Packet& packet);

        /**
        \brief Semds packet to player

        \param packet reference to packet to send
        \param id player's id
        */
        void Send(sf::Packet& packet, Id id);

        /**
        \brief Semds packet to player

        \param id player's id
        \param packet packet to write data in
        \return bool true if received
        */
        bool Receive(Id id, sf::Packet& packet);

        bool Wait();

        bool IsSelectorReady();

        bool AcceptNewSocket(Id id);

        sf::TcpSocket& GetLastSocket();
    private:

        /**
        \brief Semds packet to player

        \param selector reference to tcp socket selector
        */
        explicit NetworkManager();

        /**
        \brief default destructor
        */
        virtual ~NetworkManager() noexcept = default;

    private:
        using SocketsMap = std::unordered_map<Id, sf::TcpSocket*>;
        using SocketsStorage = std::list<sf::TcpSocket>;
    private:
        SocketsMap m_Sockets;                       ///<sockets of players

        unsigned short m_Port;                      ///<server's port
        sf::TcpListener m_Listener;                 ///<server's tcp listener
        sf::SocketSelector m_Selector;              ///<server's tcp selector
        SocketsStorage m_SocketsList;     ///<connected to server sockets

        friend Singleton<NetworkManager<Id>>;
    };

    template <typename PlayerId>
    NetworkManager<PlayerId>::NetworkManager()
    {
        std::ifstream fin("config.txt");
        fin >> m_Port;
        fin.close();

        m_Listener.listen(m_Port);
        m_Selector.add(m_Listener);
    }

    template <typename Id>
    bool NetworkManager<Id>::IsReady(Id id) {
        return m_Selector.isReady(*m_Sockets[id]);
    }

    template<typename Id>
    void NetworkManager<Id>::ConnectPlayer(Id id, sf::TcpSocket& socket) {
        m_Sockets[id] = &socket;
    }

    template<typename Id>
    void NetworkManager<Id>::Send(sf::Packet& packet) {
        for (auto& socketNode : m_Sockets) {
            if (socketNode.second->send(packet) != sf::Socket::Done) {
                std::cout << "Failed to send data to socket #{0}" << std::endl;
            }
        }
    }

    template<typename Id>
    void NetworkManager<Id>::Send(sf::Packet& packet, Id id) {
        if (m_Sockets[id]->send(packet) != sf::Socket::Done) {
            std::cout << "Failed to send packet" << std::endl;
        }
    }

    template<typename Id>
    bool NetworkManager<Id>::Receive(Id id, sf::Packet& packet) {
        if (m_Sockets[id]->receive(packet) == sf::Socket::Done) {
            return true;
        }
        return false;
    }

    template<typename Id>
    bool NetworkManager<Id>::Wait() {
        return m_Selector.wait();
    }

    template<typename Id>
    bool NetworkManager<Id>::IsSelectorReady() {
        if (m_Selector.isReady(m_Listener)) {
            m_SocketsList.emplace_back();
            return true;
        }
        else {
            return false;
        }
    }

    template<typename Id>
    bool NetworkManager<Id>::AcceptNewSocket(Id id) {
        if (m_Listener.accept(m_SocketsList.back()) == sf::Socket::Done) {
            ConnectPlayer(id, m_SocketsList.back());
            m_Selector.add(m_SocketsList.back());
            return true;
        }
        else {
            return false;
        }
    }

    template<typename Id>
    sf::TcpSocket& NetworkManager<Id>::GetLastSocket() {
        return m_SocketsList.back();
    }
}