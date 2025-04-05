#pragma once
#include <SFML/Graphics.hpp>
#include "Font.h"
#include <map>

namespace gui {

class Text : public sf::Drawable, public sf::Transformable {
protected:
	struct VertexArrayInfo {
		sf::VertexArray vertices;
		const sf::Texture* texture;
		size_t quadPosition = 0;
		size_t charCount = 0;
	};

	Font* font;
	sf::String text;
	std::unordered_map<int, VertexArrayInfo> vertexArrays;

public:
	Text(Font* font) : font(font) {}

	void setString(sf::String text);

protected: 
	// void renderWithTextureUpdates(); Maybe some optimization I can do if I need to update text colors without changing positions or texCoords
	void render();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

}