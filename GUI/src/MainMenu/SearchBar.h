#pragma once
#include <SFML/Graphics.hpp>
#include "../GUI/Div.h"
#include "../GUI/Text.h"
#include "KeyModes.h"
#include "../Util/KeyManager.h"

namespace o2{

class SearchBar : public gui::Div {
protected:
	sf::RectangleShape background;
	gui::Div* queryDiv;
	gui::Text queryText;
	//KeyModeDropDownButton keyModeDropDownButton;
	KeyMode keyMode = KeyMode::ALL;
	KeyManager keyManager;
	using gui::Div::elements;

	// Key stuff
	std::string queryString;
	bool shifting = false;
	bool controlling = false;

	//Temp
	sf::RectangleShape queryTextBackground;

private:
	std::map<sf::Keyboard::Key, char> shiftCharMap;

public:
	SearchBar(sf::Vector2u size, sf::IntRect visibleWindow = { {}, {} }, sf::ContextSettings settings = {});

	//virtual void click(sf::Vector2f mousePos, sf::Mouse::Button button) override;
	virtual void update() override;

	void setKeyMode(KeyMode keyMode);
	std::string getQueryString() const;

protected:
	void enableQueryKeys();
	void mapShiftChars();
	void handleKeyInputs();
	void processTypeableKey(KeyEvent keyEvent);
	void processBackspace();
};

}
