#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Clickable.h"

namespace gui {

class Div : public sf::Drawable, public sf::Transformable, public Clickable {
public:
	mutable sf::RenderTexture renderTexture;
	std::vector<sf::Drawable*> elements;

public:
	Div(sf::Vector2u size, sf::ContextSettings settings = {});

	virtual void click(sf::Vector2f mousePos) override;
	virtual void handleHover(sf::Vector2f mousePos) override;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

} // end namespace gui