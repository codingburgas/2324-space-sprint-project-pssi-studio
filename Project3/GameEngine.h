#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SFML/Graphics.hpp>

class GameEngine {
public:
    GameEngine();
    void run();

private:
    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::RectangleShape square;
    sf::Texture exitButtonTexture;
    sf::RectangleShape exitButton;

    // Render elements
    void processEvents();
    void update();
    void render();
    void loadContent(); 
    void initializeUI();
};

#endif
