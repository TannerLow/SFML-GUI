#include "DraggableButton.h"
#include <stdio.h>

DraggableButton::DraggableButton(sf::Vector2u size, sf::IntRect visibleWindow, sf::ContextSettings settings) {
	div = new gui::Div(size, visibleWindow, settings);
	clickEnabled = true;
	hoverable = true;
	draggable = true;

	buttonGfx.setSize({ 150, 100 });
	buttonGfx.setFillColor(sf::Color::Cyan);
	div->elements.push_back(&buttonGfx);
}

void DraggableButton::click(sf::Vector2f mousePos, sf::Mouse::Button button) {
	if (containedByDiv(mousePos)) {
		printf("Clicked the button\n");
		isDown = true;

		if (draggable) {
			attachedToMouse = true;
			dragReference = mousePos;
		}
	}
}

void DraggableButton::releaseClick(sf::Vector2f mousePos, sf::Mouse::Button button) {
	attachedToMouse = false;
}

void DraggableButton::handleHover(sf::Vector2f mousePos) {
	if (hoverable and div) {
		if (div->visiblyContains(getInverseTransform().transformPoint(mousePos))) {
			buttonGfx.setFillColor(sf::Color::Magenta);
		}
		else {
			buttonGfx.setFillColor(sf::Color::Cyan);
		}
	}

	if (attachedToMouse) {
		if (!dragLockedX) {
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
		if (!dragLockedY) {
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

void DraggableButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	gui::Button::draw(target, states);
}
