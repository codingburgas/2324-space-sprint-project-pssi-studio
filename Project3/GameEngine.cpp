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
    //Used to control events such as clicking buttons for now!
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i clickPos = sf::Mouse::getPosition(window);
                sf::Vector2f worldPos = window.mapPixelToCoords(clickPos);
                if (exitButton.getGlobalBounds().contains(worldPos)) {
                    std::cout << "Exit Button Clicked" << std::endl;
                    window.close();
                }
                if (mainMenuActive && playButton.getGlobalBounds().contains(worldPos)) {
                    std::cout << "Play Button Clicked" << std::endl;
                    expeditionScreenActive = true;
                    mainMenuActive = false;
                    logoVisible = false;
                    initializeExpeditionUI();
                }
            }
            break;
        }
    }
}




void GameEngine::update() {
    //Used to update the game state!
    float deltaTime = clock.restart().asSeconds();
    animateLogo(deltaTime);

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
    //Over all renders every element of the game!
    window.clear();

    window.draw(background1);
    window.draw(background2);
    window.draw(exitButton);

    if (expeditionScreenActive) {
        window.draw(expeditionBackground);
        window.draw(expeditionTitleShape);
        window.draw(newExpeditionButton);
        window.draw(loadExpeditionButton);
        window.draw(oldExpeditionsButton);
    }
    else {
        if (logoVisible) {
            window.draw(logo);
        }


        if (StudioTextPopped) {
            window.draw(StudioText);
        }
        if (mainMenuActive) {
            window.draw(playButton);
        }
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
    if (!expeditionBackgroundTexture.loadFromFile("Textures/ExpeditionBackground.jpg")) {
        std::cerr << "Could not load expedition background texture" << std::endl;
    }
    else {
        expeditionBackground.setTexture(&expeditionBackgroundTexture);
    }
    if (!expeditionTitleTexture.loadFromFile("Textures/ExpeditionTitle.png")) {
        std::cerr << "Could not load expedition title texture" << std::endl;
    }
    if (!newExpeditionButtonTexture.loadFromFile("Textures/NewExpeditionButton.png") ||
        !loadExpeditionButtonTexture.loadFromFile("Textures/LoadExpeditionButton.png") ||
        !oldExpeditionsButtonTexture.loadFromFile("Textures/OldExpeditionsButton.png")) {
        std::cerr << "Could not load one or more button textures" << std::endl;
    }
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

void GameEngine::initializeExpeditionUI() {
    expeditionBackground.setTexture(&expeditionBackgroundTexture);
    expeditionBackground.setSize(sf::Vector2f(1500.f, 800.f));
    expeditionBackground.setPosition(
        (screenWidth / 2.f) - (expeditionBackground.getSize().x / 2.f),
        (screenHeight / 2.f) - (expeditionBackground.getSize().y / 2.f)
    );

    // Initialize the title shape with texture
    expeditionTitleShape.setTexture(&expeditionTitleTexture); // Use the corrected member name
    expeditionTitleShape.setSize(sf::Vector2f(500.f, 200.f));
    expeditionTitleShape.setPosition(screenWidth / 2.f - expeditionTitleShape.getSize().x / 2.f,
        screenHeight / 2.f - expeditionBackground.getSize().y / 2.f - 220.f);

    // Initialize buttons
    newExpeditionButton.setTexture(&newExpeditionButtonTexture);
    loadExpeditionButton.setTexture(&loadExpeditionButtonTexture);
    oldExpeditionsButton.setTexture(&oldExpeditionsButtonTexture);

    float buttonWidth = 400.f;
    float buttonHeight = 150.f;
    float spacing = 40.f; // Spacing between buttons

    // Set sizes and initial positions (you might adjust these positions based on your UI layout)
    newExpeditionButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    loadExpeditionButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    oldExpeditionsButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));

    // Position buttons in a column within the expedition background
    float startX = screenWidth / 2.f - buttonWidth / 2.f;
    float startY = screenHeight / 2.f - (1.5f * buttonHeight + spacing); // Adjust startY as needed to center the buttons

    newExpeditionButton.setPosition(startX, startY);
    loadExpeditionButton.setPosition(startX, startY + buttonHeight + spacing);
    oldExpeditionsButton.setPosition(startX, startY + 2 * (buttonHeight + spacing));
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