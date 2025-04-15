#pragma once
#include <SFML/Graphics.hpp>
#include "../GUI/Button.h"
#include "../GUI/Text.h"

namespace o2 {

class RateButton : public gui::Button {
public:
	sf::RectangleShape buttonGfx;
	sf::RectangleShape rateUpGfx;
	sf::RectangleShape rateDownGfx;
	gui::Text text;
	float rate = 1.f;
	float previousRate = -1;

public:
	RateButton(sf::Vector2u size, sf::IntRect visibleWindow = { {}, {} }, sf::ContextSettings settings = {});

	virtual void click(sf::Vector2f mousePos, sf::Mouse::Button button) override;
	virtual void releaseClick(sf::Vector2f mousePos, sf::Mouse::Button button) override;
	
	void updateText();
};

}