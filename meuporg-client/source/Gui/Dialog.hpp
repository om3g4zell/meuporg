#ifndef DIALOG_HPP
#define DIALOG_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include <vector>
#include <map>
#include <functional>

#include "../ResourceHolder.hpp"
#include "../ResourceId.hpp"

struct DialogChoice
{
    std::map<std::string, int> possibilities;
    std::function<void(int)> callback;
    std::string title = "Quel est votre choix";
};

class Dialog : public sf::Drawable, public sf::Transformable
{
    public:
        Dialog(kantan::FontHolder* fonts);

        virtual ~Dialog();

        void init();

        void update(sf::Time dt);

        void handleEvent(sf::Event e);

        void setText(std::string str);

        DialogChoice* addChoice();

        bool isFinished();

        void next();


    protected:

        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

        std::string arrow;

        void initChoice();

    private:

        kantan::FontHolder* fonts;

        sf::RectangleShape background;

        sf::Text text;

        sf::Text nextPageText;

        unsigned int itr;

        std::vector<std::string> texts;

        DialogChoice* choice;

        sf::Time timer;

        bool drawArrow;

        bool finished;

        bool choiceStep;

        sf::Text title;

        std::vector<sf::Text> choiceTexts;

};

#endif // DIALOG_HPP
