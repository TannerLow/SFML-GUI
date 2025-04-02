#pragma once
#include "../Button.h"
#include "ScrollBarButton.h"
#include "ScrollEnums.h"
#include "../../Util/RateLimiter.h"

namespace gui {

	class ScrollEndButton : public Button {
	private:
		sf::RectangleShape buttonGfx;
		ScrollBarButton* barButton = nullptr;
		ScrollDirection direction;
		RateLimiter holdLimiter;

	public:
		ScrollEndButton(
			sf::Vector2u size, 
			ScrollDirection direction, 
			ScrollBarButton* scrollBarButton, 
			sf::IntRect visibleWindow = { {}, {} }, 
			sf::ContextSettings settings = {}
		);

		virtual void click(sf::Vector2f mousePos, sf::Mouse::Button button) override;
		virtual void releaseClick(sf::Vector2f mousePos, sf::Mouse::Button button) override;
		virtual void handleHover(sf::Vector2f mousePos) override;
		virtual void update() override;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};

}