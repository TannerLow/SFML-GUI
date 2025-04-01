#include "Div.h"
#include <stdio.h>

namespace gui {

Div::Div(sf::Vector2u size, sf::IntRect visibleWindow, sf::ContextSettings settings) {
	if (!renderTexture.resize(size, settings)) {
		printf("Failed to create RenderTexture for Div\n");
	}

	if (visibleWindow.size.x == 0 and visibleWindow.size.y == 0) {
		setVisibleWindow({ {0, 0}, sf::Vector2i(size) });
	}
	else {
		setVisibleWindow(visibleWindow);
	}
}

sf::FloatRect Div::getVisibleWindow() const {
	sf::View view = renderTexture.getView();
	return { view.getScissor().position.componentWiseMul(view.getSize()), view.getScissor().size.componentWiseMul(view.getSize())};
}

bool Div::contains(sf::Vector2f point) const {
	sf::Vector2f relativePos = getInverseTransform().transformPoint(point);
	return (0 <= relativePos.x and relativePos.x <= renderTexture.getSize().x and
		    0 <= relativePos.y and relativePos.y <= renderTexture.getSize().y);
}

bool Div::visiblyContains(sf::Vector2f point) const {
	sf::Vector2f relativePos = getInverseTransform().transformPoint(point);
	return getVisibleWindow().contains(relativePos);
}

void Div::click(sf::Vector2f mousePos, sf::Mouse::Button button) {
	if (clickEnabled) {
		if (contains(mousePos)) {
			sf::Vector2f relativeMousePos = getInverseTransform().transformPoint(mousePos);
			sf::FloatRect visibleWindow = getVisibleWindow();
			if (visibleWindow.contains(relativeMousePos)) {
				printf("Clicked Div at relative coords: %.2f %.2f\n", relativeMousePos.x, relativeMousePos.y);
				if (draggable) {
					attachedToMouse = true;
					dragReference = mousePos;
				}

				for (auto& element : elements) {
					Clickable* clickable = dynamic_cast<Clickable*>(element);
					if (clickable) {
						clickable->click(relativeMousePos, button);
					}
				}
			}
		}
	}
}

void Div::releaseClick(sf::Vector2f mousePos, sf::Mouse::Button button) {
	attachedToMouse = false;
	sf::Vector2f relativeMousePos = getInverseTransform().transformPoint(mousePos);
	for (auto& element : elements) {
		Clickable* clickable = dynamic_cast<Clickable*>(element);
		if (clickable) {
			clickable->releaseClick(relativeMousePos, button);
		}
	}
}

void Div::handleHover(sf::Vector2f mousePos) {
	if (hoverable) {
		sf::Vector2f relativeMousePos = getInverseTransform().transformPoint(mousePos);
		sf::FloatRect visibleWindow = getVisibleWindow();
		
		if (visibleWindow.contains(relativeMousePos)) {
			printf("Hovering over Div at relative coords: %.2f %.2f\n", relativeMousePos.x, relativeMousePos.y);
		}

		for (auto& element : elements) {
			Clickable* clickable = dynamic_cast<Clickable*>(element);
			if (clickable) {
				clickable->handleHover(relativeMousePos);
			}
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

void Div::setVisibleWindow(sf::IntRect window) {
	sf::View view = renderTexture.getView();
	view.setScissor({ sf::Vector2f(window.position).componentWiseDiv(view.getSize()), sf::Vector2f(window.size).componentWiseDiv(view.getSize()) });
	renderTexture.setView(view);
}

void Div::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	renderTexture.clear(sf::Color::Transparent);
	sf::RenderStates statesCopy = states;
	statesCopy.transform = states.transform.Identity;
	for (const auto& element : elements) {
		renderTexture.draw(*element, statesCopy);
	}
	renderTexture.display();

	states.transform *= getTransform();
	sf::Sprite sprite(renderTexture.getTexture());
	target.draw(sprite, states);
}

} // end namespace gui

