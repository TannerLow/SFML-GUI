#include "KeyManager.h"

namespace o2 {

KeyManager::KeyManager(bool queueEnabled) {
	this->queueEnabled = queueEnabled;

	for (std::array<KeyAction, 120>::iterator it = keyStates.begin(); it != keyStates.end(); it++) {
		*it = KeyAction::Release;
	}

	noEvent.key = sf::Keyboard::Key::Unknown;
}

KeyManager::KeyManager(const std::set<sf::Keyboard::Key>& whitelist, bool queueEnabled) {
	this->queueEnabled = queueEnabled;
	enableKeys(whitelist);

	for (std::array<KeyAction, 120>::iterator it = keyStates.begin(); it != keyStates.end(); it++) {
		*it = KeyAction::Release;
	}
}

void KeyManager::tryPushEvent(const int32_t time, const KeyAction state, const sf::Keyboard::Key key) {
	// queue stores multiple key presses to be consumed later
	if (queueEnabled) {
		keyEvents.push({
				time,
				state,
				key
			});
	}
}

void KeyManager::update(const int32_t time) {
	KeyAction state;

	for (const auto& key : enabledKeys) {
		if (sf::Keyboard::isKeyPressed(key)) {
			if (getKeyState(key) == KeyAction::Release) {
				state = KeyAction::Press;
				//i think +1 is for Unknown key code = -1 in SFML
				keyStates[(int)key + 1] = state;
				tryPushEvent(time, state, key);
			}
		}
		else if (getKeyState(key) == KeyAction::Press) {
			state = KeyAction::Release;
			keyStates[(int)key + 1] = state;
			tryPushEvent(time, state, key);
		}
	}
}

void KeyManager::enableAllKeys() {
	for (int i = 0; i < (int)sf::Keyboard::KeyCount; i++) {
		enableKey((sf::Keyboard::Key)i);
	}
}

void KeyManager::enableKey(sf::Keyboard::Key key) {
	enabledKeys.insert(key);
}

void KeyManager::enableKeys(const std::set<sf::Keyboard::Key>& keys) {
	for (const auto& key : keys) {
		enableKey(key);
	}
}

void KeyManager::disableKey(sf::Keyboard::Key key) {
	const auto it = enabledKeys.find(key);
	if (it != enabledKeys.end()) {
		enabledKeys.erase(it);
	}
}

void KeyManager::disableKeys(const std::set<sf::Keyboard::Key>& keys) {
	for (const auto& key : keys) {
		disableKey(key);
	}
}

void KeyManager::useQueue(bool shouldUseQueue) {
	queueEnabled = shouldUseQueue;
}

KeyAction KeyManager::getKeyState(sf::Keyboard::Key key) const {
	return keyStates[(int)key + 1];
}

bool KeyManager::hasNextEvent() const {
	return !keyEvents.empty();
}

const KeyEvent& KeyManager::peekEvent() const {
	if (keyEvents.empty()) {
		return noEvent;
	}
	return keyEvents.front();
}

KeyEvent KeyManager::popGetEvent() {
	const auto& event_ = keyEvents.front();
	keyEvents.pop();
	return event_;
}

void KeyManager::popEvent() {
	keyEvents.pop();
}

void KeyManager::clearQueue() {
	while (!keyEvents.empty()) {
		keyEvents.pop();
	}
}

}