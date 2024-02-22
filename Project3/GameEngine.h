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
    sf::Texture additionalElementTexture;
    sf::RectangleShape additionalElement;
    sf::RectangleShape StudioText;
    sf::Texture StudioTextTexture;
    sf::Texture playButtonTexture;
    sf::RectangleShape playButton;
    sf::RectangleShape background1;
    sf::RectangleShape background2;


    sf::Clock clock;

    sf::Vector2f logoStartPosition;
    sf::Vector2f logoEndPosition = sf::Vector2f(screenWidth / 2 - logo.getSize().x / 2, screenHeight / 3);
    sf::Vector2f playButtonStartPosition;
    sf::Vector2f playButtonEndPosition;

    sf::SoundBuffer soundBuffer;
    sf::Sound sound;

    // These are somewhat like an event value mainly used for loading and unloading elements that should be loaded again!
    unsigned int screenWidth;
    unsigned int screenHeight;
    bool logoVisible = true;
    bool StudioTextPopped = false;
    bool mainMenuActive = false;
    bool logoAnimationActive = false;
    float logoAnimationTime = 0.0f;

    float backgroundMoveSpeed = 10.0f;
    float backgroundOffset = 0.0f;
   
    bool playButtonAnimationActive = false;
    float playButtonAnimationTime = 0.0f;
    float playButtonOpacity = 0.0f;


    // Calls the main functions
    void processEvents();
    void update();
    void render();
    void loadContent();
    void initializeUI();
    void animateLogo(float deltaTime);
};

#endif
