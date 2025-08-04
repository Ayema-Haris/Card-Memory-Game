#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class CardNode {
public:
    CardNode* next;
    int ID;
    bool revealed;
    bool CanBeClicked;

    Sprite CardSprite;
    Sprite CoveredSprite;
    Texture CardTexture;
    Texture CoveredTexture;

    CardNode(int id, const string& fileName, string& coveredFile);
    void initTexture(const string& fileName, const string coveredFile);
    void initSprite();
    void initVariable();
};

class Cards {
    float width, spacing, newPos, start;
    int size;
    CardNode* head;

public:
    Cards();
    void Add_Card(int id, string img, string img2);
    void Delete_Card(int id);
    CardNode* GetNodeatIndex(int i);
    int get_Size();
    void Shuffle();
    void Spacing();
    CardNode* getHead();
};
