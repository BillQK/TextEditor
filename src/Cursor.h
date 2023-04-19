#ifndef Cursor_H
#define Cursor_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Cursor {
public:
    // Default constructor initializes cursor at position (0, 0)
    Cursor();

    // Constructor initializes cursor at a given line and character position
    Cursor(int lineN, int charN);

    // Move cursor up by one line
    void moveUp();

    // Move cursor down by one line
    void moveDown();

    // Move cursor left by one character
    void moveLeft(bool updateMaxChar = true);

    // Move cursor right by one character
    void moveRight(bool updateMaxChar = true);

    // Move cursor to beginning of next line
    void nextLine();

    // Get current line number of cursor
    int getLineN();

    // Get current character number of cursor
    int getCharN();

    // Set cursor position to given line and character position
    void setPosition(int lineN, int charN, bool updateMaxChar = true);

    // Move cursor down to maximum character position of next line
    void moveDownToMaxCharN();

    // Move cursor up to maximum character position of previous line
    void moveUpToMaxCharN();

    // Set maximum character position reached by cursor
    void setMaxCharNReached(int charN);

    // Get maximum character position reached by cursor
    int getMaxCharNReached();

private:
    // Current line number of cursor
    int lineN;

    // Current character number of cursor
    int charN;

    // Maximum character position reached by cursor
    int maxCharNReached;

    // Update cursor position to given line and character position
    void updatePos(int lineN, int charN);
};

#endif