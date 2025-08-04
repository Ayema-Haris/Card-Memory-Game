#include "Card.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

CardNode::CardNode(int id, const string& fileName, string& name) : next(nullptr), ID(id) {
    initTexture(fileName, name);
    initSprite();
    initVariable();
}

void CardNode::initTexture(const string& fileName, const string name) {
    CardTexture.loadFromFile(fileName);
    CoveredTexture.loadFromFile(name);
}

void CardNode::initSprite() {
    CardSprite.setTexture(CardTexture);
    CardSprite.setScale(1.0f, 1.0f);
    CoveredSprite.setTexture(CoveredTexture);
    CoveredSprite.setScale(1.0f, 1.0f);
}

void CardNode::initVariable() {
    revealed = false;
    CanBeClicked = true;
}

Cards::Cards() : size(0), start(46), width(0), spacing(0), head(nullptr) {}

void Cards::Add_Card(int id, string img, string img2) {
    CardNode* node = new CardNode(id, img, img2);
    if (head == nullptr) {
        head = node;
    }
    else {
        CardNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = node;
    }
}

void Cards::Delete_Card(int id) {
    CardNode* curr = head;
    CardNode* prev = nullptr;
    while (curr != nullptr) {
        if (curr->ID == id) {
            if (prev != nullptr) {
                prev->next = curr->next;
            }
            else {
                head = curr->next;
            }
            CardNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
        else {
            prev = curr;
            curr = curr->next;
        }
    }
}

CardNode* Cards::GetNodeatIndex(int i) {
    int temp = 1;
    CardNode* current = head;
    while (temp != i && current->next != nullptr) {
        current = current->next;
        temp++;
    }
    return current;
}

int Cards::get_Size() {
    size = 0;
    CardNode* current = head;
    while (current != nullptr) {
        current = current->next;
        size++;
    }
    return size;
}

void Cards::Shuffle() {
    srand(time(0));
    int j = 0;
    CardNode* current = head;
    size = get_Size();
    for (int i = size; i > 0; i--) {
        j = rand() % (i + 1);
        CardNode* nodeI = GetNodeatIndex(i);
        CardNode* nodeJ = GetNodeatIndex(j);
        swap(nodeI->ID, nodeJ->ID);
        swap(nodeI->revealed, nodeJ->revealed);
        swap(nodeI->CanBeClicked, nodeJ->CanBeClicked);
        swap(nodeI->CardTexture, nodeJ->CardTexture);
        nodeI->CardSprite.setTexture(nodeI->CardTexture);
        nodeJ->CardSprite.setTexture(nodeJ->CardTexture);
    }
}

void Cards::Spacing() {
    CardNode* curr = head;
    int ctr = 1;
    while (curr != nullptr && ctr < 9) {
        if (ctr < 5) {
            newPos = start + width + spacing;
            curr->CardSprite.setPosition(newPos, 140);
            curr->CoveredSprite.setPosition(newPos, 140);
            start = newPos;
            width = 140;
            spacing = 45;
            if (ctr == 4) {
                start = 46;
                width = 0;
                spacing = 0;
            }
        }
        else {
            newPos = start + width + spacing;
            curr->CardSprite.setPosition(newPos, 320);
            curr->CoveredSprite.setPosition(newPos, 320);
            start = newPos;
            width = 140;
            spacing = 45;
        }
        curr = curr->next;
        ctr++;
    }
}

CardNode* Cards::getHead() {
    return head;
}
