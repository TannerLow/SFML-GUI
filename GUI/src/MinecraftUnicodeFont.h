#pragma once
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <map>

namespace fs = std::filesystem;

class MinecraftUnicodeFont : public sf::Font {
private:
	sf::Font::Info info;
	sf::Texture texture;
	std::map<char32_t, sf::Glyph> glyphs;
	sf::Glyph errorGlyph;

public:
	MinecraftUnicodeFont();
	MinecraftUnicodeFont(const fs::path& filename) = delete;
	MinecraftUnicodeFont(const void* data, std::size_t sizeInBytes) = delete;
	MinecraftUnicodeFont(sf::InputStream& stream) = delete;

	bool openFromFile(const fs::path& filename);
	bool openFromMemory(const void* data, std::size_t sizeInBytes) = delete;
	bool openFromStream(sf::InputStream& stream) = delete;

	const sf::Font::Info& getInfo() const;
	const sf::Glyph& getGlyph(char32_t codePoint, unsigned int characterSize, bool bold, float outlineThickness = 0) const;
	bool hasGlyph(char32_t codePoint, unsigned int characterSize, bool bold, float outlineThickness = 0) const;
	float getKerning(uint32_t first, uint32_t second, unsigned int characterSize, bool bold = false) const;
	float getLineSpacing(unsigned int characterSize) const;
	float getUnderlinePosition(unsigned int characterSize) const;
	float getUnderlineThickness(unsigned int characterSize) const;
	const sf::Texture& getTexture(unsigned int characterSize) const;
	void setSmooth(bool smooth) = delete;
	bool isSmooth() const;

private:

};
