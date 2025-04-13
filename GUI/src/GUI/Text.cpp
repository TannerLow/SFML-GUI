#include "Text.h"
#include "../Util/VertexHelper.h"
#include <set>

namespace gui {

void Text::render() {
	boundingBox = sf::FloatRect();
	vertexArrays.clear();

	std::unordered_map<int, size_t> charCounts;

	for (int i = 0; i < text.getSize(); i++) {
		int texId = text[i] / font->numberOfCharactersPerTexture();
		auto it = vertexArrays.find(texId);
		if (it == vertexArrays.end()) {
			VertexArrayInfo info;
			vertexArrays[texId] = info; 
			vertexArrays[texId].vertices = sf::VertexArray(sf::PrimitiveType::Triangles);
			vertexArrays[texId].texture = font->getTexture(text[i]);
		}

		// we will skip rendering an actual quad for newlines
		if (text[i] != '\n') {
			vertexArrays[texId].charCount++;
		}
	}

	for (auto& info : vertexArrays) {
		info.second.vertices.resize(info.second.charCount * 6);
	}

	sf::Vector2f nextCharPos = { 0, 0 };
	for (int i = 0; i < text.getSize(); i++) {
		const sf::IntRect texCoords = font->getCharacter(text[i]);

		if (text[i] == '\n') {
			nextCharPos.y += texCoords.size.y + lineSpacing;
			nextCharPos.x = 0;
			continue;
		}
		
		if (boundLine != 0 and nextCharPos.x + texCoords.size.x > boundLine) {
			nextCharPos.y += texCoords.size.y + lineSpacing;
			nextCharPos.x = 0;
		}

		VertexArrayInfo& info = vertexArrays[text[i] / font->numberOfCharactersPerTexture()];
		vh::positionQuad(&info.vertices[info.quadPosition * 6], { nextCharPos, sf::Vector2f(texCoords.size) });
		vh::updateQuadTexture(&info.vertices[info.quadPosition * 6], texCoords);
		info.quadPosition++;
		nextCharPos.x += texCoords.size.x + 2;
		
		if (nextCharPos.x - 2 > boundingBox.size.x) {
			boundingBox.size.x = nextCharPos.x - 2;
		}
		if (nextCharPos.y + texCoords.size.y > boundingBox.size.y) {
			boundingBox.size.y = nextCharPos.y + texCoords.size.y;
		}
	}
}

void Text::setString(sf::String text) {
	this->text = text;
	render();
}

void Text::setFont(Font* font) {
	this->font = font;
}

void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();

	for (const auto& info : vertexArrays) {
		states.texture = info.second.texture;
		target.draw(info.second.vertices, states);
	}
}

void Text::setBound(float boundLine) {
	this->boundLine = boundLine;
	render();
}

sf::FloatRect Text::getBoundingBox() const {
	return getTransform().transformRect(boundingBox);
}

sf::Vector2f Text::getCenter() const {
	return getBoundingBox().size / 2.f;
}

}
