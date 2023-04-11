#include "TextDocument.h"


bool TextDocument::init(string &filename) {
    
}

bool TextDocument::saveFile(string &filename)
{
    return false;
}

bool TextDocument::hasChanged()
{
    return false;
}

sf::String TextDocument::getLine(int lineNumber)
{
    return sf::String();
}

int TextDocument::charsInLine(int line) const
{
    return 0;
}

int TextDocument::getLineCount() const
{
    return 0;
}

void TextDocument::addTextToPos(sf::String text, int line, int charN)
{
}

void TextDocument::removeTextFromPos(int amount, int line, int charN)
{
}

sf::String TextDocument::getTextFromPos(int amount, int line, int charN)
{
    return sf::String();
}

void TextDocument::swapLines(int lineA, int lineB)
{
}

int TextDocument::charAmountContained(int startLineN, int startCharN, int endLineN, int endCharN)
{
    return 0;
}

bool TextDocument::initLinebuffer()
{
    return false;
}

int TextDocument::getBufferPos(int line, int charN)
{
    return 0;
}


sf::String TextDocument::toUtf32(const std::string &inString)
{
    return sf::String();
}
