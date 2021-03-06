#include "GUIButtonPool.hpp"

namespace kantan
{
	GUIButtonPool::GUIButtonPool(sf::RenderWindow* window, FontHolder* fonts)
		: m_window(window)
		, m_fonts(fonts)
		, m_useCustomView(false)
	{
	}

	GUIButtonPool::~GUIButtonPool()
	{
	}

	void GUIButtonPool::addButton(std::string name, sf::Vector2f centerPosition, sf::Vector2f size, std::string textString, unsigned int fontId, unsigned int charSize, sf::Color backgroundColor, sf::Color hoverBackgroundColor, std::function<void()> fn)
	{
		sf::Text text;
		text.setFont(m_fonts->get(fontId));
		text.setCharacterSize(charSize);
		text.setString(textString);
		centerOrigin(text);
		text.setPosition(centerPosition.x, centerPosition.y);

		sf::RectangleShape shape;

		if(size != sf::Vector2f(0.f, 0.f))
			shape.setSize(size);
		else
			shape.setSize(sf::Vector2f(text.getGlobalBounds().width + 20.f, text.getGlobalBounds().height + 15.f));

		shape.setFillColor(backgroundColor);
		centerOrigin(shape);
		shape.setPosition(centerPosition);

		m_buttons[name] = {shape, text, backgroundColor, hoverBackgroundColor, fn};
	}

	void GUIButtonPool::addButton(std::string name, Button button)
	{
		m_buttons[name] = button;
	}

	void GUIButtonPool::removeButton(std::string name)
	{
		auto it = m_buttons.find(name);
		if(it != m_buttons.end())
			m_buttons.erase(it);
	}

	void GUIButtonPool::update()
	{
		// Update hover color.
		for(auto itr(m_buttons.begin()) ; itr != m_buttons.end() ; ++itr)
		{
			sf::FloatRect hitbox = itr->second.shape.getGlobalBounds();
			hitbox.left += getPosition().x;
			hitbox.top += getPosition().y;
			sf::Vector2i rawMousePosition = sf::Mouse::getPosition(*m_window);

			sf::Vector2f mousePosition = m_window->mapPixelToCoords(rawMousePosition);

			if(m_useCustomView)
				mousePosition = m_window->mapPixelToCoords(rawMousePosition, m_customView);

			if(hitbox.contains(mousePosition))
				itr->second.shape.setFillColor(itr->second.hoverColor);
			else
				itr->second.shape.setFillColor(itr->second.color);
		}
	}

	void GUIButtonPool::handleEvent(sf::Event event)
	{
		if(event.type == sf::Event::MouseButtonPressed)
		{
			for(std::pair<std::string, Button> b_pair : m_buttons)
			{
				sf::FloatRect hitbox = b_pair.second.shape.getGlobalBounds();

				// Execute callback if the button is clicked.
				if(hitbox.contains(event.mouseButton.x, event.mouseButton.y))
				   (b_pair.second.fn)();
			}
		}
	}

	void GUIButtonPool::setCustomView(const sf::View& v)
	{
		m_useCustomView = true;
		m_customView = v;
	}

	void GUIButtonPool::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		for(std::pair<std::string, Button> b_pair : m_buttons)
		{
			window.draw(b_pair.second.shape, states);
			window.draw(b_pair.second.text, states);
		}
	}
} // namespace kantan.
