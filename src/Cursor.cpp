#include "Cursor.h"

Cursor::Cursor() : Cursor(0, 0) {}

Cursor::Cursor(int lineN, int charN) {
    maxCharNReached = 0;
    updatePos(lineN, charN);
}

void Cursor::moveUp() {
    updatePos(lineN - 1, charN);
}

void Cursor::moveDown() {
    updatePos(lineN + 1, charN);
}

void Cursor::moveLeft(bool updateMaxChar) {
    if (updateMaxChar) {
        setMaxCharNReached(charN - 1);
    }

    updatePos(lineN, charN - 1);
}

void Cursor::moveRight(bool updateMaxChar) {
    if (updateMaxChar) {
        setMaxCharNReached(charN);
    }

    updatePos(lineN, charN + 1);
}

void Cursor::nextLine() {
    charN = 0;
    moveDown();
}

int Cursor::getLineN() {
    return lineN;
}

int Cursor::getCharN() {
    return charN;
}

void Cursor::setPosition(int lineN, int charN, bool updateMaxChar) {
    updatePos(lineN, charN);
    
    if (updateMaxChar) {
        setMaxCharNReached(charN);
    }
}

void Cursor::moveDownToMaxCharN() {
    updatePos(lineN + 1, maxCharNReached);
}

void Cursor::moveUpToMaxCharN() {
    updatePos(lineN - 1, maxCharNReached);
}

void Cursor::setMaxCharNReached(int charN) {
    maxCharNReached = charN;
}

int Cursor::getMaxCharNReached() {
    return maxCharNReached;
}

void Cursor::updatePos(int posY, int posX) {
    lineN = posY;
    charN = posX;
}