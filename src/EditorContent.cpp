#include "EditorContent.h"

// Constructor for EditorContent class
EditorContent::EditorContent(Document &textDocument) : document(textDocument)
{
    // Initialize cursor to position (0, 0)
    this->cursor = Cursor(0, 0);
}

// Move cursor one character to the left
bool EditorContent::moveCursorLeft(bool updateActiveSelections)
{
    bool moved = (this->cursor.getLineN() != 0) || (this->cursor.getLineN() == 0 && (this->cursor.getCharN() > 0));

    if (this->cursor.getCharN() == 0)
    {
        // Move cursor to end of previous line
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
        // Move cursor left one character
        this->cursor.moveLeft(true);
    }

    return moved;
}

// Move cursor one character to the right
void EditorContent::moveCursorRight(bool updateActiveSelections)
{
    int charsInLine = this->document.charsInLine(this->cursor.getLineN());
    if (this->cursor.getCharN() >= charsInLine)
    {
        // Move cursor to start of next line
        int newCursorLine = std::min(this->cursor.getLineN() + 1, this->document.getLineCount() - 1);

        if (newCursorLine != this->cursor.getLineN())
        {
            this->cursor.setPosition(newCursorLine, 0, true);
        }
    }
    else
    {
        // Move cursor right one character
        this->cursor.moveRight(true);
    }
}

// Move cursor up one line
void EditorContent::moveCursorUp(bool updateActiveSelections)
{
    if (this->cursor.getLineN() > 0)
    {
        // Move cursor to start of previous line
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

// Move cursor down one line
void EditorContent::moveCursorDown(bool updateActiveSelections)
{
    if (this->cursor.getLineN() < this->document.getLineCount() - 1)
    {
        // Move cursor to start of next line
        int charsInNextLine = this->document.charsInLine(this->cursor.getLineN() + 1);
        int currentCharPos = this->cursor.getCharN();

        if (currentCharPos <= charsInNextLine && this->cursor.getMaxCharNReached() <= charsInNextLine)
        {
            this->cursor.moveDownToMaxCharN();
        }
        else
        {
            this->cursor.setPosition(this->cursor.getLineN() + 1, charsInNextLine);
        }
    }
}

// Add text at cursor position
void EditorContent::addTextInCursorPos(sf::String text)
{
    int textSize = text.getSize();
    int lineN = this->cursor.getLineN();
    int charN = this->cursor.getCharN();


    this->document.addTextToPos(text, lineN, charN);

    // Move the cursor to the next position
    for (int i = 0; i < textSize; i++)
    {
        this->moveCursorRight();
    }
}

// Deletes a specified amount of characters before the current cursor position in the document
void EditorContent::deleteTextBeforeCursorPos(int amount)
{
    int actuallyMoved = 0;
    for (int i = 0; i < amount; i++)
    {
        bool moved = this->moveCursorLeft();
        actuallyMoved += moved ? 1 : 0;
    }
    // Deletes the text after the new cursor position,
    this->deleteTextAfterCursorPos(actuallyMoved);
}

// Deletes a specified amount of characters from the current cursor position in the document
void EditorContent::deleteTextAfterCursorPos(int amount)
{
    int newLineN = this->cursor.getLineN();
    int newCharN = this->cursor.getCharN();
    this->document.removeTextFromPos(amount, newLineN, newCharN);
}


// Returns the number of lines in the document
int EditorContent::linesCount()
{
    return this->document.getLineCount();
}

// Take a line number as an argument and returns the number of characters in that line
int EditorContent::colsInLine(int line)
{
    return this->document.charsInLine(line);
}

// Takes a line number as an argument and returns the string content of that line 
sf::String EditorContent::getLine(int line)
{
    return this->document.getLine(line);
}

// Returns the content of the line that the cursor is currently on 
sf::String EditorContent::getCursorLine()
{
    return this->getLine(cursor.getLineN());
}

// Sets the cursor position to a new line and column specified as arguments
void EditorContent::resetCursor(int line, int column)
{
    this->cursor.setPosition(line, column);
    this->cursor.setMaxCharNReached(column);
}

// Returns a std::pair object containing the current cursor position as a line number and column index
std::pair<int, int> EditorContent::cursorPosition()
{
    int lineN = this->cursor.getLineN();
    int charN = this->cursor.getCharN();
    int column = this->getColumnFromCharN(lineN, charN);

    return std::pair<int, int>(lineN, column);
}
// rRturns the character index of the given column index in the line
int EditorContent::getCharIndexOfColumn(int lineN, int column)
{
    sf::String line = this->getLine(lineN);
    int len = this->colsInLine(lineN);
    int currentCol = 0;
    for (int charN = 0; charN < len; charN++)
    {

        if (column <= currentCol)
        {
            return charN;
        }

        if (line[charN] == '\t')
        {
            currentCol += 4;
        }
        else
        {
            currentCol++;
        }
    }
    return len == 0 ? 0 : len - 1;
}

int EditorContent::getColumnFromCharN(int lineN, int charN)
{
    // Get the line of text at the specified line number
    sf::String line = this->getLine(lineN);

    // Initialize the column count to 0
    int currentCol = 0;

    // Iterate over each character in the line up to the specified character number
    for (int charNact = 0; charNact < charN; charNact++)
    {
        // If the character is a tab, increment the column count by 4
        if (line[charNact] == '\t')
        {
            currentCol += 4;
        }
        // Otherwise, increment the column count by 1
        else
        {
            currentCol++;
        }
    }

    // Return the final column count
    return currentCol;
}
