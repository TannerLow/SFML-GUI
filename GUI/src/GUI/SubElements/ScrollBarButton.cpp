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

	buttonGfx.setSize(sf::Vector2f(size));
	buttonGfx.setFillColor(sf::Color::Cyan);
	div->elements.push_back(&buttonGfx);
}

void ScrollBarButton::click(sf::Vector2f mousePos, sf::Mouse::Button button) {
	if (clickEnabled and containedByDiv(mousePos)) {
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
	isDown = false;
}

void ScrollBarButton::handleHover(sf::Vector2f mousePos) {
	if (hoverable and div) {
		if (isDown or div->visiblyContains(getInverseTransform().transformPoint(mousePos))) {
			buttonGfx.setFillColor(sf::Color::Magenta);
		}
		else {
			buttonGfx.setFillColor(sf::Color::Cyan);
		}
	}

	if (attachedToMouse) {
		if (!dragLockedX) {
			float delta = mousePos.x - dragReference.x;
			if ((dragMinX <= mousePos.x or delta < 0) and (mousePos.x <= getHighestPointOfBar() or delta > 0)) {
				move({ delta, 0 });
				sf::Vector2f pos = getPosition();
				if (pos.x > dragMaxX) {
					setPosition({ dragMaxX, pos.y });
				}
				else if (pos.x < dragMinX) {
					setPosition({ dragMinX, pos.y });
				}
			}
			dragReference.x = mousePos.x;
		}
		if (!dragLockedY) {
			if (dragMinY <= mousePos.y and mousePos.y <= getHighestPointOfBar()) {
				move({ 0, mousePos.y - dragReference.y });
				sf::Vector2f pos = getPosition();
				if (pos.y > dragMaxY) {
					setPosition({ pos.x, dragMaxY });
				}
				else if (pos.y < dragMinY) {
					setPosition({ pos.x, dragMinY });
				}
			}
			dragReference.y = mousePos.y;
		}
	}
}

void ScrollBarButton::moveBar(ScrollDirection direction) {
	sf::Vector2f pos = getPosition();
	if (direction == ScrollDirection::UP_RIGHT) {
		if (side == ScrollSide::Vertical) {
			float totalBarLength = dragMaxY - dragMinY;
			move({0, -totalBarLength * 0.02f});
			if (getPosition().y < dragMinY) {
				setPosition({ pos.x, dragMinY });
			}
		}
		else { // Horizontal
			float totalBarLength = dragMaxX - dragMinX;
			move({ totalBarLength * 0.02f, 0 });
			if (getPosition().x > dragMaxX) {
				setPosition({ dragMaxX, pos.y });
			}
		}
	}
	else { // DOWN_LEFT
		if (side == ScrollSide::Vertical) {
			float totalBarLength = dragMaxY - dragMinY;
			move({ 0, totalBarLength * 0.02f });
			if (getPosition().y > dragMaxY) {
				setPosition({ pos.x, dragMaxY });
			}
		}
		else { // Horizontal
			float totalBarLength = dragMaxX - dragMinX;
			move({ -totalBarLength * 0.02f, 0 });
			if (getPosition().x < dragMinX) {
				setPosition({ dragMinX, pos.y });
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

// Lowest Y value
float ScrollBarButton::getLowestPointOfBar() const {
	if (side == ScrollSide::Vertical) {
		return dragMinY;
	}
	else {
		return dragMinX;
	}
}

float ScrollBarButton::getHighestPointOfBar() const {
	if (side == ScrollSide::Vertical) {
		return dragMaxY + buttonGfx.getSize().y;
	}
	else {
		return dragMaxX + buttonGfx.getSize().x;
	}
}

void ScrollBarButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	gui::Button::draw(target, states);
}

}
