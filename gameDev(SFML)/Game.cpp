#include "Game.h"
#include <iostream>

Game::Game(RenderWindow& Sharedwindow) : window(&Sharedwindow) {
    initCards();
    initVariable();
    initTexture();
    initSprite();
    initText();
    initAudio();
}

void Game::initCards() {
    currCard = deck.getHead();
    Card1 = nullptr;
    Card2 = nullptr;
}

void Game::initVariable() {
    check = false;
    MatchFound = false;
    CardDeleted = false;
    InGame = false;
    score = 0;
    ID1 = 0;
    ID2 = 0;
}

void Game::initAudio() {
    CardClickBuffer.loadFromFile("assets/click.WAV");
    MatchBuffer.loadFromFile("assets/win.WAV");
    NoMatchBuffer.loadFromFile("assets/lose.WAV");
    StartSoundBuffer.loadFromFile("assets/start.WAV");
    EndGameBuffer.loadFromFile("assets/end.WAV");

    CardClickSound.setBuffer(CardClickBuffer);
    MatchSound.setBuffer(MatchBuffer);
    NoMatchSound.setBuffer(NoMatchBuffer);
    StartSound.setBuffer(StartSoundBuffer);
    EndGameSound.setBuffer(EndGameBuffer);
}

void Game::initSprite() {
    BackSprite.setTexture(BackTexture);
    BackSprite.setPosition(58, 37);

    ExitSprite.setTexture(ExitTexture);
    ExitSprite.setPosition(474, 394);

    PlayAgainSprite.setTexture(PlayAgainTexture);
    PlayAgainSprite.setPosition(290, 394);

    EndSprite.setTexture(EndTexture);
    EndSprite.setPosition(0, 0);

    ScoreSprite.setTexture(ScoreTexture);
    ScoreSprite.setPosition(364, 336);
    BackgroundSprite.setTexture(BackgroundTexture);
    BackgroundSprite.setPosition(0, 0);
}

void Game::initTexture() {
    BackTexture.loadFromFile("assets/back.png");
    ExitTexture.loadFromFile("assets/exit.png");
    PlayAgainTexture.loadFromFile("assets/PlayAgain.png");
    EndTexture.loadFromFile("assets/Endbackground.png");
    BackgroundTexture.loadFromFile("assets/background.png");
    ScoreTexture.loadFromFile("assets/score.png");
}

void Game::initText() {
    ScoreFont.loadFromFile("assets/font.ttf");
    ScoreText.setFont(ScoreFont);
    ScoreText.setCharacterSize(20);
    ScoreText.setFillColor(Color(255, 100, 0));
    ScoreText.setPosition(560, 46);
    ScoreText.setString(std::to_string(score));
}

void Game::HandleMouseEvents() {
    if (e.type == Event::MouseButtonPressed && e.key.code == Mouse::Left) {
        Vector2f mousePos = (Vector2f)Mouse::getPosition(*window);

        if (BackSprite.getGlobalBounds().contains(mousePos)) {
            StartSound.play();
            InGame = false;
            return;
        }

        if (deck.getHead() == nullptr) {
            EndGameSound.play();

            if (ExitSprite.getGlobalBounds().contains(mousePos)) {
                StartSound.play();
                window->close();
            }

            if (PlayAgainSprite.getGlobalBounds().contains(mousePos)) {
                StartSound.play();
                InGame = false;
                return;
            }
        }

        CardNode* current = deck.getHead();
        while (current != nullptr) {
            if (current->CoveredSprite.getGlobalBounds().contains(mousePos)) {
                if (!check) {
                    CardClickSound.play();
                    if (current->CanBeClicked) {
                        Card1 = current;
                        current->revealed = true;
                        check = true;
                        current->CanBeClicked = false;
                        ID1 = current->ID;
                    }
                }
                else {
                    CardClickSound.play();
                    if (current->CanBeClicked && current != Card1) {
                        Check_Match(current);
                    }
                }
                return;
            }
            current = current->next;
        }
    }
}

void Game::GameStart() {
    InGame = true;
    for (int i = 1; i < 5; i++) {
        deck.Add_Card(i, "assets/card" + std::to_string(i) + ".png", "assets/cover.png");
    }
    for (int i = 1; i < 5; i++) {
        deck.Add_Card(i, "assets/card" + std::to_string(i) + ".png", "assets/cover.png");
    }
    deck.Shuffle();
    deck.Spacing();
    Run();
}

void Game::Check_Match(CardNode* secondCard) {
    if (secondCard != nullptr) {
        secondCard->revealed = true;
        Card2 = secondCard;
        check = false;

        if (Card1 && !Card1->CanBeClicked)
            Card1->CanBeClicked = true;

        if (Card1 && Card2 && Card1 != Card2) {
            if (secondCard->ID == ID1) {
                ID2 = secondCard->ID;
                MatchFound = true;
                score++;
                CardDeleted = true;
                MatchSound.play();
            }
            else {
                NoMatchSound.play();
                MatchFound = false;
                if (score != 0) score--;
            }
        }
    }
}

void Game::NoMatch_found() {
    CardNode* curr = deck.getHead();
    while (curr != nullptr) {
        curr->revealed = false;
        curr = curr->next;
    }
}

void Game::Run() {
    while (window->isOpen() && InGame) {
        ProcessEvents();
        Update();
        Render();
    }
    if (!InGame) {
        CleanUp();
    }
}

void Game::Update() {
    // Add logic if needed
}

void Game::ProcessEvents() {
    while (window->pollEvent(e)) {
        if (e.type == Event::Closed) {
            window->close();
        }
        HandleMouseEvents();
    }
}

void Game::Render() {
    ScoreText.setString(std::to_string(score));
    window->draw(BackgroundSprite);
    window->draw(BackSprite);
    window->draw(ScoreText);

    CardNode* curr = deck.getHead();
    while (curr != nullptr) {
        window->draw(curr->revealed ? curr->CardSprite : curr->CoveredSprite);
        curr = curr->next;
    }

    if (deck.getHead() == nullptr) {
        ScoreText.setPosition(471, 335);
        window->draw(EndSprite);
        window->draw(ScoreText);
        window->draw(ExitSprite);
        window->draw(PlayAgainSprite);
        window->draw(ScoreSprite);
    }

    window->display();

    if (CardDeleted) {
        Clock clock;
        while (clock.getElapsedTime().asMilliseconds() < 500) {}
        deck.Delete_Card(ID2);
        CardDeleted = false;
    }

    if (!MatchFound) {
        Clock clock;
        while (clock.getElapsedTime().asMilliseconds() < 1000) {}
        NoMatch_found();
        MatchFound = true;
    }
}

void Game::CleanUp() {
    CardNode* curr = deck.getHead();
    while (curr != nullptr) {
        CardNode* temp = curr->next;
        delete curr;
        curr = temp;
    }
}
