#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

int main()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "SFML Application", sf::Style::Fullscreen);

    // Load the texture
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("")) {
        std::cerr << "Could not load background texture" << std::endl;
        return -1; // Exit if the texture can't be loaded
    }

    // Create a rectangle for the background
    sf::RectangleShape background(sf::Vector2f(desktop.width, desktop.height));
    background.setTexture(&backgroundTexture); // Apply the texture

    // Your other entities (square, exit button)...

    sf::RectangleShape square(sf::Vector2f(200.f, 200.f));
    square.setFillColor(sf::Color(0, 0, 139));
    square.setPosition((desktop.width / 2) - (square.getSize().x / 2), (desktop.height / 2) - (square.getSize().y / 2));

    sf::RectangleShape exitButton(sf::Vector2f(50.f, 50.f));
    exitButton.setFillColor(sf::Color::Red);
    exitButton.setPosition(desktop.width - 60, 10);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Event handling (closing window, clicking exit button)...
        }

        window.clear();
        window.draw(background); // Draw the background first
        window.draw(square); // Then draw your square
        window.draw(exitButton); // And the exit button
        window.display();
    }

    return 0;
}
