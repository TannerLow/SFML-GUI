#pragma once
#include <limits>

namespace gui {

class Clickable {
protected:
	bool attachedToMouse = false;
	sf::Vector2f dragReference;

public:
	bool clickEnabled = false;
	bool draggable = false;
	bool hoverable = false;
	bool dragLockedX = false;
	bool dragLockedY = false;
	float dragMinX = -1e7;
	float dragMaxX = 1e7;
	float dragMinY = -1e7;
	float dragMaxY = 1e7;

	virtual void click(sf::Vector2f mousePos, sf::Mouse::Button button) = 0;
	virtual void releaseClick(sf::Vector2f mousePos, sf::Mouse::Button button) {}
	virtual void handleHover(sf::Vector2f mousePos) = 0;
	virtual void update() = 0;
};

}