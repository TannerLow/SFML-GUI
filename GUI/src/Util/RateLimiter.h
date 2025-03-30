#pragma once
#include <SFML/System.hpp>

class RateLimiter {
private:
	sf::Clock clock;
	double timePerTick = 0;
	int limit = 0;

public:
	RateLimiter() {}
	RateLimiter(int limit);
	~RateLimiter() {}

	void tick();
	void setLimit(int limit);
};