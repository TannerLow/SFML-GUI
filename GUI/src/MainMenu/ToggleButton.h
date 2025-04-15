#pragma once
#include <SFML/Graphics.hpp>
#include "../GUI/Button.h"
#include "../GUI/Text.h"

namespace o2 {

class ToggleButton : public gui::Button {
protected:
	sf::RectangleShape buttonGfx;
	gui::Text buttonText;

public:
	ToggleButton(sf::String text, sf::Vector2u size, sf::IntRect visibleWindow = { {}, {} }, sf::ContextSettings settings = {});

	virtual void click(sf::Vector2f mousePos, sf::Mouse::Button button) override {}
	virtual void releaseClick(sf::Vector2f mousePos, sf::Mouse::Button button) override;
};

}
