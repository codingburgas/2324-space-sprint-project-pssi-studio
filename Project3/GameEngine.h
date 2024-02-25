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
    sf::RectangleShape expeditionBackground;
    sf::RectangleShape newExpeditionButton, loadExpeditionButton, CrewButton;
    sf::Texture expeditionBackgroundTexture, newExpeditionButtonTexture, loadExpeditionButtonTexture, CrewButtonTexture;
    sf::Texture expeditionTitleTexture;
    sf::RectangleShape expeditionTitleShape;
    sf::RectangleShape spaceShip;
    sf::Texture spaceShipTexture;
    std::vector<sf::RectangleShape> meteors;
    sf::Texture meteorTexture;
    sf::RectangleShape bigPlanet;
    sf::Texture bigPlanetTexture;
    sf::RectangleShape homeButton;
    sf::Texture homeButtonTexture;


    sf::Clock clock;

    sf::Vector2f logoStartPosition;
    sf::Vector2f logoEndPosition = sf::Vector2f(screenWidth / 2 - logo.getSize().x / 2, screenHeight / 3);
    sf::Vector2f playButtonStartPosition;
    sf::Vector2f playButtonEndPosition;
    sf::Vector2f spaceShipLandingPosition;

    sf::SoundBuffer soundBuffer;
    sf::Sound sound;
    sf::Texture earthTexture;
    sf::RectangleShape earth;
    sf::Texture secondPlanetTexture;
    sf::RectangleShape secondPlanet;

    sf::Texture congratulationsTexture;
    sf::Sprite congratulationsSprite;
    sf::RectangleShape continueButton;
    sf::Texture continueButtonTexture;
    sf::RectangleShape popupBackground;
    std::vector<sf::Text> crewOptions;
    sf::Font font;
    //Those too (Don't touch)
    std::vector<std::string> roles = { "Space Ship", "Captain", "Repairman", "Navigator", "Engineer" };
    std::map<std::string, std::vector<std::string>> crewMembers;
    bool showCongratulationsScreen = false;


    // These are somewhat like an event value mainly used for loading and unloading elements that should be loaded again!
    unsigned int screenWidth;
    unsigned int screenHeight;
    bool logoVisible = true;
    bool StudioTextPopped = false;
    bool mainMenuActive = false;
    bool logoAnimationActive = false;
    float logoAnimationTime = 0.0f;

    bool spaceGameActive = false;
    float meteorSpawnTimer = 0.0f;
    const float meteorSpawnRate = 0.5f;

    float backgroundMoveSpeed = 10.0f;
    float backgroundOffset = 0.0f;
   
    bool playButtonAnimationActive = false;
    float playButtonAnimationTime = 0.0f;
    float playButtonOpacity = 0.0f;

    float gameSessionTimer = 0.0f;
    bool gameEnded = false;

    bool expeditionScreenActive;
    bool landingAnimationStarted;
    bool spaceshipLanded;

    bool crewSelectionScreenActive = false;

    bool startingPhase = true;
    float startingPhaseTimer = 0.0f;


    // Calls the main functions
    void processEvents();
    void initializeExpeditionUI();
    void update();
    void render();
    void loadContent();
    void initializeUI();
    void initializeSpaceGame();
    void updateMeteors(float deltaTime);
    void checkCollisions();
    void animateLogo(float deltaTime);
    void resetGameState();
    void handleContinueButtonClick();
    void handleHomeButtonClick();
    //Those will be used on a later state!!! (Don't remove)
    void showCrewSelection();
    void selectCrewMember(const sf::Vector2f& mousePos);
    void initializeCrewMembers();

};

#endif
