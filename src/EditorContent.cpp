#include "EditorContent.h"

EditorContent::EditorContent(TextDocument &textDocument) : document(textDocument)
{
    this->cursor = Cursor(0, 0);
}

bool EditorContent::moveCursorLeft(bool updateActiveSelections)
{
    bool moved = (this->cursor.getLineN() != 0) || (this->cursor.getLineN() == 0 && (this->cursor.getCharN() > 0));

    if (this->cursor.getCharN() == 0)
    {
        int newCursor = std::max(this->cursor.getLineN() - 1, 0);
        int newChar = 0;
        if (this->cursor.getLineN() != 0)
        {
           newCursor = this->document.charsInLine(newCursor);
        }
        this->cursor.setPosition(newCursor, newChar, true);
    }
    else
    {
        this->cursor.moveLeft(true);
    }

    return moved;
}

void EditorContent::moveCursorRight(bool updateActiveSelections)
{
    int charsInLine = this->document.charsInLine(this->cursor.getLineN());
    if (this->cursor.getCharN() >= charsInLine)
    {
        int newCursorLine = std::min(this->cursor.getLineN() + 1, this->document.getLineCount() - 1);

        if (newCursorLine != this->cursor.getLineN())
        {
            this->cursor.setPosition(newCursorLine, 0, true);
        }
    }
    else
    {
        this->cursor.moveRight(true);
    }
}

void EditorContent::moveCursorUp(bool updateActiveSelections)
{
    if (this->cursor.getLineN() > 0)
    {
        int charsInPreviousLine = this->document.charsInLine(this->cursor.getLineN() - 1);
        int currentCharPos = this->cursor.getCharN();

        if (currentCharPos <= charsInPreviousLine && this->cursor.getMaxCharNReached() <= charsInPreviousLine)
        {
            this->cursor.moveUpToMaxCharN();
        }
        else
        {
            this->cursor.setPosition(this->cursor.getLineN() - 1, charsInPreviousLine);
        }
    }
}

void EditorContent::moveCursorDown(bool updateActiveSelections)
{
    if (this->cursor.getLineN() < this->document.getLineCount() - 1) {
        int charsInNextLine = this->document.charsInLine(this->cursor.getLineN() + 1);
        int currentCharPos = this->cursor.getCharN();

        if (currentCharPos <= charsInNextLine && this->cursor.getMaxCharNReached() <= charsInNextLine) {
            this->cursor.moveDownToMaxCharN();
        } else {
            this->cursor.setPosition(this->cursor.getLineN() + 1, charsInNextLine);
        }
    }
}

void EditorContent::addTextInCursorPos(sf::String text)
{
    int textSize = text.getSize();
    int lineN = this->cursor.getLineN();
    int charN = this->cursor.getCharN();

    this->document.addTextToPos(text, lineN, charN);
    for (int i = 0; i < textSize; i++) {
        this->moveCursorRight();
    }
}

void EditorContent::deleteTextBeforeCursorPos(int amount) {
    int actuallyMoved = 0;
    for (int i = 0; i < amount; i++) {
        bool moved = this->moveCursorLeft();
        actuallyMoved += moved ? 1 : 0;
    }
    this->deleteTextAfterCursorPos(actuallyMoved);
}

void EditorContent::deleteTextAfterCursorPos(int amount) {
    int newLineN = this->cursor.getLineN();
    int newCharN = this->cursor.getCharN();
    this->document.removeTextFromPos(amount, newLineN, newCharN);
}

int EditorContent::linesCount()
{
    return this->document.getLineCount();
}

int EditorContent::colsInLine(int line)
{
    return this->document.charsInLine(line);
}

sf::String EditorContent::getLine(int line)
{
    return this->document.getLine(line);
}

sf::String EditorContent::getCursorLine()
{
    return this->getLine(cursor.getLineN());
}

void EditorContent::resetCursor(int line, int column)
{
    this->cursor.setPosition(line, column);
    this->cursor.setMaxCharNReached(column);
}

std::pair<int, int> EditorContent::cursorPosition()
{
    int lineN = this->cursor.getLineN();
    int charN = this->cursor.getCharN();
    int column = this->getColumnFromCharN(lineN, charN);

    return std::pair<int, int>(lineN, column);
}

int EditorContent::getCharIndexOfColumn(int lineN, int column)
{
    sf::String line = this->getLine(lineN);
    int len = this->colsInLine(lineN);
    int currentCol = 0;
    for (int charN = 0; charN < len; charN++) {

        if (column <= currentCol) {
            return charN;
        }

        if (line[charN] == '\t') {
            currentCol += 4;
        } else {
            currentCol++;
        }
    }
    return len == 0 ? 0 : len - 1;
}

int EditorContent::getColumnFromCharN(int lineN, int charN)
{
    sf::String line = this->getLine(lineN);
    int currentCol = 0;
    for (int charNact = 0; charNact < charN; charNact++) {
        if (line[charNact] == '\t') {
            currentCol += 4;
        } else {
            currentCol++;
        }
    }

    return currentCol;
}

void EditorContent::handleSelectionOnCursorMovement(bool updateActiveSelections)
{
}
