#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <../NetworkValues.hpp>
#include <../PlayerInput.hpp>

class Game
{
    public:

        // Constructor
        Game();

        // Destructor
        virtual ~Game();

        // Returns true if the server is running, false otherwise.
        bool isRunning() const;

        // Initialisation
        void init();

        // Establish the communication with the server.
        void serverConnection();

        // Update
        void update(sf::Time dt);

    protected:
        // Connects to the server.
        void connectToServer(std::string username, sf::IpAddress ip);

    private:
        const unsigned int Version;
        sf::Time timeout;
        bool running;
};

#endif // GAME_HPP_INCLUDED