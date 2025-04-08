#pragma once
#include <SFML/Graphics.hpp>
#include "../GUI/Div.h"
#include "ExpandScoreStatsButton.h"
#include <array>
#include "../GUI/Text.h"
#include "../Util/RateLimiter.h"
#include "SlideDirection.h"

namespace o2 {

class ScoreStats : public gui::Div {
public:
	struct ScoreData {
		sf::String topScore;
		std::vector<sf::String> scores;
	};

protected:
	using gui::Div::elements;
	std::array<gui::Text, 51> scoreTexts;
	sf::RectangleShape scoreStatsBackground;
	ExpandScoreStatsButton expandButton;
	SlideDirection slideDirection = SlideDirection::STATIONARY;
	RateLimiter slideRateLimiter;
	int bottomMostScoreIndex = 0;

public:
	ScoreStats(
		gui::Div* parentDiv, 
		gui::Font* font, 
		sf::Vector2u size, 
		sf::IntRect visibleWindow = { {}, {} }, 
		sf::ContextSettings settings = {}
	);

	void loadScores(ScoreData scoreData);
	virtual void update() override;
	void setSlideDirection(SlideDirection direction);
	virtual void click(sf::Vector2f mousePos, sf::Mouse::Button button) override;
	virtual void scroll(float delta) override;

protected:
	void slide();
};

}
