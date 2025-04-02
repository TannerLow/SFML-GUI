#pragma once
#include "../Button.h"
#include "ScrollEnums.h"

namespace gui {

class ScrollBarButton : public Button {
private:
	sf::RectangleShape buttonGfx;
	ScrollSide side;

public:
	ScrollBarButton(sf::Vector2u size, ScrollSide side, sf::Vector2f bounds, sf::IntRect visibleWindow = { {}, {} }, sf::ContextSettings settings = {});

	virtual void click(sf::Vector2f mousePos, sf::Mouse::Button button) override;
	virtual void releaseClick(sf::Vector2f mousePos, sf::Mouse::Button button) override;
	virtual void handleHover(sf::Vector2f mousePos) override;
	virtual void update() override {}

	void moveBar(ScrollDirection direction);

	float getScrollPercentage() const;
	float getLowestPointOfBar() const;
	float getHighestPointOfBar() const;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

}