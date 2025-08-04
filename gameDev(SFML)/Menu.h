#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"

using namespace sf;

class Menu {
public:
    RenderWindow* window;
    Event e;

    Sprite StartSprite, BackgroundSprite, ExitSprite;
    Texture StartTexture, BackgroundTexture, ExitTexture;

    Music backgroundMusic;
    Sound StartSound;
    SoundBuffer StartSoundBuffer;

    Menu();
    void Run();
    void HandleMouseEvents();
    void ProcessEvents();
    void Render();

private:
    void initWindow();
    void initTexture();
    void initSprite();
    void initAudio();
};
