#pragma once
#include <SFML/Graphics.hpp>
#include "../GUI/Div.h"
#include "MapInfo.h"
#include "../GUI/Text.h"

namespace o2 {

class MapInfoDiv : public gui::Div {
protected:
	//MapInfo data;
	sf::RectangleShape background;
	gui::Text songName;
	gui::Text artist;
	gui::Text diffName;

	using gui::Div::elements;

public:
	MapInfoDiv(sf::Vector2u size, sf::IntRect visibleWindow = { {}, {} }, sf::ContextSettings settings = {});

	void setMapInfo(MapInfo info);
};

}