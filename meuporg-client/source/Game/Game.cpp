#include "Game.hpp"

Game::Game(sf::RenderWindow* window) : running(true)
    , token("")
    , udpPacketNumber(0)
    , udpPacketNumberReceive(0)
    , username("")
    , chat(window, &gameServerSocket, &fonts)
    , ping(0)
    , world(&textures, &fonts, &username, window, &gameServerSocket, &chat, &ping)
    , loosedPacket(0)
    , timeOutTimer(sf::Time::Zero)
    , timeOut(sf::seconds(5.f))
    , pingTimer(sf::Time::Zero)
    , pingCounter(sf::Time::Zero)
    , pingId(0)
    , state(State::CHARGEMENT)
    , loading(&informationSocket, &serverSocket, &gameServerSocket, &gameServerUdpSocket, &fonts, window, &state, &token, &username)
{
    //ctor
    fonts.load(ResourceId::SECRET_CODE_FONT, "assets/fonts/secrcode.ttf");
    fonts.load(ResourceId::MONOF_56, "assets/fonts/monof56.ttf");
    fonts.load(ResourceId::KENPIXEL, "assets/fonts/kenpixel.ttf");

    textures.load(ResourceId::SPARTIATE_TEXTURE, "assets/spartan_spritesheet.png");
    textures.load(ResourceId::ONE_PUNCH_MAN_TEXTURE, "assets/saitama_spritesheet.png");
    textures.load(ResourceId::TILESET, "assets/box.png");

    textures.load(ResourceId::BULLET, "assets/bullet2.png");
    textures.load(ResourceId::GRAVE, "assets/tombe.png");
    textures.load(ResourceId::TOWER, "assets/tour2.png");

    this->window = window;
}

Game::~Game()
{
    //dtor
    disconnectToGameServer();
}

void Game::init()
{
    loading.init();
    chat.setPosition(0, 400);
    chat.init();
    world.init();
}


void Game::disconnectToGameServer()
{
    sf::Packet packet;
    packet << NetworkValues::DISCONNECT;
    gameServerSocket.send(packet);
}

bool Game::isRunning() const
{
    return running;
}


void Game::receivePacket()
{
    timeOutTimer += sf::seconds(1/60.f);
    sf::Packet packet;
    //sf::Socket::Status status = gameServerSocket.receive(packet);

    //if(status == sf::Socket::Status::Done)
    while(gameServerSocket.receive(packet) == sf::Socket::Status::Done)
    {
        unsigned int netCode(0);
        packet >> netCode;

        switch(netCode)
        {
        case NetworkValues::NOTIFY:
            notificationPacket(&packet);
            break;
        }
    }

    packet.clear();
    sf::IpAddress ip;
    unsigned short int remotePort(0);
    //status = gameServerUdpSocket.receive(packet, ip, remotePort);

    //if(status == sf::Socket::Status::Done)
    while(gameServerUdpSocket.receive(packet, ip, remotePort) == sf::Socket::Status::Done)
    {
        timeOutTimer = sf::Time::Zero;
        unsigned int netCode(0);
        packet >> netCode;

        switch(netCode)
        {
        case NetworkValues::UPDATE:
            unsigned long long number;
            packet >> number;
            if(number - udpPacketNumberReceive > 1)
            {
                loosedPacket += (number - 1) - udpPacketNumberReceive;
                /*std::cout   << "[PACKET_LOSS] " << loosedPacket << " / " << udpPacketNumberReceive
                                            << " (" << (loosedPacket * 100.f) / (float)(udpPacketNumberReceive) << "%)" << std::endl;*/
            }
            if(number > udpPacketNumberReceive)
            {
                udpPacketNumberReceive = number;
                world.updateEntity(&packet);
            }
            break;
        }
    }
}

void Game::notificationPacket(sf::Packet* packet)
{
    unsigned int notifyType(0);
    *packet >> notifyType;

    switch(notifyType)
    {
        case NetworkValues::RECEIVE_CHAT_MESSAGE:
            {
                std::string message("");
                std::string username("");
                std::string chanel("");
                std::string text("");

                *packet >> username
                        >> chanel
                        >> text;
                /**
                TODO
                Canaux
                **/
                message  = "[" + username + "] " + text;
                chat.write(message);
            }
            break;
        case NetworkValues::PLAYER_CONNECTED :
            {
                std::string username("");
                std::string message("");

                *packet >> username;

                message = "[" + username + "] Viens de se connecter !";

                chat.write(message, sf::Color::Yellow);
            }
            break;
        case NetworkValues::PLAYER_DISCONNECTED :
            {
                std::string username("");
                std::string message("");

                *packet >> username;

                message = "[" + username + "] Viens de se deconnecter !";

                chat.write(message, sf::Color::Yellow);
            }
            break;
        case NetworkValues::ENTITY_REMOVED :
            {
                unsigned int entityId(0);
                unsigned long long id(0);
                *packet >> id
                        >> entityId;
                world.removeEntity(entityId);
                udpPacketNumberReceive = id;
            }
            break;
        case NetworkValues::LEVEL_UP :
            {
                unsigned int entityId(0);
                *packet >> entityId;
                std::string name = world.getEntityById(entityId)->getName();
                float level(0);
                *packet >> level;
                std::stringstream ss;
                ss << name << " viens de monter level " << (unsigned int)level;
                chat.write(ss.str(), sf::Color::Yellow);
            }
            break;
        case NetworkValues::PLAYER_MOVED_TO_WORLD:
            {
                unsigned int worldId(0);
                unsigned int mapId(0);

                *packet >> worldId
                        >> mapId;
                world.changeWorld(worldId, mapId);

                std::stringstream ss;
                ss << "Vous vous tel�portez au monde: " << (unsigned int)worldId;
                chat.write(ss.str(), sf::Color::Yellow);
            }
            break;
        case NetworkValues::KILL:
            {
                unsigned int killerId(0);
                unsigned int killedId(0);

                *packet >> killerId
                        >> killedId;

                std::string killer = world.getEntityById(killerId)->getName();
                std::string killed = world.getEntityById(killedId)->getName();

                std::stringstream ss;

                ss << killer << " a tu�: " << killed << " !";
                chat.write(ss.str(), sf::Color::Red);
                world.entityKilled(killedId);
            }
        default:
            break;
    }
}

void Game::sendInput()
{
    sf::Packet packet;
    packet << NetworkValues::INPUT
            << username
            << token
            << udpPacketNumber
            << playerInput.MoveUp
            << playerInput.MoveDown
            << playerInput.MoveLeft
            << playerInput.MoveRight
            << playerInput.MouseX
            << playerInput.MouseY
            << playerInput.aAttack
            << playerInput.eAttack
            << playerInput.leftClickPressed
            << playerInput.rightClickPressed;

    gameServerUdpSocket.send(packet, loading.getIp(), 22623);
    udpPacketNumber++;
}

void Game::testInput()
{
    playerInput.MoveUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
    playerInput.MoveDown = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    playerInput.MoveLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
    playerInput.MoveRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

    playerInput.aAttack = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    playerInput.eAttack = sf::Keyboard::isKeyPressed(sf::Keyboard::E);

    playerInput.leftClickPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    playerInput.rightClickPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);




    sf::Vector2i mouseposition = sf::Mouse::getPosition(*window);

    sf::Vector2f gameMousePosition = window->mapPixelToCoords(mouseposition);

    playerInput.MouseX = gameMousePosition.x;
    playerInput.MouseY = gameMousePosition.y;
}

void Game::receiveInformationPacket()
{
    sf::Packet packet;
    informationSocket.setBlocking(false);
    while(informationSocket.receive(packet) == sf::Socket::Status::Done)
    {
        unsigned int netCode(0);
        packet >> netCode;
        switch(netCode) {
            case NetworkValues::PING:
            {
                long long id;
                packet >> id;

                if(id == pingId)
                {
                    ping = static_cast<int>(pingCounter.asMilliseconds());
                    pingCounter = sf::Time::Zero;
                }
                break;
            }
        }
    }
}

void Game::update(sf::Time dt)
{
    switch(state)
    {
        case State::MENU:

        break;
        case State::CHARGEMENT:
            loading.update(dt);
        break;
        case State::JEU :
            if(!chat.isActive())
            {
                testInput();
            }
            else
            {
                playerInput.MoveUp = playerInput.MoveDown = playerInput.MoveLeft = playerInput.MoveRight = playerInput.aAttack = playerInput.eAttack = false;
            }

            sendInput();
            receivePacket();

            world.update(dt);
            chat.update();
        break;
    }
    if(timeOutTimer >= timeOut)
    {
        std::cout << "Connection timed out" << std::endl;
        running = false;
    }
}

void Game::updatePing(sf::Time dt)
{
    if(state == State::JEU) {
        if(pingTimer.asSeconds() >= 1)
        {
            sf::Packet packet;
            packet << NetworkValues::PING << ++pingId;
            informationSocket.send(packet);
            pingTimer -= sf::seconds(1.f);
            pingCounter = sf::Time::Zero;
        }

        pingTimer += dt;
        pingCounter += dt;
        receiveInformationPacket();
    }
}

void Game::EventHandle(sf::Event event)
{
    switch(state)
    {
    case State::JEU :
        chat.handleEvent(event);
        world.handleEvent(event);
        break;
    case State::CHARGEMENT :
        loading.eventHandle(event);
        break;
    case State::MENU :
        break;
    }
}

void Game::render(sf::RenderWindow* window)
{
    window->clear(sf::Color::Black);
    switch(state)
     {
         case State::MENU:
            break;
         case State::CHARGEMENT:
            window->draw(loading);
            break;
         case State::JEU:
            window->draw(world);
            break;
     }
    window->display();
}
