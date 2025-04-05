#include "Text.h"
#include "../Util/VertexHelper.h"
#include <set>

namespace gui {

void Text::render() {
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
		vertexArrays[texId].charCount++;
	}

	for (auto& info : vertexArrays) {
		info.second.vertices.resize(info.second.charCount * 6);
	}

	float nextCharPos = 0;
	for (int i = 0; i < text.getSize(); i++) {
		const sf::IntRect texCoords = font->getCharacter(text[i]);
		VertexArrayInfo& info = vertexArrays[text[i] / font->numberOfCharactersPerTexture()];
		vh::positionQuad(&info.vertices[info.quadPosition * 6], { {nextCharPos, 0}, {(float)texCoords.size.x, 16} });
		vh::updateQuadTexture(&info.vertices[info.quadPosition * 6], texCoords);
		info.quadPosition++;
		nextCharPos += texCoords.size.x + 2;
	}
}

void Text::setString(sf::String text) {
	this->text = text;
	render();
}

void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();

	for (const auto& info : vertexArrays) {
		states.texture = info.second.texture;
		target.draw(info.second.vertices, states);
	}
}

}
