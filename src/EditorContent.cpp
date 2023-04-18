#include "EditorContent.h"

EditorContent::EditorContent(TextDocument &textDocument)
{
}

bool EditorContent::moveCursorLeft(bool updateActiveSelections)
{
    return false;
}

void EditorContent::moveCursorRight(bool updateActiveSelections)
{
}

void EditorContent::moveCursorUp(bool updateActiveSelections)
{
}

void EditorContent::moveCursorDown(bool updateActiveSelections)
{
}

void EditorContent::moveCursorToEnd(bool updateActiveSelections)
{
}

void EditorContent::moveCursorToStart(bool updateActiveSelections)
{
}

void EditorContent::addTextInCursorPos(sf::String text)
{
}

void EditorContent::deleteTextAfterCursorPos(int amount)
{
}

void EditorContent::deleteTextBeforeCursorPos(int amount)
{
}

int EditorContent::linesCount()
{
    return 0;
}

int EditorContent::colsInLine(int line)
{
    return 0;
}

sf::String EditorContent::getLine(int line)
{
    return sf::String();
}

sf::String EditorContent::getCursorLine()
{
    return sf::String();
}

void EditorContent::resetCursor(int line, int column)
{
}

std::pair<int, int> EditorContent::cursorPosition()
{
    return std::pair<int, int>();
}

int EditorContent::getCharIndexOfColumn(int lineN, int column)
{
    return 0;
}

int EditorContent::getColumnFromCharN(int lineN, int charN)
{
    return 0;
}

void EditorContent::handleSelectionOnCursorMovement(bool updateActiveSelections)
{
}
