#pragma once
#include <SFML/Graphics.hpp>
#include "../GUI/Button.h"
#include "KeyModeDropDownOptions.h"
#include "KeyModes.h"
#include "../GUI/Text.h"

namespace o2 {

class KeyModeDropDownButton : public gui::Button {
protected:
	KeyModeDropDownOptions* optionsDiv = nullptr;
	sf::RectangleShape buttonGfx;
	gui::Text buttonText;
	KeyMode keyMode = KeyMode::ALL;
	bool dontRemoveOptions = false;

public:
	KeyModeDropDownButton(sf::Vector2u size, sf::IntRect visibleWindow = { {}, {} }, sf::ContextSettings settings = {});

	virtual void click(sf::Vector2f mousePos, sf::Mouse::Button button) override;
	virtual void releaseClick(sf::Vector2f mousePos, sf::Mouse::Button button) override;

	void updateText();
	KeyMode getKeyMode() const;

protected:
	void spawnOptionsDiv();
};

}

