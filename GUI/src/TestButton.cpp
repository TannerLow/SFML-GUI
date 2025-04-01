#include "TestButton.h"
#include <stdio.h>

TestButton::TestButton(sf::Vector2u size, sf::IntRect visibleWindow, sf::ContextSettings settings) {
	div = new gui::Div(size, visibleWindow, settings);
	clickEnabled = true;
	hoverable = true;

	buttonGfx.setSize({ 150, 100 });
	buttonGfx.setFillColor(sf::Color::Cyan);
	div->elements.push_back(&buttonGfx);
}

void TestButton::click(sf::Vector2f mousePos, sf::Mouse::Button button) {
	if (containedByDiv(mousePos)) {
		printf("Clicked the button\n");
		isDown = true;
	}
}

void TestButton::releaseClick(sf::Vector2f mousePos, sf::Mouse::Button button) {

}

void TestButton::handleHover(sf::Vector2f mousePos) {
	if (hoverable and div) {
		if (div->visiblyContains(getInverseTransform().transformPoint(mousePos))) {
			buttonGfx.setFillColor(sf::Color::Magenta);
		}
		else {
			buttonGfx.setFillColor(sf::Color::Cyan);
		}
	}
}

void TestButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	gui::Button::draw(target, states);

	//states.transform *= getTransform();
}
