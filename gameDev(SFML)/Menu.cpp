#include "Menu.h"

Menu::Menu() {
    initWindow();
    initTexture();
    initSprite();
    initAudio();
}

void Menu::initWindow() {
    window = new RenderWindow(VideoMode(800, 520), "Menu");
    window->setFramerateLimit(60);
}

void Menu::initTexture() {
    BackgroundTexture.loadFromFile("assets/Startbackground.png");
    StartTexture.loadFromFile("assets/start.png");
    ExitTexture.loadFromFile("assets/exit.png");
}

void Menu::initSprite() {
    StartSprite.setTexture(StartTexture);
    StartSprite.setPosition(311, 370);

    BackgroundSprite.setTexture(BackgroundTexture);
    BackgroundSprite.setPosition(0, 0);

    ExitSprite.setTexture(ExitTexture);
    ExitSprite.setPosition(440, 370);
}

void Menu::initAudio() {
    backgroundMusic.openFromFile("assets/music.WAV");
    backgroundMusic.setLoop(true);
    StartSoundBuffer.loadFromFile("assets/start.WAV");
    StartSound.setBuffer(StartSoundBuffer);
}

void Menu::HandleMouseEvents() {
    if (e.type == Event::MouseButtonPressed && e.key.code == Mouse::Left) {
        Vector2f mousePos = (Vector2f)Mouse::getPosition(*window);
        if (StartSprite.getGlobalBounds().contains(mousePos)) {
            StartSound.play();
            Game g(*window);
            g.GameStart();
            StartSound.play();
        }
        else if (ExitSprite.getGlobalBounds().contains(mousePos)) {
            StartSound.play();
            window->close();
        }
    }
}

void Menu::Run() {
    while (window->isOpen()) {
        ProcessEvents();
        Render();
    }
}

void Menu::ProcessEvents() {
    while (window->pollEvent(e)) {
        if (e.type == Event::Closed) {
            window->close();
        }
        HandleMouseEvents();
    }
}

void Menu::Render() {
    window->clear(Color::White);
    window->draw(BackgroundSprite);
    window->draw(StartSprite);
    window->draw(ExitSprite);
    window->display();
}
