#pragma once
#include <SFML/Graphics.hpp>
#include "../GUI/Div.h"
#include "KeyModes.h"
#include "../GUI/Text.h"

namespace o2 {

class KeyModeDropDownOptions : public gui::Div {
protected:
	using gui::Div::elements;
	KeyMode keyMode = KeyMode::ALL;

	sf::RectangleShape keysAllButton;
	sf::RectangleShape keys7Button;
	sf::RectangleShape keys4Button;

	gui::Text keysAllText;
	gui::Text keys7Text;
	gui::Text keys4Text;

public:
	KeyModeDropDownOptions(KeyMode initialKeyMode, sf::Vector2f parentButtonSize, sf::IntRect visibleWindow = { {}, {} }, sf::ContextSettings settings = {});

	virtual void releaseClick(sf::Vector2f mousePos, sf::Mouse::Button button) override;
	virtual void handleHover(sf::Vector2f mousePos) override;

	KeyMode getKeyMode() const;
};

}
