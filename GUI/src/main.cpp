#include <SFML/Graphics.hpp>
#include "GUI/Div.h"
#include "GUI/Button.h"

#include "TestButton.h"
#include "DraggableButton.h"
#include "GUI/SubElements/ScrollBarButton.h"
#include "GUI/SubElements/ScrollEndButton.h"
#include "GUI/Text.h"
#include "Util/RateLimiter.h"
#include <iostream>

#include <fstream>

int main() {
    RateLimiter rateLimiter(60);

    sf::RenderWindow window(sf::VideoMode({ 1600, 900 }), "SFML GUI Driver");

    sf::Vector2u testRectSize = { 100, 200 };
    sf::Vector2u testRectSizeB = { 50, 50 };

    sf::RectangleShape greenRect;
    greenRect.setSize({ 150, 100 });
    greenRect.setFillColor(sf::Color::Green);
    greenRect.setPosition({ 10, 10 });

    sf::RectangleShape redRectOutline;
    redRectOutline.setSize(sf::Vector2f(testRectSize));
    redRectOutline.setFillColor(sf::Color::Transparent);
    redRectOutline.setOutlineThickness(-3.f);
    redRectOutline.setOutlineColor(sf::Color::Red);

    sf::RectangleShape whiteRect;
    whiteRect.setSize({ 150, 100 });
    whiteRect.setFillColor(sf::Color::White);
    whiteRect.setPosition({ 5, 5 });

    sf::RectangleShape magentaRectOutline;
    magentaRectOutline.setSize(sf::Vector2f(testRectSizeB));
    magentaRectOutline.setFillColor(sf::Color::Transparent);
    magentaRectOutline.setOutlineThickness(-3.f);
    magentaRectOutline.setOutlineColor(sf::Color::Magenta);

    gui::Div div(testRectSize);
    div.clickEnabled = true;
    //div.draggable = true;
    div.hoverable = true;
    div.elements.push_back(&greenRect);
    div.elements.push_back(&redRectOutline);
    div.setPosition({10, 10});
    div.setScale({2, 2});

    gui::Div subDiv({ 50, 50 }, { {0, 0}, {50, 20} });
    subDiv.clickEnabled = true;
    subDiv.draggable = true;
    subDiv.dragLockedX = true;
    subDiv.dragMinY = 10;
    subDiv.dragMaxY = 100;
    subDiv.hoverable = true;
    subDiv.elements.push_back(&whiteRect);
    subDiv.elements.push_back(&magentaRectOutline);
    subDiv.setPosition({ 10, 20 });
    //subDiv.setScale({ 2, 2 });

    div.elements.push_back(&subDiv);

    
    TestButton button({100, 50});
    button.setPosition({400, 300});

    DraggableButton dragButton({100, 50});
    dragButton.setPosition({1000, 200});

    gui::ScrollBarButton scrollButton({ 50, 20 }, gui::ScrollSide::Horizontal, {400, 1000});
    scrollButton.setPosition({400, 800});

    gui::ScrollEndButton scrollEndButtonLeft({20, 20}, gui::ScrollDirection::DOWN_LEFT, &scrollButton);
    scrollEndButtonLeft.setPosition({scrollButton.getLowestPointOfBar() - 20, 800});

    gui::ScrollEndButton scrollEndButtonRight({ 20, 20 }, gui::ScrollDirection::UP_RIGHT, &scrollButton);
    scrollEndButtonRight.setPosition({ scrollButton.getHighestPointOfBar(), 800 });

    sf::Font font;
    if (!font.openFromFile("resources/RuneScape-Plain-12.ttf"))
    {
        std::cout << "Failed to load resources/RuneScape-Plain-12.ttf font file" << std::endl;
    }
    font.setSmooth(false);
    sf::Text text(font); // a font is required to make a text object
    // set the string to display
    text.setString("Welcome to Runescape");
    // set the character size
    text.setCharacterSize(72); // in pixels, not points!
    text.setPosition({ 400, 30 });

    gui::Font minecraftFont;
    std::map<int, fs::path> imagePaths;
    imagePaths.emplace(0x00, fs::path("resources/font/unicode_page_00.png"));
    imagePaths.emplace(0x01, fs::path("resources/font/unicode_page_01.png"));
    imagePaths.emplace(0x5e, fs::path("resources/font/unicode_page_5e.png"));
    minecraftFont.load({16, 16}, "resources/font/font_widths.dat", imagePaths, 256);
    //auto _a = minecractFont.getCharacter('A');
    //auto _b = minecractFont.getTexture('A');
    //sf::Sprite s(*_b, _a);
    gui::Text minecraftText(&minecraftFont);
    minecraftText.setString(L"I am Steve@@@\x100\x5e00");
    minecraftText.setScale({ 2, 2 });
    minecraftText.move({ 100, 30 });

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                sf::Vector2f clickCoords = sf::Vector2f(sf::Mouse::getPosition(window));
                div.click(clickCoords, mouseButtonPressed->button);
                button.click(clickCoords, mouseButtonPressed->button);
                dragButton.click(clickCoords, mouseButtonPressed->button);
                scrollButton.click(clickCoords, mouseButtonPressed->button);
                scrollEndButtonLeft.click(clickCoords, mouseButtonPressed->button);
                scrollEndButtonRight.click(clickCoords, mouseButtonPressed->button);
            }
            else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonReleased>()) {
                sf::Vector2f coords = sf::Vector2f(sf::Mouse::getPosition(window));
                div.releaseClick(coords, mouseButtonPressed->button);
                //button.click(clickCoords, mouseButtonPressed->button);
                dragButton.releaseClick(coords, mouseButtonPressed->button);
                scrollButton.releaseClick(coords, mouseButtonPressed->button);
                scrollEndButtonLeft.releaseClick(coords, mouseButtonPressed->button);
                scrollEndButtonRight.releaseClick(coords, mouseButtonPressed->button);
            }
        }

        if (window.hasFocus()) {
            sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
            div.handleHover(mousePos);
            button.handleHover(mousePos);
            dragButton.handleHover(mousePos);
            scrollButton.handleHover(mousePos);
            scrollEndButtonLeft.handleHover(mousePos);
            scrollEndButtonRight.handleHover(mousePos);
        }

        scrollEndButtonLeft.update();
        scrollEndButtonRight.update();

        if (rateLimiter.isReady()) {
            window.clear();
            //window.draw(div);
            //window.draw(button);
            //window.draw(dragButton);
            window.draw(scrollButton);
            window.draw(scrollEndButtonRight);
            window.draw(scrollEndButtonLeft);
            //window.draw(text);
            //window.draw(s);
            window.draw(minecraftText);
            window.display();
        }
    }
}

//void setLower(uint8_t& num, uint8_t fourBits) {
//    fourBits &= 0x0F;
//    num &= 0xF0;
//    num |= fourBits;
//}
//
//void setUpper(uint8_t& num, uint8_t fourBits) {
//    fourBits &= 0x0F;
//    fourBits <<= 4;
//    num &= 0x0F;
//    num |= fourBits;
//}
//
//bool containsPixel(const sf::Image& img, int row, int col, int subCol) {
//    sf::Color empty(0, 0, 0, 0);
//    for (int i = 0; i < 16; i++) {
//        if (img.getPixel({ col * 16 + subCol, row * 16 + i }) != empty) {
//            return true;
//        }
//    }
//    return false;
//}
//
//bool createFontWidthDatFile(const std::string& fontPath, const std::string& filepath) {
//    bool success = true;
//
//    std::ofstream file(filepath, std::ios::binary);
//
//    if (!file.is_open())
//        success = false;
//
//    sf::Image image;
//    if (!image.loadFromFile(fontPath))
//        return false;
//
//    for (int i = 0;;) {
//
//    }
//
//    uint8_t value = 0;
//    for (int row = 0; row < 256; row++) {
//        for (int col = 0; col < 256; col++) {
//            uint8_t value = 0xF0;
//            // find front
//            for (int subCol = 0; subCol < 16; subCol++) {
//                if (containsPixel(image, row, col, subCol)) {
//                    setUpper(value, (uint8_t)subCol);
//                    break;
//                }
//            }
//            // find back
//            for (int subCol = 15; subCol >= 0; subCol--) {
//                if (containsPixel(image, row, col, subCol)) {
//                    setLower(value, (uint8_t)subCol);
//                    break;
//                }
//            }
//
//            if (row == 0 and col == 32) {
//                value = 0x07; // make space ' ' half character width
//            }
//
//            file << ((unsigned char)value);
//        }
//    }
//
//    if (file.bad())
//        success = false;
//
//    file.close();
//
//    return success;
//}