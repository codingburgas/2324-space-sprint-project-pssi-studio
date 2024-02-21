// These are the main values for the GameEngine in case you wonder!


#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class GameEngine {
public:
    GameEngine();
    void run();

private:
    // Identify new values here! (Don't remove them only add new once!)
    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Texture logoTexture;
    sf::RectangleShape logo;
    sf::Texture exitButtonTexture;
    sf::RectangleShape exitButton;
    sf::Clock clock;
    sf::Texture additionalElementTexture;
    sf::RectangleShape additionalElement;
    sf::RectangleShape StudioText;
    sf::Texture StudioTextTexture;

    sf::SoundBuffer soundBuffer;
    sf::Sound sound;

    // These are somewhat like an event value mainly used for loading and unloading elements that should be loaded again!
    unsigned int screenWidth;
    unsigned int screenHeight;
    bool logoVisible = true;
    bool StudioTextPopped = false;

    // Calls the main functions
    void processEvents();
    void update();
    void render();
    void loadContent();
    void initializeUI();
    void animateLogo(float deltaTime);
};

#endif
