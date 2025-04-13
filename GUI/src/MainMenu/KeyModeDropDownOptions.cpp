#include "KeyModeDropDownOptions.h"
#include "MainMenuGlobals.h"

namespace o2 {

KeyModeDropDownOptions::KeyModeDropDownOptions(KeyMode initialKeyMode, sf::Vector2f parentButtonSize, sf::IntRect visibleWindow, sf::ContextSettings settings)
	: gui::Div::Div({ (unsigned int)parentButtonSize.x, (unsigned int)parentButtonSize.y * 3 }, visibleWindow, settings)
{
	clickEnabled = true;
	hoverable = true;
	keyMode = initialKeyMode;

	sf::Vector2f size = sf::Vector2f(renderTexture.getSize());

	keysAllButton.setSize({ size.x, size.y / 3});
	keys7Button.setSize({ size.x, size.y / 3});
	keys4Button.setSize({ size.x, size.y / 3});

	keys7Button.setPosition({0, keysAllButton.getSize().y});
	keys4Button.setPosition({0, keys7Button.getPosition().y + keys7Button.getSize().y});

	keysAllText.setFont(minecraftFont);
	keys7Text.setFont(minecraftFont);
	keys4Text.setFont(minecraftFont);

	keysAllText.setString("All");
	keys7Text.setString("7 Key");
	keys4Text.setString("4 Key");

	keysAllText.setPosition(keysAllButton.getPosition() + keysAllButton.getSize() / 2.f - keysAllText.getCenter());
	keys7Text.setPosition(keys7Button.getPosition() + keys7Button.getSize() / 2.f - keys7Text.getCenter());
	keys4Text.setPosition(keys4Button.getPosition() + keys4Button.getSize() / 2.f - keys4Text.getCenter());

	elements.push_back(&keysAllButton);
	elements.push_back(&keys7Button);
	elements.push_back(&keys4Button);
	elements.push_back(&keysAllText);
	elements.push_back(&keys7Text);
	elements.push_back(&keys4Text);
}

void KeyModeDropDownOptions::releaseClick(sf::Vector2f mousePos, sf::Mouse::Button button) {
	if (clickEnabled) {
		sf::Vector2f relativeMousePos = getInverseTransform().transformPoint(mousePos);
		if (keysAllButton.getGlobalBounds().contains(relativeMousePos)) {
			keyMode = KeyMode::ALL;
		}

		if (keys7Button.getGlobalBounds().contains(relativeMousePos)) {
			keyMode = KeyMode::KEYS_7;
		}

		if (keys4Button.getGlobalBounds().contains(relativeMousePos)) {
			keyMode = KeyMode::KEYS_4;
		}
	}
}

void KeyModeDropDownOptions::handleHover(sf::Vector2f mousePos) {
	if (hoverable) {
		sf::Vector2f relativeMousePos = getInverseTransform().transformPoint(mousePos);
		if (keysAllButton.getGlobalBounds().contains(relativeMousePos)) {
			keysAllButton.setFillColor(sf::Color::Black);
		}
		else {
			keysAllButton.setFillColor(sf::Color::Cyan);
		}

		if (keys7Button.getGlobalBounds().contains(relativeMousePos)) {
			keys7Button.setFillColor(sf::Color::Black);
		}
		else {
			keys7Button.setFillColor(sf::Color::Yellow);
		}

		if (keys4Button.getGlobalBounds().contains(relativeMousePos)) {
			keys4Button.setFillColor(sf::Color::Black);
		}
		else {
			keys4Button.setFillColor(sf::Color::Green);
		}
	}
}

KeyMode KeyModeDropDownOptions::getKeyMode() const {
	return keyMode;
}

}