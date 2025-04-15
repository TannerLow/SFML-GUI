#pragma once
#include <SFML/Graphics.hpp>
#include "../GUI/Button.h"
#include "../GUI/Text.h"

namespace o2 {

class SimpleButton : public gui::Button {
protected:
	sf::RectangleShape buttonGfx;
	gui::Text text;

public:
	SimpleButton(sf::String text, sf::Vector2u size, sf::IntRect visibleWindow = { {}, {} }, sf::ContextSettings settings = {});
};

}
