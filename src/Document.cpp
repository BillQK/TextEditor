#include "Document.h"

// g++ -Wall -Wextra -pedantic --std=c++17 -o test TextDocumentTest.cpp Document.cpp 
// -Wall -I/usr/local/lib/SFML-2.5.1/include -L/usr/local/lib/SFML-2.5.1/lib -lsfml-system -lsfml-graphics -MMD

bool Document::init(const std::string &filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    std::stringstream inputStream;
    inputStream << inputFile.rdbuf();

    this->buffer = inputStream.str();
    this->length = buffer.getSize();
    inputFile.close();
    initLineBuffer();
    return true;
}

bool Document::saveFile(const std::string &filename) {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    std::stringstream savedFile;

    for (sf::Uint32 ch : this->buffer) {
        std::string utf8_char;
        sf::Utf8::encode(ch, std::back_inserter(utf8_char));
        savedFile << utf8_char;
    }

    outputFile << savedFile.str();
    outputFile.close();

    this->documentHasChanged = false;
    return true;
}

bool Document::hasChanged() const {
    return this->documentHasChanged;
}

sf::String Document::getLine(int lineNumber) const {
    int lastLine = static_cast<int>(this->lineBuffer.size()) - 1;

    if (lineNumber < 0 || lineNumber > lastLine) {
        std::cerr << "lineNumber " << lineNumber << " is not a valid number line. "
                  << "Max is: " << this->lineBuffer.size() - 1 << std::endl;
        return "";
    }

    int bufferStart = this->lineBuffer[lineNumber];
    int nextBufferStart = this->lineBuffer[lineNumber + 1];
 

    // Look for end of line 
    while (nextBufferStart > bufferStart &&
           (this->buffer[nextBufferStart - 1] == '\n' ||
            this->buffer[nextBufferStart - 1] == '\r')) {
        nextBufferStart--;
    }

    int cantidad = nextBufferStart - bufferStart;

    return this->buffer.substring(bufferStart, cantidad);
}


int Document::charsInLine(int line) const {
    int bufferSize = static_cast<int>(lineBuffer.size());

    if (line == bufferSize - 1) {
        return static_cast<int>(buffer.getSize()) - lineBuffer[lineBuffer.size() - 1];
    } else {
        return lineBuffer[line + 1] - lineBuffer[line] - 1;
    }
}

int Document::getLineCount() const {
    return static_cast<int>(lineBuffer.size()); 
}

void Document::addTextToPos(sf::String& text, int line, int charN){
    documentHasChanged = true;

    int textSize = static_cast<int>(text.getSize());
    int bufferInsertPos = getBufferPos(line, charN);
    buffer.insert(bufferInsertPos, text);

    int lineAmount = static_cast<int>(lineBuffer.size());
    for (int l = line + 1; l < lineAmount; l++) {
        lineBuffer[l] += textSize;
    }

    for (int i = 0; i < textSize; i++) {
        if (text[i] == '\n' || text[i] == 13) {
            int newLineStart = bufferInsertPos + i + 1;

            lineBuffer.insert(
                std::lower_bound(lineBuffer.begin(), lineBuffer.end(), newLineStart),
                newLineStart);
        }
    }
}

void Document::removeTextFromPos(int amount, int lineN, int charN) {
    documentHasChanged = true;

    int bufferStartPos = getBufferPos(lineN, charN);
    buffer.erase(bufferStartPos, amount);

    initLineBuffer();
}

sf::String Document::getTextFromPos(int amount, int line, int charN) {
    int bufferPos = getBufferPos(line, charN);
    return buffer.substring(bufferPos, amount);
}

bool Document::initLineBuffer() {
    int lineStart = 0;
    int bufferSize = static_cast<int>(buffer.getSize());

    lineBuffer.clear();
    lineBuffer.reserve(bufferSize / 40); // reserve space for about 40 lines
    lineBuffer.push_back(lineStart);

    const sf::Uint32 *bufferPtr = buffer.getData();

    for (int i = 0; i < bufferSize; i++, bufferPtr++) {
        if (*bufferPtr == '\n' || *bufferPtr == 13) {
            lineStart = i + 1;
            lineBuffer.push_back(lineStart);
        }
    }

    return true;
}

int Document::getBufferPos(int line, int charN) {
    if (line >= static_cast<int>(lineBuffer.size())) {
        std::cerr << "\nCan't get buffer pos of: " << line << "\n";
        std::cerr << "Buffer last line is: " << lineBuffer.size() - 1 << "\n\n";
    }
    return lineBuffer[line] + charN;
}


sf::String Document::toUtf32(const std::string &inString) {
    sf::String outString;

    auto iterEnd = inString.cend();
    for (auto iter = inString.cbegin(); iter != iterEnd;) {
        sf::Uint32 out;
        iter = sf::Utf8::decode(iter, iterEnd, out);
        outString += out;
    }

    return outString;
}


