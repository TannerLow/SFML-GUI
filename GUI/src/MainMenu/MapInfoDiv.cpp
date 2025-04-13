#include "MapInfoDiv.h"'
#include "MainMenuGlobals.h"

namespace o2 {

MapInfoDiv::MapInfoDiv(sf::Vector2u size, sf::IntRect visibleWindow, sf::ContextSettings settings)
	: gui::Div::Div(size, visibleWindow, settings)
{
	background.setSize({ 864, 108 });
	background.setFillColor(sf::Color::Black);

	songName.setFont(minecraftFont);
	artist.setFont(minecraftFont);
	diffName.setFont(minecraftFont);

	songName.setScale({ 2, 2 });
	artist.setScale({ 2, 2 });
	diffName.setScale({ 2, 2 });

	elements.push_back(&background);
	elements.push_back(&songName);
	elements.push_back(&artist);
	elements.push_back(&diffName);
}

void MapInfoDiv::setMapInfo(MapInfo info) {
	songName.setString(info.songName);
	artist.setString(info.artist);
	diffName.setString(info.diffName);

	songName.setPosition({ background.getSize().x / 2.f - songName.getBoundingBox().size.x / 2.f, 3 });
	artist.setPosition({ background.getSize().x / 2.f - artist.getBoundingBox().size.x / 2.f, 38 });
	diffName.setPosition({ background.getSize().x / 2.f - diffName.getBoundingBox().size.x / 2.f, 73 });
}

}