#include "Cursor.h"

Cursor::Cursor() : Cursor(0, 0) {};

Cursor::Cursor(int lineN, int charN)
{
    this->maxCharNReached = 0; 
    this->updatePos(lineN, charN);
}

void Cursor::moveUp()
{
    this->updatePos(this->lineN-1, this->charN); 
}

void Cursor::moveDown()
{
    this->updatePos(this->lineN-1, this->charN); 
}

void Cursor::moveLeft(bool updateMaxChar)
{   
    if (updateMaxChar) {
        this->setMaxCharNReached(this->charN-1); 
    }

    this->updatePos(this->lineN, this->charN-1);
}

void Cursor::moveRight(bool updateMaxChar)
{   
    if (updateMaxChar) {
        this->setMaxCharNReached(this->charN);
    }
    this->updatePos(this->lineN, this->charN+1);
}

void Cursor::nextLine()
{ 
    this->charN = 0; 
    this->moveDown();
}

int Cursor::getLineN()
{
    return this->lineN;
}

int Cursor::getCharN()
{
    return this->charN; 
}

void Cursor::setPosition(int lineN, int charN, bool updateMaxChar)
{
    this->updatePos(lineN, charN);
    if (updateMaxChar) {
        this->setMaxCharNReached(this->charN); 
    }
}

void Cursor::moveDownToMaxCharN()
{
    this->updatePos(this->lineN+1, this->maxCharNReached);
}

void Cursor::moveUpToMaxCharN()
{
    this->updatePos(this->lineN-1, this->maxCharNReached);
}

void Cursor::setMaxCharNReached(int charN)
{
    this->maxCharNReached = charN; 
}

int Cursor::getMaxCharNReached()
{
    return this->maxCharNReached; 
}

void Cursor::updatePos(int posY, int posX)
{
    this->lineN = posY;
    this->charN = posX;
}
