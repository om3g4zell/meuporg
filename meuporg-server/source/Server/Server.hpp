#ifndef SERVER_HPP_INCLUDED
#define SERVER_HPP_INCLUDED

#include <iostream>
#include <SFML/Network.hpp>
#include "../ServerConfiguration.hpp"
#include "../NetworkValues.hpp"

/*
    Server class.
    This class manages the main functions of the server.
*/
class Server
{
    public:
        // Client structure.
        struct Client
        {
            sf::TcpSocket loginTcp;
            sf::TcpSocket gameTcp;
            sf::UdpSocket gameUdp;
            sf::Time timeout = sf::Time::Zero;

            bool loggedIn = false;

            unsigned int gameVersion = 0;
            std::string name = "";
            unsigned int accountId = 0;
        };

    public:
        // Constructor.
        Server();

        // Destructor.
        virtual ~Server();

        // Inits the server.
        void init();

        // Returns true if the server is running, false otherwise.
        bool isRunning() const;

        // Logs in the new players.
        void login(sf::Time dt);

        // Receives the input from the clients.
        void receiveInput();

        // Updates the server.
        void update(sf::Time dt);

        // Sends the update to the clients.
        void sendUpdate();

        // Returns the number of players currently online.
        unsigned int getNumberOfPlayers() const;

        // Return the maximum players capacity of the server.
        unsigned int getMaximumPlayersCapacity() const;

    protected:
        // Number of players connected and maximum number of players.
        unsigned int m_numberOfPlayers;
        unsigned int m_maximumPlayersCapacity;

        // Login TCP listener.
        sf::TcpListener m_loginListener;

        // List of the players.
        std::vector<Client*> m_clients;
};

#endif // SERVER_HPP_INCLUDED
