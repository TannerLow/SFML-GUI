#include <SFML/Graphics.hpp>
#include "GUI/Div.h"

#include "Util/RateLimiter.h"
#include <iostream>

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
    div.hoverable = true;
    div.elements.push_back(&greenRect);
    div.elements.push_back(&redRectOutline);
    div.setPosition({10, 10});
    div.setScale({2, 2});

    gui::Div subDiv({ 50, 50 });
    subDiv.clickEnabled = true;
    subDiv.hoverable = true;
    subDiv.elements.push_back(&whiteRect);
    subDiv.elements.push_back(&magentaRectOutline);
    subDiv.setPosition({ 10, 20 });
    //subDiv.setScale({ 2, 2 });

    div.elements.push_back(&subDiv);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseButtonPressed->button == sf::Mouse::Button::Right) {
                    std::cout << "the right button was pressed" << std::endl;
                    std::cout << "mouse x: " << mouseButtonPressed->position.x << std::endl;
                    std::cout << "mouse y: " << mouseButtonPressed->position.y << std::endl;

                    div.click(sf::Vector2f(sf::Mouse::getPosition(window)));
                }
            }
        }

        if (window.hasFocus()) {
            div.handleHover(sf::Vector2f(sf::Mouse::getPosition(window)));
        }

        rateLimiter.tick();

        window.clear();
        window.draw(div);
        window.display();
    }
}
