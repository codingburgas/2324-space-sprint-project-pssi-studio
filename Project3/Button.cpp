#include "Button.h"
#include <iostream>

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& texturePath) {
    shape.setPosition(position);
    shape.setSize(size);
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Could not load texture: " << texturePath << std::endl;
    }
    shape.setTexture(&texture);
}

bool Button::isClicked(sf::RenderWindow& window) const {
    return shape.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}
