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
	Div(sf::Vector2u size, sf::IntRect visibleWindow = { {}, {} }, sf::ContextSettings settings = {});

	bool contains(sf::Vector2f point) const;
	bool visiblyContains(sf::Vector2f point) const;
	virtual void click(sf::Vector2f mousePos, sf::Mouse::Button button) override;
	virtual void releaseClick(sf::Vector2f mousePos, sf::Mouse::Button button) override;
	virtual void handleHover(sf::Vector2f mousePos) override;
	virtual void update() override {}
	void setVisibleWindow(sf::IntRect window);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::FloatRect getVisibleWindow() const;

};

} // end namespace gui