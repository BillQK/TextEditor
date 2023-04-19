#include "Cursor.h"

// Default constructor initializes cursor at position (0, 0)
Cursor::Cursor() : lineN(0), charN(0), maxCharNReached(0) {}

// Constructor initializes cursor at a given line and character position
Cursor::Cursor(int lineN, int charN) : lineN(lineN), charN(charN), maxCharNReached(0) {}

// Move cursor up by one line
void Cursor::moveUp()
{
    updatePos(lineN - 1, charN);
}

// Move cursor down by one line
void Cursor::moveDown()
{
    updatePos(lineN + 1, charN);
}

// Move cursor left by one character
void Cursor::moveLeft(bool updateMaxChar)
{
    // Update maxCharNReached if specified
    if (updateMaxChar)
    {
        setMaxCharNReached(charN - 1);
    }

    updatePos(lineN, charN - 1);
}

// Move cursor right by one character
void Cursor::moveRight(bool updateMaxChar)
{
    // Update maxCharNReached if specified
    if (updateMaxChar)
    {
        setMaxCharNReached(charN + 1);
    }

    updatePos(lineN, charN + 1);
}

// Move cursor to beginning of next line
void Cursor::nextLine()
{
    charN = 0;
    moveDown();
}

// Get current line number of cursor
int Cursor::getLineN()
{
    return lineN;
}

// Get current character number of cursor
int Cursor::getCharN()
{
    return charN;
}
// Set cursor position to given line and character position
void Cursor::setPosition(int lineN, int charN, bool updateMaxChar)
{
    updatePos(lineN, charN);
    // Update maxCharNReached if specified
    if (updateMaxChar)
    {
        setMaxCharNReached(charN);
    }
}

// Move cursor down to maximum character position of next line
void Cursor::moveDownToMaxCharN()
{
    updatePos(lineN + 1, maxCharNReached);
}

// Move cursor up to maximum character position of previous line
void Cursor::moveUpToMaxCharN()
{
    updatePos(lineN - 1, maxCharNReached);
}

// Set maximum character position reached by cursor
void Cursor::setMaxCharNReached(int charN)
{
    maxCharNReached = charN;
}

// Get maximum character position reached by cursor
int Cursor::getMaxCharNReached()
{
    return maxCharNReached;
}

// Update cursor position to given line and character position
void Cursor::updatePos(int lineN, int charN)
{
    this->lineN = lineN;
    this->charN = charN;
}