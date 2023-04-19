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



using std::string;
using std::vector;

class Document {
   public:
    bool init(const string &filename);
    bool saveFile(const string &filename);
    bool hasChanged() const;

    sf::String getLine(int lineNumber) const;
    int charsInLine(int line) const;
    int getLineCount() const;

    void addTextToPos(sf::String& text, int line, int charN);
    void removeTextFromPos(int amount, int lineN, int charN);
    sf::String getTextFromPos(int amount, int line, int charN);

    int getBufferPos(int line, int charN);

    sf::String toUtf32(const std::string &inString);

    bool initLineBuffer();

    bool documentHasChanged;
   private:
    sf::String buffer;
    int length;
    vector<int> lineBuffer;

    
};

#endif
