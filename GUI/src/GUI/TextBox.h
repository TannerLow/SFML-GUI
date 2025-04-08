#pragma once
#include <SFML/Graphics.hpp>
#include "Text.h"

namespace gui {

class TextBox : public sf::Drawable, public sf::Transformable {


public:
	TextBox() {}

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

}