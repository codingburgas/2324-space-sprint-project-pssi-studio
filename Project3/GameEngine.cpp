#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine() : window(sf::VideoMode::getDesktopMode(), "SFML Application", sf::Style::Fullscreen) {
    loadContent();
    initializeUI();
}

void GameEngine::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void GameEngine::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i clickPos = sf::Mouse::getPosition(window);
                if (exitButton.getGlobalBounds().contains(window.mapPixelToCoords(clickPos))) {
                    window.close(); // Close the program
                }
            }
        }
    }
}

void GameEngine::update() {
    // Update game state
}

void GameEngine::render() {
    window.clear();
    window.draw(background);
    window.draw(square);
    window.draw(exitButton);
    window.display();
}

void GameEngine::loadContent() {
    // Load the textures for Backround!
    if (!backgroundTexture.loadFromFile("Textures/Untitled.jpg")) {
        std::cerr << "Could not load background texture" << std::endl;
    }
    background.setTexture(&backgroundTexture);

    // Load the textures for Close button!
    if (!exitButtonTexture.loadFromFile("Textures/Close.png")) {
        std::cerr << "Could not load exit button texture" << std::endl;
    }
    exitButton.setTexture(&exitButtonTexture);
}

void GameEngine::initializeUI() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    // Setup backround!
    background.setSize(sf::Vector2f(desktop.width, desktop.height));

    // Test it will be removed!
    square.setSize(sf::Vector2f(200.f, 200.f));
    square.setFillColor(sf::Color(0, 0, 139));
    square.setPosition((desktop.width / 2) - (square.getSize().x / 2), (desktop.height / 2) - (square.getSize().y / 2));

    // Setup Close button!
    exitButton.setSize(sf::Vector2f(50.f, 50.f));
    exitButton.setPosition(desktop.width - 60, 10);
}
