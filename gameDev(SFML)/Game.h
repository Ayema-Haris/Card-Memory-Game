#pragma once
#include "Card.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class Game {
    RenderWindow* window;
    Event e;

    Sprite BackSprite, ExitSprite, PlayAgainSprite, EndSprite, ScoreSprite, BackgroundSprite;
    Texture BackTexture, ExitTexture, PlayAgainTexture, EndTexture, ScoreTexture, BackgroundTexture;

    Text ScoreText;
    Font ScoreFont;

    SoundBuffer CardClickBuffer, MatchBuffer, NoMatchBuffer, StartSoundBuffer, EndGameBuffer;
    Sound CardClickSound, MatchSound, NoMatchSound, StartSound, EndGameSound;

    CardNode* currCard;
    CardNode* Card1;
    CardNode* Card2;
    Cards deck;

    bool check, MatchFound, CardDeleted, InGame;
    int ID1, ID2, score;

public:
    Game(RenderWindow& Sharedwindow);
    void GameStart();

private:
    void initCards();
    void initVariable();
    void initAudio();
    void initSprite();
    void initTexture();
    void initText();

    void HandleMouseEvents();
    void Check_Match(CardNode* secondCard);
    void NoMatch_found();
    void Run();
    void Update();
    void ProcessEvents();
    void Render();
    void CleanUp();
};

