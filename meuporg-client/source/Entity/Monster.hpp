#ifndef MONSTER_Hpp
#define MONSTER_Hpp

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "../ResourceHolder.hpp"
#include "../ResourceId.hpp"
#include "EntityWithStats.hpp"
#include "Animation.hpp"

class Monster: public EntityWithStats
{
    public:
        Monster(kantan::TextureHolder* textures, kantan::FontHolder* fonts, std::string name, unsigned int id);
        virtual ~Monster();

        enum State {IDLE, WALKING, DEAD};

        enum Direction{UP, DOWN, LEFT, RIGHT};

        void setDirection();

        virtual void init();

        virtual void update(sf::Time dt);

        void setState(State state);

    protected:

        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

        State state;

        Direction direction;

        Animation a_MoveUp;
        Animation a_MoveDown;
        Animation a_MoveLeft;
        Animation a_MoveRight;

        sf::Vector2f velocityNormalized;

    private:
};

#endif // MONSTER_Hpp
