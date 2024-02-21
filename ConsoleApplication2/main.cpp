#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
//This should be separated into another file but later!
int main()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "SFML Application", sf::Style::Fullscreen);

    // Backround Texture on the main page
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("")) {
        std::cerr << "Could not load background texture" << std::endl;
        return -1; // If for some reason we have forgotten the texture it won't break the program!
    }

    // The part that creates the backround!
    sf::RectangleShape background(sf::Vector2f(desktop.width, desktop.height));
    background.setTexture(&backgroundTexture); // This part applies the texture!

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
            // This thing closes the program
        }

        window.clear();
        window.draw(background); // The backround should be with a texture soon!
        window.draw(square); // This is for a test
        window.draw(exitButton); // The exit button should not be the first!
        window.display();
    }

    return 0;
}
