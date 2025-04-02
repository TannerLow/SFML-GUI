#pragma once
#include "GUI/Button.h"

class DraggableButton : public gui::Button {
private:
	sf::RectangleShape buttonGfx;

public:
	DraggableButton(sf::Vector2u size, sf::IntRect visibleWindow = { {}, {} }, sf::ContextSettings settings = {});

	virtual void click(sf::Vector2f mousePos, sf::Mouse::Button button) override;
	virtual void releaseClick(sf::Vector2f mousePos, sf::Mouse::Button button) override;
	virtual void handleHover(sf::Vector2f mousePos) override;
	virtual void update() override {}

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};