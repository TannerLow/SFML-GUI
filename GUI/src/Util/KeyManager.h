#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <array>
#include <set>
#include <queue>

namespace o2 {

enum class KeyAction { Press, Release };

struct KeyEvent {
	int32_t time;
	KeyAction action;
	sf::Keyboard::Key key;
};


class KeyManager
{
private:
	std::array<KeyAction, 120> keyStates;
	std::set<sf::Keyboard::Key> enabledKeys;
	std::queue<KeyEvent> keyEvents;
	bool queueEnabled;
	KeyEvent noEvent;

public:
	KeyManager(bool queueEnabled = true);
	KeyManager(const std::set<sf::Keyboard::Key>& whitelist, bool queueEnabled = true);
	~KeyManager() {}

	void update(const int32_t time = 0);
	void enableAllKeys();
	void enableKey(sf::Keyboard::Key key);
	void enableKeys(const std::set<sf::Keyboard::Key>& keys);
	void disableKey(sf::Keyboard::Key key);
	void disableKeys(const std::set<sf::Keyboard::Key>& keys);
	void useQueue(bool shouldUseQueue);

	KeyAction getKeyState(sf::Keyboard::Key key) const;
	bool hasNextEvent() const;
	const KeyEvent& peekEvent() const;
	KeyEvent popGetEvent();
	void popEvent();
	void clearQueue();

private:
	void tryPushEvent(const int32_t time, const KeyAction state, const sf::Keyboard::Key key);
};

}
