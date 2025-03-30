#include "RateLimiter.h"


RateLimiter::RateLimiter(int limit) {
	setLimit(limit);
}

void RateLimiter::tick() {
	if (limit == 0) {
		return;
	}

	while (clock.getElapsedTime().asSeconds() < timePerTick);

	clock.restart();
}

void RateLimiter::setLimit(int limit) {
	this->limit = limit;
	this->timePerTick = 1.0 / limit;
}
