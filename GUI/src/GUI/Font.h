#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include <stdint.h>
#include <map>
#include <filesystem>

namespace fs = std::filesystem;

namespace gui {

class Font {
protected:
	// assumption that all images must be the same size
	//std::map<int, sf::Image> images;
	std::vector<sf::Texture> textureData;
	std::map<int, sf::Texture*> textures;
	std::map<int, fs::path> imagePaths;
	sf::Vector2u charSize;
	std::vector<uint8_t> charWidths;
	bool isLoaded = false;
	sf::Image noImage;
	unsigned int charactersPerImage;

public:
	Font() {}

	bool load(
		const sf::Vector2u charSize,
		const fs::path& fontWidthFile,
		std::map<int, fs::path> imagePaths,
		unsigned int charactersPerImage
	);
	const sf::IntRect getCharacter(unsigned int code) const;
	// const sf::Image& getImage(unsigned int code);
	const sf::Texture* getTexture(unsigned int code);
	int numberOfCharactersPerTexture() const;

protected:
	// const sf::Image& loadImage(int id);
};

}