#include "LoadoutDiv.h"
#include "MainMenuGlobals.h"

namespace o2 {

LoadoutDiv::LoadoutDiv(sf::Vector2u size, sf::IntRect visibleWindow, sf::ContextSettings settings)
	: gui::Div(size, visibleWindow, settings)
{
	sf::Vector2f sizef = sf::Vector2f(size);
	streaks.resize(3);

	background.setFillColor(sf::Color(64, 64, 64));
	background.setSize(sizef);

	//sf::RectangleShape background;
	//sf::RectangleShape player;
	//std::vector<sf::RectangleShape> streaks;
	//sf::RectangleShape weapon;
	//sf::RectangleShape helmet;
	//sf::RectangleShape chest;
	//sf::RectangleShape pants;
	//sf::RectangleShape boots;
	//sf::RectangleShape expContainer;
	//sf::RectangleShape exp;
	//gui::Text currentLevel;
	//gui::Text nextLevel;

	sf::Vector2f playerSize = { 0.475f, 0.6625f };
	sf::Vector2f playerPos = { 0.2625f, 0.05f };
	player.setFillColor(sf::Color::Black);
	player.setSize({ sizef.x * playerSize.x, sizef.y * playerSize.y });
	player.setPosition({ sizef.x * playerPos.x, sizef.y * playerPos.y });

	inside.setFillColor(sf::Color::Blue);
	inside.setSize(sizef * 0.9f);
	inside.setPosition(sizef * 0.05f);

	sf::Vector2f pos = { 0.05f, 0.05f };
	sf::Vector2f slotSize = { 0.1875f, 0.1875f };
	for (int i = 0; i < streaks.size(); i++) {
		streaks[i].setFillColor(sf::Color::Yellow);
		streaks[i].setSize({ sizef.x * slotSize.x, sizef.y * slotSize.y });
		streaks[i].setPosition({ sizef.x * pos.x, sizef.y * pos.y });
		pos.y += 0.1875f + 0.05f;
	}

	weapon.setFillColor(sf::Color::Yellow);
	weapon.setSize({ sizef.x * slotSize.x, sizef.y * slotSize.y });
	weapon.setPosition({ sizef.x * 0.05f, sizef.y * pos.y });

	pos = { 1.f - 0.1875f - 0.05f, 0.05f };
	helmet.setFillColor(sf::Color::White);
	helmet.setSize({ sizef.x * slotSize.x, sizef.y * slotSize.y });
	helmet.setPosition({ sizef.x * pos.x, sizef.y * pos.y });
	pos.y += 0.1875f + 0.05f;

	chest.setFillColor(sf::Color::White);
	chest.setSize({ sizef.x * slotSize.x, sizef.y * slotSize.y });
	chest.setPosition({ sizef.x * pos.x, sizef.y * pos.y });
	pos.y += 0.1875f + 0.05f;

	pants.setFillColor(sf::Color::White);
	pants.setSize({ sizef.x * slotSize.x, sizef.y * slotSize.y });
	pants.setPosition({ sizef.x * pos.x, sizef.y * pos.y });
	pos.y += 0.1875f + 0.05f;

	boots.setFillColor(sf::Color::White);
	boots.setSize({ sizef.x * slotSize.x, sizef.y * slotSize.y });
	boots.setPosition({ sizef.x * pos.x, sizef.y * pos.y });

	expContainer.setFillColor(sf::Color(140, 140, 140));
	expContainer.setSize({ sizef.x * playerSize.x, sizef.y * slotSize.y / 2.f });
	expContainer.setPosition({ sizef.x * playerPos.x, sizef.y * 0.95f - (sizef.y * slotSize.y / 2.f) });

	exp.setFillColor(sf::Color::Green);
	exp.setSize({ sizef.x * playerSize.x * 0.7f, sizef.y * slotSize.y / 2.f});
	exp.setPosition({ sizef.x * playerPos.x, sizef.y * 0.95f - (sizef.y * slotSize.y / 2.f) });

	currentLevel.setFont(minecraftFont);
	currentLevel.setString("107");
	currentLevel.setPosition({ sizef.x * playerPos.x, sizef.y * pos.y });

	nextLevel.setFont(minecraftFont);
	nextLevel.setString("108");
	nextLevel.setPosition({ sizef.x * (playerPos.x + playerSize.x) - nextLevel.getBoundingBox().size.x, sizef.y * pos.y});

	
	elements.push_back(&background);
	//elements.push_back(&inside);
	elements.push_back(&player);
	for (int i = 0; i < streaks.size(); i++) {
		elements.push_back(&streaks[i]);
	}
	elements.push_back(&weapon);
	elements.push_back(&helmet);
	elements.push_back(&chest);
	elements.push_back(&pants);
	elements.push_back(&boots);
	elements.push_back(&expContainer);
	elements.push_back(&exp);
	elements.push_back(&currentLevel);
	elements.push_back(&nextLevel);
}

}