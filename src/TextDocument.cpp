#include "TextDocument.h"


bool TextDocument::init(string &filename) {
    std::ifstream inputFile(filename); 
    if (!inputFile.is_open()) { 
        std::cerr << "Error: Could not open file " << filename << std::endl; 
        return false; 
    }

    std::stringstream inputStream; 
    inputStream << inputFile.rdbuf(); 

    this->buffer = this->toUtf32(inputStream.str()); 
    this->length = buffer.getSize(); 
    inputFile.close();
    this->initLinebuffer();
    return true; 
}

bool TextDocument::saveFile(string &filename)
{   
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    std::stringstream savedFile; 
    for (sf::Uint32 ch : this->buffer) {
        savedFile << ch;
    };

    outputFile << savedFile.str(); 

    outputFile.close();

    this->documentHasChanged = false;
    return true;

}

bool TextDocument::hasChanged()
{
    return this->documentHasChanged;
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

int TextDocument::charAmountContained(int startLineN, int startCharN, int endLineN, int endCharN)
{
    return 0;
}

bool TextDocument::initLinebuffer()
{
    int lineStart = 0;
    int bufferSize = this->buffer.getSize();

    this->lineBuffer.clear();
    this->lineBuffer.reserve(bufferSize / 40); // reserve space for about 40 lines
    this->lineBuffer.push_back(lineStart);

    const sf::Uint32 *bufferPtr = this->buffer.getData();

    for (int i = 0; i < bufferSize; i++, bufferPtr++)
    {
        if (*bufferPtr == '\n' || *bufferPtr == 13)
        {
            lineStart = i + 1;
            this->lineBuffer.push_back(lineStart);
        }
    }

    return true;
}


int TextDocument::getBufferPos(int line, int charN)
{
    return 0;
}


sf::String TextDocument::toUtf32(const std::string &inString)
{
    sf::String outString = "";

    // Copy the input string into a local std::string object
    std::string localString = inString;

    // Obtain a pointer to the first character in the string
    const char* ptr = localString.c_str();

    // Decode characters until the null terminator is reached
    while (*ptr != '\0') {
        sf::Uint32 out;
        ptr = sf::Utf8::decode(ptr, localString.c_str() + localString.length(), out);
        outString += out;
    }

    return outString;
}


