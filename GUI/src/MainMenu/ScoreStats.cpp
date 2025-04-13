#include "ScoreStats.h"
#include "MainMenuGlobals.h"

#include <iostream>

namespace o2 {

ScoreStats::ScoreStats(
	gui::Div* parentDiv,
	sf::Vector2u size, 
	sf::IntRect visibleWindow, 
	sf::ContextSettings settings
)
	: gui::Div::Div(size, visibleWindow, settings)
{
	clickEnabled = true;
	slideRateLimiter.setLimit(200);

	scoreStatsBackground.setSize(sf::Vector2f(size));
	scoreStatsBackground.setFillColor(sf::Color(64, 64, 64, 201));
	
	elements.push_back(&scoreStatsBackground);


	for (int i = 0; i < 51; i++) {
		scoreTexts[i].setFont(minecraftFont);
		scoreTexts[i].setScale({ 2, 2 });
		elements.push_back(&scoreTexts[i]);
	}
	scoreTexts[0].setString("Play the map to set a score");

	elements.push_back(&expandButton);
}

void ScoreStats::loadScores(ScoreData scoreData) {
	float width = renderTexture.getSize().x;
	float height = 40;
	sf::Vector2f pos = { 0, 2 };

	scoreTexts[0].setString(scoreData.topScore);
	sf::FloatRect textBounds = scoreTexts[0].getBoundingBox();
	scoreTexts[0].setPosition({ width / 2.f - textBounds.size.x / 2.f, pos.y + height / 2.f - textBounds.size.y / 2.f });
	pos.y += height;

	for (int i = 1; i <= scoreData.scores.size() and i < scoreTexts.size(); i++) {
		scoreTexts[i].setString(scoreData.scores[i-1]);
		textBounds = scoreTexts[0].getBoundingBox();
		scoreTexts[i].setPosition({ width / 2.f - textBounds.size.x / 2.f, pos.y + height / 2.f - textBounds.size.y / 2.f });
		pos.y += height;
		bottomMostScoreIndex = i;
	}
}

void ScoreStats::update() {
	if (slideRateLimiter.isReady()) {
		slide();
	}

	float yPos = getPosition().y;
	if (yPos < 0) {
		expandButton.setPosition({0, -yPos});
	}
	else {
		expandButton.setPosition({ 0, 0 });
	}
}

void ScoreStats::scroll(float delta) {
	std::cout << "scrolled div " << delta << std::endl;
	if (delta > 0) { // up
		if (getPosition().y < (486 - 40)) {
			move({ 0, 10 });
			if (getPosition().y > (486 - 40)) {
				setPosition({ 0, (486 - 40) });
			}
		}
	}
	else { // down
		float bottomTextY = scoreTexts[bottomMostScoreIndex].getPosition().y;
		if (bottomTextY > (486 - 40)) {
			move({ 0, -10 });
			if (bottomTextY + getPosition().y < (486 - 40)) {
				setPosition({ 0, 486 - bottomTextY - 40});
			}
		}
	}
}

//void ScoreStats::setSlideDirection(SlideDirection direction) {
//	slideDirection = direction;
//}

void ScoreStats::slide() {
	if (expandButton.slideDirection != SlideDirection::STATIONARY) {
		if (expandButton.slideDirection == SlideDirection::UP) {
			move({ 0, -1 });
			if (getPosition().y < 0) {
				setPosition({ 0, 0 });
				expandButton.slideDirection = SlideDirection::STATIONARY;
			}
		}
		else {
			move({ 0, 1 });
			if (getPosition().y > (486 - 40)) {
				setPosition({ 0, (486 - 40) });
				expandButton.slideDirection = SlideDirection::STATIONARY;
			}
		}
	}
}

}