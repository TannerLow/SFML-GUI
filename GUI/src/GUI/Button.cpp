#include "Button.h"

namespace gui {

bool Button::isDepressed() const {
	return isDown;
}

bool Button::containedByDiv(sf::Vector2f point) const {
	if (clickEnabled and div != nullptr) {
		point = getInverseTransform().transformPoint(point);
		return div->contains(point);
	}
	return false;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if(div) {
		states.transform *= getTransform();
		
		target.draw(*div, states);
	}
}

}
