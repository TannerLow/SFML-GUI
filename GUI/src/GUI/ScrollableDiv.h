#pragma once
#include <SFML/Graphics.hpp>
#include "Div.h"

namespace gui {

class ScrollableDiv : public Div {
protected:
	sf::RectangleShape scrollbarBackground;
	sf::RectangleShape scrollbarUp;
	sf::RectangleShape scrollbarBar;
	sf::RectangleShape scrollbarDown;

public:
	ScrollableDiv(sf::Vector2u size, sf::ContextSettings settings = {});

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

} // end namespace gui
