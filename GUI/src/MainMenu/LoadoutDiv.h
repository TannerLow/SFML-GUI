#pragma once
#include <SFML/Graphics.hpp>
#include "../GUI/Div.h"
#include <vector>
#include "../GUI/Text.h"

namespace o2 {

class LoadoutDiv : public gui::Div {
protected:
	sf::RectangleShape background;
	sf::RectangleShape player;
	std::vector<sf::RectangleShape> streaks;
	sf::RectangleShape weapon;
	sf::RectangleShape helmet;
	sf::RectangleShape chest;
	sf::RectangleShape pants;
	sf::RectangleShape boots;
	sf::RectangleShape expContainer;
	sf::RectangleShape exp;
	gui::Text currentLevel;
	gui::Text nextLevel;
	using gui::Div::elements;

	//TEMP
	sf::RectangleShape inside;

public:
	LoadoutDiv(sf::Vector2u size, sf::IntRect visibleWindow = { {}, {} }, sf::ContextSettings settings = {});
};

}