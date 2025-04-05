#include "Font.h"
#include <fstream>
#include <sstream>

namespace gui {

bool Font::load(
	const sf::Vector2u charSize,
	const fs::path& fontWidthFile,
	std::map<int, fs::path> imagePaths,
	unsigned int charactersPerImage
) {
	this->imagePaths = imagePaths;
	this->charactersPerImage = charactersPerImage;

	std::ifstream fontWidthFileHandle(fontWidthFile, std::ios::binary);
	if (!fontWidthFileHandle.is_open()) {
		printf("Unable to load font width file: %s\n", fontWidthFile.string().c_str());
		fontWidthFileHandle.close(); // just in case
		return false;
	}

	std::stringstream buffer;
	buffer << fontWidthFileHandle.rdbuf();
	fontWidthFileHandle.close();
	std::string charWidthData = buffer.str();

	charWidths.reserve(charWidthData.size());
	for (auto charIter = charWidthData.cbegin(); charIter != charWidthData.cend(); charIter++) {
		charWidths.push_back(uint8_t(*charIter));
	}

	textureData.resize(imagePaths.size());
	int i = 0;
	for (auto it = imagePaths.begin(); it != imagePaths.end(); it++) {
		int texId = it->first;
		if(!textureData[i].loadFromFile(it->second)) {
			printf("Failed to load texture from file: %d\n", i);
			textures[texId] = nullptr;
		}
		else {
			textures[texId] = &textureData[i];
		}
		i++;
	}

	isLoaded = true;
	return true;
}

const sf::IntRect Font::getCharacter(unsigned int code) const {
	sf::IntRect texRect;
	if (!isLoaded) {
		return texRect;
	}

	uint8_t charWidth = charWidths[code];

	code %= charactersPerImage;
	int right = charWidth & 0x0F;
	int left = ((charWidth & 0xF0) >> 4) & 0x0F;
	return { {(int)(code % 16 * 16) + left, (int)(code / 16 * 16)}, {right - left + 1, 16}};
}

const sf::Texture* Font::getTexture(unsigned int code) {
	int texId = code / charactersPerImage;

	auto it = textures.find(texId);
	if (it == textures.end()) {
		return nullptr;
	}

	return it->second;
}

int Font::numberOfCharactersPerTexture() const {
	return charactersPerImage;
}

//const sf::Image& Font::loadImage(int id) {
//	auto it = imagePaths.find(id);
//
//	if (it == imagePaths.end()) {
//		printf("Image id does not have a registered image path: %d\n", id);
//		return noImage;
//	}
//
//	images.emplace(id, sf::Image());
//	bool loaded = images[id].loadFromFile(it->second);
//
//	if (loaded) {
//		return images[id];
//	}
//
//	printf("Failed to load image from file: %d\n", id);
//	return noImage;
//}
//
//const sf::Image& Font::getImage(unsigned int code) {
//	if (!isLoaded) {
//		printf("Attempt to get font image before font is loaded!\n");
//		return noImage;
//	}
//
//	int id = code / charactersPerImage;
//
//	auto it = images.find(id);
//	if (it != images.end()) {
//		return it->second;
//	}
//
//	return loadImage(id);
//}

}
