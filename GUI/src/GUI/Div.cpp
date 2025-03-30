#include "Div.h"
#include <stdio.h>

namespace gui {

Div::Div(sf::Vector2u size, sf::ContextSettings settings) {
	if (!renderTexture.resize(size, settings)) { // NOTE can apply antialiasing here
		printf("Failed to create RenderTexture for Div\n");
	}
}

void Div::click(sf::Vector2f mousePos) {
	if (clickEnabled) {
		sf::Vector2f relativeMousePos = getInverseTransform().transformPoint(mousePos);
		if (0 <= relativeMousePos.x and relativeMousePos.x <= renderTexture.getSize().x and
			0 <= relativeMousePos.y and relativeMousePos.y <= renderTexture.getSize().y) 
		{
			printf("Clicked Div at relative coords: %.2f %.2f\n", relativeMousePos.x, relativeMousePos.y);

			for (auto& element : elements) {
				Clickable* clickable = dynamic_cast<Clickable*>(element);
				if (clickable) {
					clickable->click(relativeMousePos);
				}
			}
		}
	}
}

void Div::handleHover(sf::Vector2f mousePos) {
	if (hoverable) {
		sf::Vector2f relativeMousePos = getInverseTransform().transformPoint(mousePos);
		if (0 <= relativeMousePos.x and relativeMousePos.x <= renderTexture.getSize().x and
			0 <= relativeMousePos.y and relativeMousePos.y <= renderTexture.getSize().y)
		{
			printf("Hovering over Div at relative coords: %.2f %.2f\n", relativeMousePos.x, relativeMousePos.y);

			for (auto& element : elements) {
				Clickable* clickable = dynamic_cast<Clickable*>(element);
				if (clickable) {
					clickable->handleHover(relativeMousePos);
				}
			}
		}
	}
}

void Div::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	renderTexture.clear(sf::Color::Transparent);
	for (const auto& element : elements) {
		renderTexture.draw(*element, states);
	}
	renderTexture.display();

	states.transform *= getTransform();
	sf::Sprite sprite(renderTexture.getTexture());
	target.draw(sprite, states);
}

} // end namespace gui

