#pragma once
#include <SFML/Graphics.hpp>
#include "../GUI/Button.h"

namespace o2 {

class ExpandScoreStatsButton : public gui::Button {
protected:
	sf::RectangleShape buttonGfx;

public:
	ExpandScoreStatsButton();

	virtual void click(sf::Vector2f mousePos, sf::Mouse::Button button) override;
	virtual void releaseClick(sf::Vector2f mousePos, sf::Mouse::Button button) override;
	virtual void handleHover(sf::Vector2f mousePos) override;
	virtual void update() override;

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

}
