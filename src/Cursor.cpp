#include "Cursor.h"

Cursor::Cursor()
{
}

Cursor::Cursor(int lineN, int charN)
{
}

void Cursor::moveUp()
{
}

void Cursor::moveDown()
{
}

void Cursor::moveLeft(bool updateMaxChar)
{
}

void Cursor::moveRight(bool updateMaxChar)
{
}

void Cursor::moveToEnd(int charsInLine, bool updateMaxChar)
{
}

void Cursor::moveToStart(bool updateMaxChar)
{
}

    void Cursor::nextLine()
{
}

int Cursor::getLineN()
{
    return 0;
}

int Cursor::getCharN()
{
    return 0;
}

void Cursor::setPosition(int lineN, int charN, bool updateMaxChar)
{
}

void Cursor::moveDownToMaxCharN()
{
}

void Cursor::moveUpToMaxCharN()
{
}

void Cursor::setMaxCharNReached(int charN)
{
}

int Cursor::getMaxCharNReached()
{
    return 0;
}

void Cursor::updatePos(int posY, int posX)
{
}
