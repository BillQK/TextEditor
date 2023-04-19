#ifndef Document_H
#define Document_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <locale>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>


class Document {
public:
    // Initialize document from a file
    bool init(const std::string &filename);

    // Save document to a file
    bool saveFile(const std::string &filename);

    // Check if document has changed since last save
    bool hasChanged() const;

    // Get a line of text from the document
    sf::String getLine(int lineNumber) const;

    // Get the number of characters in a line of text
    int charsInLine(int line) const;

    // Get the number of lines in the document
    int getLineCount() const;

    // Add text to a specified position in the document
    void addTextToPos(sf::String& text, int line, int charN);

    // Remove text from a specified position in the document
    void removeTextFromPos(int amount, int lineN, int charN);

    // Get text from a specified position in the document
    sf::String getTextFromPos(int amount, int line, int charN);

    // Get the buffer position of a specified position in the document
    int getBufferPos(int line, int charN);

    // Convert a string from UTF-8 to UTF-32 encoding
    sf::String toUtf32(const std::string &inString);

    // Initialize line buffer to keep track of line starts in buffer
    bool initLineBuffer();

    // Flag to indicate if the document has been modified
    bool documentHasChanged;

private:
    // Text buffer containing the document's content
    sf::String buffer;

    // Length of the text buffer
    int length;

    // Vector to keep track of the start position of each line in the buffer
    std::vector<int> lineBuffer;
};


#endif
