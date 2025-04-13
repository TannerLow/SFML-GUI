#include "KeyModeDropDownButton.h"
#include "MainMenuGlobals.h"

namespace o2 {

KeyModeDropDownButton::KeyModeDropDownButton(
	sf::Vector2u size, 
	sf::IntRect visibleWindow, 
	sf::ContextSettings settings
) {
	clickEnabled = true;
	hoverable = true;

	div = new gui::Div(size, visibleWindow, settings);

	buttonGfx.setSize(sf::Vector2f(size));
	buttonGfx.setFillColor(sf::Color::Blue);

	buttonText.setFont(minecraftFont);
	updateText();

	div->elements.push_back(&buttonGfx);
	div->elements.push_back(&buttonText);
}

void KeyModeDropDownButton::click(sf::Vector2f mousePos, sf::Mouse::Button button) {
	if (clickEnabled) {
		if (containedByDiv(mousePos)) {
			spawnOptionsDiv();
		}
	}
}

void KeyModeDropDownButton::releaseClick(sf::Vector2f mousePos, sf::Mouse::Button button) {
	if (div != nullptr) {
		div->releaseClick(mousePos, button);
	
		if (optionsDiv != nullptr) {
			keyMode = optionsDiv->getKeyMode();
			updateText();
			if (dontRemoveOptions) {
				dontRemoveOptions = false;
			}
			else {
				o2::removeGlobalDiv(optionsDiv);
				div->elements.erase(div->elements.end() - 1);
				delete optionsDiv;
				optionsDiv = nullptr;
			}
		}
	}
}

void KeyModeDropDownButton::spawnOptionsDiv() {
	if (optionsDiv == nullptr) {
		optionsDiv = new KeyModeDropDownOptions(keyMode, buttonGfx.getSize());
		div->elements.push_back(optionsDiv);
		optionsDiv->setPosition(getPosition() + sf::Vector2f(0, buttonGfx.getSize().y));
		o2::globalDivs.push_back(optionsDiv);
		dontRemoveOptions = true;
	}
}

void KeyModeDropDownButton::updateText() {
	if (keyMode == KeyMode::ALL) {
		buttonText.setString("All");
	}
	else if (keyMode == KeyMode::KEYS_7) {
		buttonText.setString("7 Key");
	}
	else if (keyMode == KeyMode::KEYS_4) {
		buttonText.setString("4 Key");
	}

	buttonText.setPosition(sf::Vector2f(div->renderTexture.getSize()) / 2.f - buttonText.getCenter());
}

KeyMode KeyModeDropDownButton::getKeyMode() const {
	return keyMode;
}

}