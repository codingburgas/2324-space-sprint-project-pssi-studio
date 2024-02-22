// GameEngine used to run most of the stuff happening! Also the graphics!

#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine() : window(sf::VideoMode::getDesktopMode(), "SFML Application", sf::Style::Fullscreen),screenWidth(sf::VideoMode::getDesktopMode().width),screenHeight(sf::VideoMode::getDesktopMode().height) {
    window.setFramerateLimit(60);
    logoVisible = true;
    loadContent();
    initializeUI();
}


void GameEngine::run() {
    // This is the main function it operates the game by calling all otehr functions!
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void GameEngine::processEvents() {
    // over all calls the exit button for now!
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i clickPos = sf::Mouse::getPosition(window);
                if (exitButton.getGlobalBounds().contains(window.mapPixelToCoords(clickPos))) {
                    window.close();
                }
            }
        }
    }
}

void GameEngine::update() {
    float deltaTime = clock.restart().asSeconds();
    animateLogo(deltaTime);
    // Logo Animation
    if (logoAnimationActive) {
        logoAnimationTime += deltaTime;
        float duration = 1.0f;
        float progress = std::min(logoAnimationTime / duration, 1.0f);

        logo.setPosition(
            logoStartPosition.x + (logoEndPosition.x - logoStartPosition.x) * progress,
            logoStartPosition.y + (logoEndPosition.y - logoStartPosition.y) * progress
        );

        if (progress >= 1.0f) logoAnimationActive = false;
    }

    // Play Button Animation
    if (playButtonAnimationActive) {
        playButtonAnimationTime += deltaTime;
        float duration = 1.0f;
        float progress = std::min(playButtonAnimationTime / duration, 1.0f);

        playButton.setPosition(
            playButtonStartPosition.x + (playButtonEndPosition.x - playButtonStartPosition.x) * progress,
            playButtonStartPosition.y + (playButtonEndPosition.y - playButtonStartPosition.y) * progress
        );

        playButtonOpacity = 255 * progress;
        playButton.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(playButtonOpacity)));

        if (progress >= 1.0f) playButtonAnimationActive = false;
    }
    // Backround Animation
    float moveAmount = backgroundMoveSpeed * deltaTime;
    background1.move(-moveAmount, 0);
    background2.move(-moveAmount, 0);

    if (background1.getPosition().x + screenWidth < 0) {
        background1.setPosition(background2.getPosition().x + screenWidth, 0);
    }

    if (background2.getPosition().x + screenWidth < 0) {
        background2.setPosition(background1.getPosition().x + screenWidth, 0);
    }
}

void GameEngine::render() {
    // Really simple it renders the elements!
    window.clear();
    window.draw(background1);
    window.draw(background2);

    if (logoVisible) {
        window.draw(logo);
    }
    window.draw(exitButton);

    if (StudioTextPopped) {
        window.draw(StudioText);
    }
    if (mainMenuActive) {
        window.draw(playButton);
    }

    window.display();
}


void GameEngine::loadContent() {
    // This is the main loading function here! (Only add elements and don't remove them!)
    if (!backgroundTexture.loadFromFile("Textures/Background.jpg")) {
        std::cerr << "Could not load background texture" << std::endl;
    }
    background.setTexture(&backgroundTexture);

    if (!logoTexture.loadFromFile("Textures/Logo.png")) {
        std::cerr << "Could not load logo texture" << std::endl;
    }
    logo.setTexture(&logoTexture);

    if (!exitButtonTexture.loadFromFile("Textures/Close.png")) {
        std::cerr << "Could not load exit button texture" << std::endl;
    }
    exitButton.setTexture(&exitButtonTexture);

    if (!soundBuffer.loadFromFile("Audio/IntroSound.mp3")) {
        std::cerr << "Failed to load sound file" << std::endl;
    }
    else {
        std::cout << "Sound file loaded successfully" << std::endl;
    }
    sound.setBuffer(soundBuffer);

    if (!StudioTextTexture.loadFromFile("Textures/StudioText.png")) {
        std::cerr << "Could not load StudioText texture" << std::endl;
    }
    StudioText.setTexture(&StudioTextTexture);
    if (!playButtonTexture.loadFromFile("Textures/PlayButton.png")) {
        std::cerr << "Could not load play button texture" << std::endl;
    }
    playButton.setTexture(&playButtonTexture);
}

void GameEngine::initializeUI() {

    // This over all sets the sizes of the elements also the possitions! (Really Don't touch here :D)

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    background.setSize(sf::Vector2f(desktop.width, desktop.height));

    logo.setSize(sf::Vector2f(200.f, 200.f));
    logo.setPosition((screenWidth / 2) - (logo.getSize().x / 2), screenHeight - logo.getSize().y);

    exitButton.setSize(sf::Vector2f(50.f, 50.f));
    exitButton.setPosition(desktop.width - 60, 10);

    StudioText.setSize(sf::Vector2f(100.f, 100.f));
    StudioText.setPosition(-100.f, -100.f);

    logoEndPosition = sf::Vector2f(screenWidth / 2 - logo.getSize().x / 2, screenHeight / 3);
    playButton.setSize(sf::Vector2f(200.f, 100.f));
    playButtonStartPosition = sf::Vector2f(screenWidth / 2 - playButton.getSize().x / 2, screenHeight + 20.f);
    playButton.setFillColor(sf::Color(255, 255, 255, 0));

    background1.setTexture(&backgroundTexture);
    background2.setTexture(&backgroundTexture);

    background1.setSize(sf::Vector2f(screenWidth, screenHeight));
    background1.setPosition(0, 0);

    background2.setSize(sf::Vector2f(screenWidth, screenHeight));
    background2.setPosition(screenWidth, 0);
}

void GameEngine::animateLogo(float deltaTime) {
    // Play the introduction sound here! (Don't touch here :D)
    static bool soundPlayed = false;
    if (!soundPlayed) {
        sound.play();
        soundPlayed = true;
    }

    static float movementDuration = 0;
    movementDuration += deltaTime;

    // Define and tweak the values for the introduction screen!
    float logoToCenterDuration = 1.3f;
    float postLogoDuration = 2.0f;
    float cycleDuration = logoToCenterDuration + postLogoDuration + 2.0f;

    // The main logo should show here!
    if (movementDuration <= logoToCenterDuration) {
        float progress = movementDuration / logoToCenterDuration;
        float middleYPosition = screenHeight / 2 - logo.getSize().y / 2;
        float bottomYPosition = screenHeight - logo.getSize().y;
        logo.setPosition(screenWidth / 2 - logo.getSize().x / 2, bottomYPosition + progress * (middleYPosition - bottomYPosition));
    }

    // The Studio Text should show here!
    if (movementDuration > logoToCenterDuration && movementDuration <= postLogoDuration) {
        if (!StudioTextPopped) {
            StudioText.setSize(sf::Vector2f(300.f, 100.f));

            float margin = 20.f;
            float studioTextY = logo.getPosition().y + logo.getSize().y + margin;
            StudioText.setPosition((screenWidth - StudioText.getSize().x) / 2, studioTextY);

            StudioTextPopped = true;
        }
    }

    // This is for the PlayButton!
    if (movementDuration > cycleDuration && !mainMenuActive) {
        mainMenuActive = true;
        logoAnimationActive = true;
        StudioTextPopped = false;
        logoStartPosition = logo.getPosition();
        logoAnimationTime = 0.0f;

        playButtonAnimationActive = true;
        playButtonEndPosition = sf::Vector2f(screenWidth / 2 - playButton.getSize().x / 2, logoEndPosition.y + logo.getSize().y + 20.f);
        playButtonAnimationTime = 0.0f;
        playButtonOpacity = 0;
    }
}