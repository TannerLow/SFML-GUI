#include "SimpleButton.h"

namespace o2 {

SimpleButton::SimpleButton(sf::String text, sf::Vector2u size, sf::IntRect visibleWindow, sf::ContextSettings settings) {
	div = new gui::Div(size, visibleWindow, settings);

}

}