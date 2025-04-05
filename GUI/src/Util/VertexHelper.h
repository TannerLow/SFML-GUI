#pragma once
#include <SFML/Graphics.hpp>

namespace vh {
	void updateQuadTexture(sf::Vertex* vertex, const sf::IntRect texCoords);
	void positionQuad(sf::Vertex* vertex, const sf::FloatRect rect);
	void colorQuad(sf::Vertex* vertex, const sf::Color color);
}
