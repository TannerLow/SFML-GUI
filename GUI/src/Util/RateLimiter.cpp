#include "RateLimiter.h"


RateLimiter::RateLimiter(int limit) {
	setLimit(limit);
}

bool RateLimiter::isReady() {
	if (limit == 0) {
		return true;
	}

	if (clock.getElapsedTime().asSeconds() < timePerTick) {
		return false;
	}

	clock.restart();

	return true;
}

void RateLimiter::setLimit(int limit) {
	this->limit = limit;
	this->timePerTick = 1.0 / limit;
}
