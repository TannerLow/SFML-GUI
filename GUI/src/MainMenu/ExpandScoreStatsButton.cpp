#include "ExpandScoreStatsButton.h"

namespace o2 {

// Assumes screen space of 1920x1080
ExpandScoreStatsButton::ExpandScoreStatsButton() {
	clickEnabled = true;
	div = new gui::Div({40, 40});
	
	buttonGfx.setSize({40, 40});
	buttonGfx.setFillColor(sf::Color::Black);

	div->elements.push_back(&buttonGfx);
}

void ExpandScoreStatsButton::click(sf::Vector2f mousePos, sf::Mouse::Button button) {
	if (containedByDiv(mousePos)) {
		isDown = !isDown;
		printf("Clicked ExpandMapInfoButton at relative coords: %.2f %.2f\n", mousePos.x, mousePos.y);
	}
}

void ExpandScoreStatsButton::releaseClick(sf::Vector2f mousePos, sf::Mouse::Button button) {

}

void ExpandScoreStatsButton::handleHover(sf::Vector2f mousePos) {

}

void ExpandScoreStatsButton::update() {

}

void ExpandScoreStatsButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	gui::Button::draw(target, states);
}

}
