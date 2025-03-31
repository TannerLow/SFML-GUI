#include "ScrollableDiv.h"

namespace gui {

ScrollableDiv::ScrollableDiv(sf::Vector2u size, sf::ContextSettings settings) 
	: Div(size) {

	scrollbarBackground.setSize({15, (float)size.y});
	scrollbarUp.setSize({15, 15});
	scrollbarBar.setSize({15, 15});
	scrollbarDown.setSize({15, 15});

	scrollbarBackground.setFillColor(sf::Color(0xF0, 0xF0, 0xF0));
	scrollbarUp.setFillColor(sf::Color(0xF0, 0xF0, 0xF0));
	scrollbarBar.setFillColor(sf::Color(0xF0, 0xF0, 0xF0));
	scrollbarDown.setFillColor(sf::Color(0xF0, 0xF0, 0xF0));
}

void ScrollableDiv::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	renderTexture.clear(sf::Color::Transparent);
	for (const auto& element : elements) {
		renderTexture.draw(*element, states);
	}
	renderTexture.display();

	states.transform *= getTransform();
	sf::Sprite sprite(renderTexture.getTexture());
	target.draw(sprite, states);
}

}
