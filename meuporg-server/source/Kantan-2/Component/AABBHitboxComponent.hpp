#ifndef KANTAN_AABBHITBOXCOMPONENT
#define KANTAN_AABBHITBOXCOMPONENT

#include <SFML/Graphics.hpp>
#include <string>

#include "Component.hpp"

namespace kantan
{
    /*
        AABB hitbox component.
    */
    class AABBHitboxComponent : public kantan::Component
    {
        public:
            // Ctor.
            AABBHitboxComponent(std::size_t ownerId);

            // Attributes.
            sf::FloatRect hitbox;
            bool isBlocking;
    };
} // namespace kantan.

#endif // KANTAN_AABBHITBOXCOMPONENT
