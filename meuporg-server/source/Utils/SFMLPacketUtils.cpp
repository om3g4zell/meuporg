#include "SFMLPacketUtils.hpp"

// Reading.
sf::Packet& operator >>(sf::Packet& packet, std::size_t& x)
{
    sf::Uint32 ui32b;
    packet >> ui32b;
    
    x = (std::size_t)(ui32b);
    
    return packet;
}

sf::Packet& operator >>(sf::Packet& packet, sf::Time& time)
{
    sf::Int32 x;
    packet >> x;

    time = sf::milliseconds(x);

    return packet;
}

// Writing.
sf::Packet& operator >>(sf::Packet& packet, const std::size_t& x)
{
    sf::Uint32 ui32b;
    ui32b = (unsigned int)(x);
    
    return packet << ui32b;
}

sf::Packet& operator <<(sf::Packet& packet, const sf::Time& time)
{
    return packet << time.asMilliseconds();
}
