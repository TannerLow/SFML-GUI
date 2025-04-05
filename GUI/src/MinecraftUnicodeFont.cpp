#include "MinecraftUnicodeFont.h"

MinecraftUnicodeFont::MinecraftUnicodeFont() {
	
}

bool MinecraftUnicodeFont::openFromFile(const fs::path& filename) {
	info.family = "Minecraft Unicode";
	
	if(!texture.loadFromFile(filename)) {
		return false;
	}

	for (int i = 0; i < 256; i++) {
		sf::Glyph glyph;
		glyph.advance = 8;
		glyph.bounds = { {0, 0}, {8, 8} };
		glyph.textureRect = { {(i % 16) * 8, (i / 16) * 8}, {8, 8} };
		glyphs.emplace((char32_t)i, glyph);
	}

	errorGlyph.advance = 6;
	errorGlyph.bounds = { {0, 0}, {6, 7} };
	errorGlyph.textureRect = { {120, 24}, {8, 8} };
}

const sf::Font::Info& MinecraftUnicodeFont::getInfo() const {
	return info;
}

const sf::Glyph& MinecraftUnicodeFont::getGlyph(char32_t codePoint, unsigned int characterSize, bool bold, float outlineThickness) const {
	auto it = glyphs.find(codePoint);
	if (it != glyphs.end()) {
		return it->second;
	}
	return errorGlyph;
}

bool MinecraftUnicodeFont::hasGlyph(char32_t codePoint, unsigned int characterSize, bool bold, float outlineThickness) const {
	return 0 <= codePoint and codePoint < 256;
}

float MinecraftUnicodeFont::getKerning(uint32_t first, uint32_t second, unsigned int characterSize, bool bold) const {
	return 0;
}
float MinecraftUnicodeFont::getLineSpacing(unsigned int characterSize) const {
	return 8;
}
float MinecraftUnicodeFont::getUnderlinePosition(unsigned int characterSize) const {
	return 0;
}
float MinecraftUnicodeFont::getUnderlineThickness(unsigned int characterSize) const {
	return 0;
}

const sf::Texture& MinecraftUnicodeFont::getTexture(unsigned int characterSize) const {
	return texture;
}

bool MinecraftUnicodeFont::isSmooth() const {
	return false;
}