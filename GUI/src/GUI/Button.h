#pragma once
#include <SFML/Graphics.hpp>
#include "Clickable.h"
#include "Div.h"

namespace gui {

class Button : public sf::Drawable, public sf::Transformable, public Clickable {
protected:
	bool isDown = false;

public:
	Div* div = nullptr;
	bool isToggle = false;

	bool isDepressed() const;

protected:
	bool containedByDiv(sf::Vector2f point) const;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

}
