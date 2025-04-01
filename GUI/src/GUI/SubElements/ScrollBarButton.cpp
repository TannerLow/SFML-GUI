#include "ScrollBarButton.h"
#include <stdio.h>

namespace gui {

ScrollBarButton::ScrollBarButton(sf::Vector2u size, ScrollSide side, sf::Vector2f bounds, sf::IntRect visibleWindow, sf::ContextSettings settings) {
	div = new gui::Div(size, visibleWindow, settings);
	clickEnabled = true;
	hoverable = true;
	draggable = true;
	this->side = side;
	
	if (side == ScrollSide::Horizontal) {
		dragMinX = bounds.x;
		dragMaxX = bounds.y;
		dragLockedY = true;
	}
	else {
		dragMinY = bounds.x;
		dragMaxY = bounds.y;
		dragLockedX = true;
	}

	buttonGfx.setSize({ 150, 100 });
	buttonGfx.setFillColor(sf::Color::Cyan);
	div->elements.push_back(&buttonGfx);
}

void ScrollBarButton::click(sf::Vector2f mousePos, sf::Mouse::Button button) {
	if (containedByDiv(mousePos)) {
		printf("Clicked the button\n");
		isDown = true;

		if (draggable) {
			attachedToMouse = true;
			dragReference = mousePos;
		}
	}
}

void ScrollBarButton::releaseClick(sf::Vector2f mousePos, sf::Mouse::Button button) {
	attachedToMouse = false;
}

void ScrollBarButton::handleHover(sf::Vector2f mousePos) {
	if (hoverable and div) {
		if (div->visiblyContains(getInverseTransform().transformPoint(mousePos))) {
			buttonGfx.setFillColor(sf::Color::Magenta);
		}
		else {
			buttonGfx.setFillColor(sf::Color::Cyan);
		}
	}

	if (attachedToMouse) {
		if (div) {
			buttonGfx.setFillColor(sf::Color::Magenta);
		}

		if (!dragLockedX) {
			if (dragMinX <= mousePos.x and mousePos.x <= dragMaxX) {
				move({ mousePos.x - dragReference.x, 0 });
				sf::Vector2f pos = getPosition();
				if (pos.x > dragMaxX) {
					setPosition({ dragMaxX, pos.y });
				}
				else if (pos.x < dragMinX) {
					setPosition({ dragMinX, pos.y });
				}
				dragReference.x = mousePos.x;
			}
		}
		if (!dragLockedY) {
			if (dragMinY <= mousePos.y and mousePos.y <= dragMaxY) {
				move({ 0, mousePos.y - dragReference.y });
				sf::Vector2f pos = getPosition();
				if (pos.y > dragMaxY) {
					setPosition({ pos.x, dragMaxY });
				}
				else if (pos.y < dragMinY) {
					setPosition({ pos.x, dragMinY });
				}
				dragReference.y = mousePos.y;
			}
		}
	}
}

float ScrollBarButton::getScrollPercentage() const {
	if (side == ScrollSide::Horizontal) {
		float percent = (getPosition().x - dragMinX) / (dragMaxX - dragMinX);
		// NOTE can add snapping to 0/1 here
		return percent;
	}
	else {
		float percent = (getPosition().y - dragMinY) / (dragMaxY - dragMinY);
		// NOTE can add snapping to 0/1 here
		return percent;
	}
}

void ScrollBarButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	gui::Button::draw(target, states);
}

}
