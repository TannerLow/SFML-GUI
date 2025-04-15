#include "ToggleButton.h"
#include "MainMenuGlobals.h"

namespace o2 {

ToggleButton::ToggleButton(sf::String text, sf::Vector2u size, sf::IntRect visibleWindow, sf::ContextSettings settings) {
	clickEnabled = true;
	div = new gui::Div(size, visibleWindow, settings);

	buttonGfx.setFillColor(sf::Color(64, 64, 64));
	buttonGfx.setSize(sf::Vector2f(size));

	buttonText.setFont(minecraftFont);
	buttonText.setString(text);
	buttonText.setPosition(sf::Vector2f(size) / 2.f - buttonText.getCenter());

	div->elements.push_back(&buttonGfx);
	div->elements.push_back(&buttonText);
}

void ToggleButton::releaseClick(sf::Vector2f mousePos, sf::Mouse::Button button) {
	if (clickEnabled) {
		if (containedByDiv(mousePos)) {
			isDown = !isDown;
			if (isDown) {
				buttonGfx.setFillColor(sf::Color::Red);
			}
			else {
				buttonGfx.setFillColor(sf::Color(64, 64, 64));
			}
		}
	}
}

}
