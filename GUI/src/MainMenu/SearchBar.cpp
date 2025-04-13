#include "SearchBar.h"
#include "MainMenuGlobals.h"

namespace o2 {

SearchBar::SearchBar(sf::Vector2u size, sf::IntRect visibleWindow, sf::ContextSettings settings)
	: gui::Div::Div(size, visibleWindow, settings)
{
	clickEnabled = true;
	hoverable = true;
	toggleOutOfBoundsClicking(true);

	background.setSize(sf::Vector2f(size));
	background.setFillColor(sf::Color::Black);

	queryDiv = new gui::Div({ size.x - 100, size.y });

	queryTextBackground.setFillColor(sf::Color(130, 130, 130));
	queryTextBackground.setSize({ (float)size.x - 100, (float)size.y });
	queryDiv->elements.push_back(&queryTextBackground);

	queryText.setFont(minecraftFont);
	queryText.setScale({ 2, 2 });
	queryText.setString("Enter a search query in this text box");
	queryText.setPosition({ 10, size.y / 2.f - queryText.getBoundingBox().size.y / 2.f });
	queryDiv->elements.push_back(&queryText);

	elements.push_back(&background);
	elements.push_back(queryDiv);

	enableQueryKeys();
	mapShiftChars();
}

//void SearchBar::click(sf::Vector2f mousePos, sf::Mouse::Button button) {
//	gui::Div::click(mousePos, button);
//}

void SearchBar::update() {
	keyManager.update();
	handleKeyInputs();
}

void SearchBar::setKeyMode(KeyMode keyMode) {
	this->keyMode = keyMode;
}

std::string SearchBar::getQueryString() const {
	return queryString;
}

void SearchBar::handleKeyInputs() {
	bool stringUpdated = false;
	while (keyManager.hasNextEvent()) {
		KeyEvent keyEvent = keyManager.popGetEvent();
		stringUpdated = true;
		if (keyEvent.action == KeyAction::Press) {
			if (keyEvent.key == sf::Keyboard::Key::LShift or keyEvent.key == sf::Keyboard::Key::RShift) {
				shifting = true;
			}
			else if (keyEvent.key == sf::Keyboard::Key::LControl or keyEvent.key == sf::Keyboard::Key::RControl) {
				controlling = true;
			}
			else if (keyEvent.key == sf::Keyboard::Key::Backspace) {
				processBackspace();
			}
			else if (keyEvent.key == sf::Keyboard::Key::Delete) {
				if (!queryString.empty()) {
					// TODO pending cursor feature
				}
			}
			else {
				processTypeableKey(keyEvent);
			}
		}
		else {
			if (keyEvent.key == sf::Keyboard::Key::LShift or keyEvent.key == sf::Keyboard::Key::RShift) {
				shifting = false;
			}
			else if (keyEvent.key == sf::Keyboard::Key::LControl or keyEvent.key == sf::Keyboard::Key::RControl) {
				controlling = false;
			}
		}
	}

	if (stringUpdated) {
		queryText.setString(queryString);
	}
}

void SearchBar::processTypeableKey(KeyEvent keyEvent) {
	int keyEnumIndex = (int)keyEvent.key;

	char letter = '?';
	if (shifting) {
		if ((int)sf::Keyboard::Key::A <= keyEnumIndex and keyEnumIndex <= (int)sf::Keyboard::Key::Z) {
			letter = keyEnumIndex - (int)sf::Keyboard::Key::A + 'A';
		}
		
		auto it = shiftCharMap.find(keyEvent.key);
		if (it != shiftCharMap.end()) {
			letter = shiftCharMap[keyEvent.key];
		}
	}
	else {
		if ((int)sf::Keyboard::Key::A <= keyEnumIndex and keyEnumIndex <= (int)sf::Keyboard::Key::Z) {
			letter = keyEnumIndex - (int)sf::Keyboard::Key::A + 'a';
		}
		else if ((int)sf::Keyboard::Key::Num0 <= keyEnumIndex and keyEnumIndex <= (int)sf::Keyboard::Key::Num9) {
			letter = keyEnumIndex - (int)sf::Keyboard::Key::Num0 + '0';
		}
		else if ((int)sf::Keyboard::Key::Numpad0 <= keyEnumIndex and keyEnumIndex <= (int)sf::Keyboard::Key::Numpad9) {
			letter = keyEnumIndex - (int)sf::Keyboard::Key::Numpad0 + '0';
		}
		else {
			switch (keyEvent.key) {
			case sf::Keyboard::Key::LBracket: letter = '['; break;
			case sf::Keyboard::Key::RBracket: letter = ']'; break;
			case sf::Keyboard::Key::Semicolon: letter = ';'; break;
			case sf::Keyboard::Key::Comma: letter = ','; break;
			case sf::Keyboard::Key::Period: letter = '.'; break;
			case sf::Keyboard::Key::Apostrophe: letter = '\''; break;
			case sf::Keyboard::Key::Slash: letter = '/'; break;
			case sf::Keyboard::Key::Backslash: letter = '\\'; break;
			case sf::Keyboard::Key::Grave: letter = '`'; break;
			case sf::Keyboard::Key::Equal: letter = '='; break;
			case sf::Keyboard::Key::Hyphen: letter = '-'; break;
			case sf::Keyboard::Key::Space: letter = ' '; break;
			case sf::Keyboard::Key::Add: letter = '+'; break;
			case sf::Keyboard::Key::Subtract: letter = '-'; break;
			case sf::Keyboard::Key::Multiply: letter = '*'; break;
			case sf::Keyboard::Key::Divide: letter = '/'; break;
			}
		}
	}
	
	queryString += letter;
}

void SearchBar::processBackspace() {
	if (queryString.empty()) {
		return;
	}
	if (controlling) {
		size_t pos = queryString.size() - 1;
		while (pos > 0) {
			char c = queryString[pos - 1];
			char d = queryString[pos];
			if ((c == ' ' or c == '-') and (d != ' ' and d != '-')) {
				break;
			}
			if (c == ' ' and d == '-') {
				break;
			}
			pos--;
		}
		queryString = queryString.substr(0, pos);
	}
	else {
		queryString.erase(queryString.end() - 1);
	}
}

void SearchBar::enableQueryKeys() {
	std::set<sf::Keyboard::Key> keys;

	for (int i = (int)sf::Keyboard::Key::A; i <= (int)sf::Keyboard::Key::Z; i++) {
		keys.insert((sf::Keyboard::Key)i);
	}
	for (int i = (int)sf::Keyboard::Key::Num0; i <= (int)sf::Keyboard::Key::Num9; i++) {
		keys.insert((sf::Keyboard::Key)i);
	}
	for (int i = (int)sf::Keyboard::Key::Numpad0; i <= (int)sf::Keyboard::Key::Numpad9; i++) {
		keys.insert((sf::Keyboard::Key)i);
	}
	for (int i = (int)sf::Keyboard::Key::Add; i <= (int)sf::Keyboard::Key::Divide; i++) {
		keys.insert((sf::Keyboard::Key)i);
	}
	for (int i = (int)sf::Keyboard::Key::LBracket; i <= (int)sf::Keyboard::Key::Space; i++) {
		keys.insert((sf::Keyboard::Key)i);
	}
	keys.insert(sf::Keyboard::Key::Backspace);
	keys.insert(sf::Keyboard::Key::Delete);
	keys.insert(sf::Keyboard::Key::LControl);
	keys.insert(sf::Keyboard::Key::LShift);
	keys.insert(sf::Keyboard::Key::RControl);
	keys.insert(sf::Keyboard::Key::RShift);

	// TODO add left right home end when adding a cursor feature

	keyManager.enableKeys(keys);
}

void SearchBar::mapShiftChars() {
	shiftCharMap[sf::Keyboard::Key::Num1] = '!';
	shiftCharMap[sf::Keyboard::Key::Num2] = '@';
	shiftCharMap[sf::Keyboard::Key::Num3] = '#';
	shiftCharMap[sf::Keyboard::Key::Num4] = '$';
	shiftCharMap[sf::Keyboard::Key::Num5] = '%';
	shiftCharMap[sf::Keyboard::Key::Num6] = '^';
	shiftCharMap[sf::Keyboard::Key::Num7] = '&';
	shiftCharMap[sf::Keyboard::Key::Num8] = '*';
	shiftCharMap[sf::Keyboard::Key::Num9] = '(';
	shiftCharMap[sf::Keyboard::Key::Num0] = ')';
	shiftCharMap[sf::Keyboard::Key::Hyphen] = '_';
	shiftCharMap[sf::Keyboard::Key::Equal] = '+';

	shiftCharMap[sf::Keyboard::Key::LBracket] = '{';
	shiftCharMap[sf::Keyboard::Key::RBracket] = '}';
	shiftCharMap[sf::Keyboard::Key::Backslash] = '|';
	shiftCharMap[sf::Keyboard::Key::Semicolon] = ';';
	shiftCharMap[sf::Keyboard::Key::Grave] = '~';
	shiftCharMap[sf::Keyboard::Key::Apostrophe] = '\"';
	shiftCharMap[sf::Keyboard::Key::Comma] = '<';
	shiftCharMap[sf::Keyboard::Key::Period] = '>';
	shiftCharMap[sf::Keyboard::Key::Slash] = '?';
}

}
