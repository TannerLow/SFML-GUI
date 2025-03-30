#pragma once

namespace gui {

class Clickable {
public:
	bool clickEnabled = false;
	bool draggable = false;
	bool hoverable = false;
	bool dragLockedX = false;
	bool dragLockedY = false;

	virtual void click(sf::Vector2f mousePos) = 0;
	virtual void handleHover(sf::Vector2f mousePos) = 0;
};

}