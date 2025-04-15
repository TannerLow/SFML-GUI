#include "RateButton.h"
#include "MainMenuGlobals.h"
#include <sstream>

namespace o2 {

RateButton::RateButton(sf::Vector2u size, sf::IntRect visibleWindow, sf::ContextSettings settings) {
	clickEnabled = true;
	div = new gui::Div(size, visibleWindow, settings);

	buttonGfx.setFillColor(sf::Color(64, 64, 64));
	buttonGfx.setSize(sf::Vector2f(size));

	sf::Vector2f rateChangeSize = { size.x * 0.4f , 20 };

	rateDownGfx.setFillColor(sf::Color::Green);
	rateDownGfx.setSize(rateChangeSize);
	rateDownGfx.setPosition({
		div->renderTexture.getSize().x * 0.07f,
		2 * div->renderTexture.getSize().y / 3.f - rateDownGfx.getSize().y / 2.f
	});

	rateUpGfx.setFillColor(sf::Color::Green);
	rateUpGfx.setSize(rateChangeSize);
	rateUpGfx.setPosition({
		div->renderTexture.getSize().x * 0.53f,
		2 * div->renderTexture.getSize().y / 3.f - rateUpGfx.getSize().y / 2.f
	});

	text.setFont(minecraftFont);
	updateText();

	div->elements.push_back(&buttonGfx);
	div->elements.push_back(&rateUpGfx);
	div->elements.push_back(&rateDownGfx);
	div->elements.push_back(&text);
}

void RateButton::click(sf::Vector2f mousePos, sf::Mouse::Button button) {

}

void RateButton::releaseClick(sf::Vector2f mousePos, sf::Mouse::Button button) {
	if (clickEnabled) {
		if (containedByDiv(mousePos)) {
			sf::Vector2f relativeMousePos = getInverseTransform().transformPoint(mousePos);
			if (rateUpGfx.getGlobalBounds().contains(relativeMousePos)) {
				rate += 0.05f;
				updateText();
			}
			else if (rateDownGfx.getGlobalBounds().contains(relativeMousePos)) {
				rate -= 0.05f;
				updateText();
			}
		}
	}
}

void RateButton::updateText() {
	if (rate != previousRate) {
		if (rate > 2.f) {
			rate = 2.f;
		}
		else if (rate < 0.5f) {
			rate = 0.5f;
		}
		std::stringstream ss;
		ss << std::fixed << std::setprecision(2) << rate;
		std::string rateString = ss.str();
		text.setString("Rate (" + rateString + "x)");
		text.setPosition(sf::Vector2f({ 
			div->renderTexture.getSize().x / 2.f - text.getCenter().x , 
			div->renderTexture.getSize().y / 3.f - text.getCenter().y 
		}));
		previousRate = rate;
	}
}

}
