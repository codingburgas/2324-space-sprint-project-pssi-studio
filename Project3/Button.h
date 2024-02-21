// This is for the exit Button in case you wonder!


#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class Button {
public:
    Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& texturePath);

    bool isClicked(sf::RenderWindow& window) const;
    void draw(sf::RenderWindow& window) const;

private:
    sf::RectangleShape shape;
    sf::Texture texture;
};

#endif
