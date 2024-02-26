// GameEngine used to run most of the stuff happening! Also the graphics!

#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine() : window(sf::VideoMode::getDesktopMode(), "SFML Application", sf::Style::Fullscreen), screenWidth(sf::VideoMode::getDesktopMode().width), screenHeight(sf::VideoMode::getDesktopMode().height) {
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
                if (playButton.getGlobalBounds().contains(worldPos) && !playButtonRemoved) {
                    std::cout << "Play Button Clicked" << std::endl;
                    playButtonRemoved = true;
                    expeditionScreenActive = true;
                    mainMenuActive = false;
                    logoVisible = false;
                    initializeExpeditionUI();
                }
                if (newExpeditionButton.getGlobalBounds().contains(worldPos)) {
                    std::cout << "New Expedition Button Clicked" << std::endl;
                    spaceGameActive = true;
                    expeditionScreenActive = false;
                    resetGameState();
                    initializeSpaceGame();
                }
                if (showCongratulationsScreen && continueButton.getGlobalBounds().contains(worldPos.x, worldPos.y)) {
                    handleContinueButtonClick();
                }

                if (showCongratulationsScreen && homeButton.getGlobalBounds().contains(worldPos.x, worldPos.y)) {
                    handleHomeButtonClick();
                }
                if (CrewButton.getGlobalBounds().contains(worldPos)) {
                    crewSelectionScreenActive = !crewSelectionScreenActive;
                    expeditionScreenActive = false;
                    crewSelectionScreenActive = true;

                }
                if (spaceShipAButton.getGlobalBounds().contains(worldPos)) {
                    std::cout << "SpaceShipA Button Clicked" << std::endl;
                    currentSpaceShipTexture = &spaceShipATexture;

                    sf::Vector2u textureSize = currentSpaceShipTexture->getSize();
                    spaceShip.setSize(sf::Vector2f(textureSize.x, textureSize.y));

                    if (spaceGameActive) {
                        spaceShip.setTexture(currentSpaceShipTexture);
                    }

                    crewSelectionScreenActive = false;
                    expeditionScreenActive = true;
                }

                if (spaceShipBButton.getGlobalBounds().contains(worldPos)) {
                    std::cout << "SpaceShipA Button Clicked" << std::endl;
                    currentSpaceShipTexture = &spaceShipBTexture;

                    // Adjust the size of the spaceShip to match the texture's dimensions
                    sf::Vector2u textureSize = currentSpaceShipTexture->getSize();
                    spaceShip.setSize(sf::Vector2f(textureSize.x, textureSize.y)); // Adjust this line as needed

                    if (spaceGameActive) {
                        spaceShip.setTexture(currentSpaceShipTexture);
                    }

                    crewSelectionScreenActive = false;
                    expeditionScreenActive = true;
                }

                if (spaceShipCButton.getGlobalBounds().contains(worldPos)) {
                    std::cout << "SpaceShipA Button Clicked" << std::endl;
                    currentSpaceShipTexture = &spaceShipCTexture;

                    // Adjust the size of the spaceShip to match the texture's dimensions
                    sf::Vector2u textureSize = currentSpaceShipTexture->getSize();
                    spaceShip.setSize(sf::Vector2f(textureSize.x, textureSize.y)); // Adjust this line as needed

                    if (spaceGameActive) {
                        spaceShip.setTexture(currentSpaceShipTexture);
                    }

                    crewSelectionScreenActive = false;
                    expeditionScreenActive = true;
                }

                if (backButton.getGlobalBounds().contains(worldPos)) {
                    std::cout << "Back Button Clicked" << std::endl;
                    crewSelectionScreenActive = false;
                    expeditionScreenActive = true;
                    playButtonAnimationActive = false;
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

    if (spaceGameActive && !gameEnded) {
        gameSessionTimer += deltaTime;

        if (startingPhase) {
            startingPhaseTimer += deltaTime;
            if (startingPhaseTimer >= 5.0f) {
                startingPhase = false;
            }
        }
        else {
            updateMeteors(deltaTime);
        }
        // I set that timer to 10 seconds for testing purposes ! It should be set back to 60 after the test!(Still be aware that here is the time for testing purposes!!!)
        if (gameSessionTimer >= 60.0f) {
            gameEnded = true;
        }

        float moveSpeed = 200 * deltaTime;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            if (spaceShip.getPosition().x > 0) {
                spaceShip.move(-moveSpeed, 0);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            float rightEdge = window.getSize().x - spaceShip.getSize().x;
            if (spaceShip.getPosition().x < rightEdge) {
                spaceShip.move(moveSpeed, 0);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            if (spaceShip.getPosition().y > 0) {
                spaceShip.move(0, -moveSpeed);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            float bottomEdge = window.getSize().y - spaceShip.getSize().y;
            if (spaceShip.getPosition().y < bottomEdge) {
                spaceShip.move(0, moveSpeed);
            }
        }

        if (!startingPhase) {
            checkCollisions();
        }

        if (gameEnded && !showCongratulationsScreen) {
            if (!spaceshipLanded) {
                showCongratulationsScreen = true;
            }
        }
    }

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
    // Clears the window with black color by default
    window.clear();

    // Always draw the background
    window.draw(background1);
    window.draw(background2);
    window.draw(exitButton);

    if (!playButtonRemoved && mainMenuActive) {
        window.draw(playButton);
    }


    if (spaceGameActive) {
        if (startingPhase) {
            window.draw(earth);
        }
        else {
            if (!gameEnded) {

                for (auto& meteor : meteors) {
                    window.draw(meteor);
                }
            }

            window.draw(spaceShip);
        }

        if (gameEnded && spaceshipLanded) {
            window.draw(bigPlanet);
        }
    }
    else {

        if (expeditionScreenActive) {
            window.draw(expeditionBackground);
            window.draw(expeditionTitleShape);
            window.draw(newExpeditionButton);
            window.draw(CrewButton);
        }
        else if (crewSelectionScreenActive) {
            window.draw(crewSelectionBackground);
            window.draw(spaceShipAButton);
            window.draw(spaceShipBButton);
            window.draw(spaceShipCButton);
            window.draw(backButton);
        }

        if (logoVisible) {
            window.draw(logo);
        }

        if (StudioTextPopped) {
            window.draw(StudioText);
        }
    }

    if (showCongratulationsScreen) {
        window.draw(congratulationsSprite);
        window.draw(continueButton);
        window.draw(homeButton);
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

    if (!soundBuffer.loadFromFile("Audio/MainSong.mp3")) {
        std::cerr << "Failed to load sound file" << std::endl;
    }
    else {
        std::cout << "Sound file loaded successfully" << std::endl;
        sound.setBuffer(soundBuffer);
        sound.setLoop(true);
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
        !CrewButtonTexture.loadFromFile("Textures/CrewButton.png")) {
        std::cerr << "Could not load one or more button textures" << std::endl;
    }
    if (!meteorTexture.loadFromFile("Textures/Meteor.png")) {
        std::cerr << "Could not load meteor texture" << std::endl;
    }
    if (!secondPlanetTexture.loadFromFile("Textures/SecondPlanet.png")) {
        std::cerr << "Could not load Second Planet texture" << std::endl;
    }
    if (!congratulationsTexture.loadFromFile("Textures/Congratulations.png")) {
        std::cerr << "Could not load Congratulations texture" << std::endl;
    }
    congratulationsSprite.setTexture(congratulationsTexture);

    if (!continueButtonTexture.loadFromFile("Textures/ContinueButton.png")) {
        std::cerr << "Could not load Continue Button texture" << std::endl;
    }
    continueButton.setTexture(&continueButtonTexture);
    if (!homeButtonTexture.loadFromFile("Textures/HomeButton.png")) {
        std::cerr << "Could not load Home Button texture" << std::endl;
    }
    if (!spaceShipATexture.loadFromFile("Textures/SpaceShipA.png")) {
        std::cerr << "Could not load SpaceShipA texture" << std::endl;
    }
    if (!spaceShipBTexture.loadFromFile("Textures/SpaceShipB.png")) {
        std::cerr << "Could not load SpaceShipB texture" << std::endl;
    }
    if (!spaceShipCTexture.loadFromFile("Textures/SpaceShipC.png")) {
        std::cerr << "Could not load SpaceShipC texture" << std::endl;
    }
    if (!crewSelectionBackgroundTexture.loadFromFile("Textures/CrewSelectionBackground.jpg")) {
        std::cerr << "Could not load Crew Selection background texture" << std::endl;
    }
    if (!spaceShipTexture.loadFromFile("Textures/SpaceShipA.png")) {
        std::cerr << "Could not load SpaceShipA texture" << std::endl;
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

    spaceShipAButton.setTexture(&spaceShipATexture);
    spaceShipBButton.setTexture(&spaceShipBTexture);
    spaceShipCButton.setTexture(&spaceShipCTexture);

    float baseX = CrewButton.getPosition().x;
    float baseY = CrewButton.getPosition().y + CrewButton.getSize().y + 50;


    sf::FloatRect backgroundBounds = crewSelectionBackground.getGlobalBounds();

    float buttonWidth = 150.f;
    float buttonHeight = 250.f;
    float spacing = 20.f;

    float totalWidth = 3 * buttonWidth + 2 * spacing;

    float startX = (screenWidth - totalWidth) / 2;

    float startY = (screenHeight - buttonHeight) / 2;

    spaceShipAButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    spaceShipAButton.setPosition(startX, startY);

    spaceShipBButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    spaceShipBButton.setPosition(startX + buttonWidth + spacing, startY);

    spaceShipCButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    spaceShipCButton.setPosition(startX + 2 * (buttonWidth + spacing), startY);

    crewSelectionBackground.setTexture(crewSelectionBackgroundTexture);
    crewSelectionBackground.setPosition((screenWidth - crewSelectionBackground.getGlobalBounds().width) / 2, (screenHeight - crewSelectionBackground.getGlobalBounds().height) / 2);

    backButton.setTexture(&backButtonTexture);
    backButton.setSize(sf::Vector2f(150.f, 50.f));
    backButton.setPosition(screenWidth / 2 - backButton.getSize().x / 2, crewSelectionBackground.getPosition().y + crewSelectionBackground.getGlobalBounds().height - backButton.getSize().y - 20);

}

void GameEngine::initializeExpeditionUI() {
    expeditionBackground.setTexture(&expeditionBackgroundTexture);
    expeditionBackground.setSize(sf::Vector2f(1500.f, 800.f));
    expeditionBackground.setPosition(
        (screenWidth / 2.f) - (expeditionBackground.getSize().x / 2.f),
        (screenHeight / 2.f) - (expeditionBackground.getSize().y / 2.f)
    );

    expeditionTitleShape.setTexture(&expeditionTitleTexture);
    expeditionTitleShape.setSize(sf::Vector2f(500.f, 200.f));
    expeditionTitleShape.setPosition(screenWidth / 2.f - expeditionTitleShape.getSize().x / 2.f,
        screenHeight / 2.f - expeditionBackground.getSize().y / 2.f - 220.f);


    newExpeditionButton.setTexture(&newExpeditionButtonTexture);
    CrewButton.setTexture(&CrewButtonTexture);

    float buttonWidth = 400.f;
    float buttonHeight = 150.f;
    float spacing = 40.f;

    newExpeditionButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    CrewButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));

    float startX = screenWidth / 2.f - buttonWidth / 2.f;
    float startY = screenHeight / 2.f - (1.5f * buttonHeight + spacing);

    newExpeditionButton.setPosition(startX, startY);
    CrewButton.setPosition(startX, startY + 2 * (buttonHeight + spacing));
}

void GameEngine::initializeSpaceGame() {
    spaceShip.setTexture(&spaceShipTexture);
    spaceShip.setSize(sf::Vector2f(100.f, 150.f));
    spaceShip.setPosition(screenWidth / 2 - spaceShip.getSize().x / 2, screenHeight - spaceShip.getSize().y - 450);
    meteors.clear();
    meteorSpawnTimer = 0.0f;
    gameSessionTimer = 0.0f;
    gameEnded = false;

    // Load and set up the big planet texture (in that case this is unused for the moment!)
    bigPlanet.setTexture(&bigPlanetTexture);
    bigPlanet.setSize(sf::Vector2f(300.f, 300.f));
    bigPlanet.setPosition(screenWidth / 2 - bigPlanet.getSize().x / 2, screenHeight / 2 - bigPlanet.getSize().y / 2);

    if (!earthTexture.loadFromFile("Textures/Earth.png")) {
        std::cerr << "Could not load Earth texture" << std::endl;
    }
    earth.setTexture(&earthTexture);
    earth.setSize(sf::Vector2f(6000.f, 3000.f));
    earth.setPosition(screenWidth / 2 - earth.getSize().x / 2, screenHeight - earth.getSize().y + 2750);
    startingPhase = true;
    startingPhaseTimer = 0.0f;

    continueButton.setTexture(&continueButtonTexture);
    continueButton.setSize(sf::Vector2f(400, 200));
    continueButton.setPosition(screenWidth / 2 - continueButton.getSize().x / 2, screenHeight * 0.75);

    homeButton.setTexture(&homeButtonTexture);
    homeButton.setSize(sf::Vector2f(400, 200));
    homeButton.setPosition(screenWidth / 2 - homeButton.getSize().x / 3, continueButton.getPosition().y + continueButton.getSize().y + 10);
    spaceShip.setTexture(currentSpaceShipTexture);
}

void GameEngine::updateMeteors(float deltaTime) {
    meteorSpawnTimer += deltaTime;
    if (meteorSpawnTimer >= meteorSpawnRate) {
        sf::RectangleShape meteor(sf::Vector2f(50.f, 50.f));
        meteor.setTexture(&meteorTexture);
        meteor.setPosition(rand() % screenWidth, -50.f);
        meteors.push_back(meteor);
        meteorSpawnTimer = 0.0f;
    }
    for (auto& meteor : meteors) {
        meteor.move(0, 100 * deltaTime);
    }
    meteors.erase(std::remove_if(meteors.begin(), meteors.end(), [this](const sf::RectangleShape& meteor) {
        return meteor.getPosition().y > screenHeight;
        }), meteors.end());
}

void GameEngine::checkCollisions() {
    for (auto& meteor : meteors) {
        if (spaceShip.getGlobalBounds().intersects(meteor.getGlobalBounds())) {
            spaceGameActive = false;
            expeditionScreenActive = true;
            break;
        }
    }
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

    // Define and tweak the values for the introduction screen!(I presonally don't recommend you guys to touch this part!)
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

void GameEngine::resetGameState() {
    // Reset game timers and otehr stuff
    gameSessionTimer = 0.0f;
    startingPhaseTimer = 0.0f;
    gameEnded = false;
    spaceshipLanded = false;
    landingAnimationStarted = false;
    showCongratulationsScreen = false;
    startingPhase = true;

    // Reset spaceship and meteors (Don't need an explanation why...)
    spaceShip.setPosition(screenWidth / 2 - spaceShip.getSize().x / 2, screenHeight / 4);
    meteors.clear();


    // Reset UI elements if necessary (In most of the cases it's needed!)
    mainMenuActive = false;
    expeditionScreenActive = true;
}
void GameEngine::handleContinueButtonClick() {
    showCongratulationsScreen = false;
    expeditionScreenActive = true;
    resetGameState();

}

void GameEngine::handleHomeButtonClick() {
    showCongratulationsScreen = false;
    expeditionScreenActive = true;
    spaceGameActive = false;

}

void GameEngine::initializeCrewMembers() {

    float optionY = popupBackground.getPosition().y + 20;
    for (const auto& role : roles) {
        sf::Text option(role, font, 24);
        option.setPosition(popupBackground.getPosition().x + 20, optionY);
        crewOptions.push_back(option);
        optionY += 30;
    }
}