#include "ScrollEndButton.h"

namespace gui {

ScrollEndButton::ScrollEndButton(
	sf::Vector2u size,
	ScrollDirection direction,
	ScrollBarButton* scrollBarButton,
	sf::IntRect visibleWindow,
	sf::ContextSettings settings
) {
	div = new gui::Div(size, visibleWindow, settings);
	clickEnabled = true;
	hoverable = true;
	this->direction = direction;
	barButton = scrollBarButton;

	if (direction == ScrollDirection::UP_RIGHT) {
		// TODO texture rotation
	}
	else {

	}

	buttonGfx.setSize(sf::Vector2f(size));
	buttonGfx.setFillColor(sf::Color::White);
	div->elements.push_back(&buttonGfx);

	holdLimiter.setLimit(30);
}

void ScrollEndButton::click(sf::Vector2f mousePos, sf::Mouse::Button button) {
	if (clickEnabled and containedByDiv(mousePos)) {
		isDown = true;
	}
}

void ScrollEndButton::releaseClick(sf::Vector2f mousePos, sf::Mouse::Button button) {
	isDown = false;
}

void ScrollEndButton::handleHover(sf::Vector2f mousePos) {
	if (hoverable and div) {
		if (isDown or div->visiblyContains(getInverseTransform().transformPoint(mousePos))) {
			buttonGfx.setFillColor(sf::Color::Yellow);
		}
		else {
			buttonGfx.setFillColor(sf::Color::White);
		}
	}
}

void ScrollEndButton::update() {
	if (isDown) {
		if (holdLimiter.isReady()) {
			if (barButton) {
				barButton->moveBar(direction);
			}
		}
	}
}

void ScrollEndButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	gui::Button::draw(target, states);
}

}
