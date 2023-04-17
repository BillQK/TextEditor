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

// bool TextDocument::saveFile(string &filename)
// {   
//     std::ofstream outputFile(filename);
//     if (!outputFile.is_open()) {
//         std::cerr << "Error opening file: " << filename << std::endl;
//         return false;
//     }

//     std::stringstream savedFile; 
//     for (sf::Uint32 ch : this->buffer) {
//         savedFile << ch;
//     };

//     outputFile << savedFile.str(); 

//     outputFile.close();

//     this->documentHasChanged = false;
//     return true;

// }

// bool TextDocument::hasChanged()
// {
//     return this->documentHasChanged;
// }

// sf::String TextDocument::getLine(int lineNumber)
// {
//     int lastLine = this->lineBuffer.size() - 1;

//     if (lineNumber < 0 || lineNumber > lastLine)
//     {
//         std::cerr << "lineNumber " << lineNumber << " is not a valid number line. "
//                   << "Max is: " << this->lineBuffer.size() - 1 << std::endl;
//         return "";
//     }

//     if (lineNumber == lastLine)
//     {
//         return this->buffer.substring(this->lineBuffer[lineNumber]);
//     }
//     else
//     {
//         int bufferStart = this->lineBuffer[lineNumber];
//         int nextBufferStart = this->lineBuffer[lineNumber + 1];
//         int cantidad = nextBufferStart - bufferStart - 1;

//         return this->buffer.substring(bufferStart, cantidad);
//     }
// }

// int TextDocument::charsInLine(int line) const
// {
//     int bufferSize = this->lineBuffer.size();

//     if (line == bufferSize - 1)
//     {
//         return this->buffer.getSize() - this->lineBuffer[this->lineBuffer.size() - 1];
//     }
//     else
//     {
//         return this->lineBuffer[line + 1] - this->lineBuffer[line] - 1;
//     }
// }

// int TextDocument::getLineCount() const
// {
//      return (int)this->lineBuffer.size();
// }

// void TextDocument::addTextToPos(sf::String text, int line, int charN)
// {
//     this->documentHasChanged = true;

//     int textSize = text.getSize();
//     int bufferInsertPos = this->getBufferPos(line, charN);
//     this->buffer.insert(bufferInsertPos, text);

//     int lineAmount = this->lineBuffer.size();
//     for (int l = line + 1; l < lineAmount; l++)
//     {
//         this->lineBuffer[l] += textSize;
//     }

//     for (int i = 0; i < (int)text.getSize(); i++)
//     {
//         if (text[i] == '\n' || text[i] == 13)
//         {                                               
//             int newLineStart = bufferInsertPos + i + 1; 

//             this->lineBuffer.insert(
//                 std::lower_bound(this->lineBuffer.begin(), this->lineBuffer.end(), newLineStart),
//                 newLineStart);
//         }
//     }
// }

// void TextDocument::removeTextFromPos(int amount, int lineN, int charN)
// {
//     this->documentHasChanged = true;

//     int bufferStartPos = this->getBufferPos(lineN, charN);
//     this->buffer.erase(bufferStartPos, amount);

//     this->initLinebuffer();
// }

// sf::String TextDocument::getTextFromPos(int amount, int line, int charN)
// {
//     int bufferPos = this->getBufferPos(line, charN);
//     return this->buffer.substring(bufferPos, amount);
// }

// int TextDocument::charAmountContained(int startLineN, int startCharN, int endLineN, int endCharN)
// {
//     return this->getBufferPos(endLineN, endCharN) - this->getBufferPos(startLineN, startCharN) + 1;
// }

// bool TextDocument::initLinebuffer()
// {
//     int lineStart = 0;
//     int bufferSize = this->buffer.getSize();

//     this->lineBuffer.clear();
//     this->lineBuffer.reserve(bufferSize / 40); // reserve space for about 40 lines
//     this->lineBuffer.push_back(lineStart);

//     const sf::Uint32 *bufferPtr = this->buffer.getData();

//     for (int i = 0; i < bufferSize; i++, bufferPtr++)
//     {
//         if (*bufferPtr == '\n' || *bufferPtr == 13)
//         {
//             lineStart = i + 1;
//             this->lineBuffer.push_back(lineStart);
//         }
//     }

//     return true;
// }


// int TextDocument::getBufferPos(int line, int charN)
// {
//     if (line >= (int)this->lineBuffer.size())
//     {
//         std::cerr << "\nCan't get buffer pos of: " << line << "\n";
//         std::cerr << "Buffer last line is: " << this->lineBuffer.size() - 1 << "\n\n";
//     }
//     return this->lineBuffer[line] + charN;
// }


// sf::String TextDocument::toUtf32(const std::string &inString)
// {
//    sf::String outString = "";
//     auto iterEnd = inString.cend();

//     for (auto iter = inString.cbegin(); iter != iterEnd;)
//     {
//         sf::Uint32 out;
//         iter = sf::Utf8::decode(iter, iterEnd, out);
//         outString += out;
//     }

//     return outString;
// }


