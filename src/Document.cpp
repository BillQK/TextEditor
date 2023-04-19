#include "Document.h"

// Initialize the document by loading a file
bool Document::init(const std::string &filename)
{
    // Open the input file
    std::ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    // Read the input file into a stringstream
    std::stringstream inputStream;
    inputStream << inputFile.rdbuf();

    // Load the contents of the input file into the document buffer
    this->buffer = inputStream.str();
    this->length = buffer.getSize();
    inputFile.close();
    initLineBuffer();
    return true;
}

// Save the contents of the document to a file
bool Document::saveFile(const std::string &filename)
{
    // Open the output file
    std::ofstream outputFile(filename);
    if (!outputFile.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    // Convert the document buffer from UTF-32 to UTF-8 and write it to the output file
    std::stringstream savedFile;
    for (sf::Uint32 ch : this->buffer)
    {
        std::string utf8_char;
        sf::Utf8::encode(ch, std::back_inserter(utf8_char));
        savedFile << utf8_char;
    }

    outputFile << savedFile.str();
    outputFile.close();

    // Mark the document as unchanged since it has been saved
    this->documentHasChanged = false;
    return true;
}

// Check if the document has changed since it was last saved
bool Document::hasChanged() const
{
    return this->documentHasChanged;
}

sf::String Document::getLine(int lineNumber) const
{
    int lastLine = static_cast<int>(this->lineBuffer.size()) - 1;

    if (lineNumber < 0 || lineNumber > lastLine)
    {
        std::cerr << "lineNumber " << lineNumber << " is not a valid number line. "
                  << "Max is: " << this->lineBuffer.size() - 1 << std::endl;
        return "";
    }

    int bufferStart = this->lineBuffer[lineNumber];
    int nextBufferStart = (lineNumber + 1 <= lastLine) ? this->lineBuffer[lineNumber + 1] : this->buffer.getSize();

    // Look for the end of the line
    while (nextBufferStart > bufferStart &&
           (this->buffer[nextBufferStart - 1] == '\n' ||
            this->buffer[nextBufferStart - 1] == '\r'))
    {
        nextBufferStart--;
    }

    int cantidad = nextBufferStart - bufferStart;

    return this->buffer.substring(bufferStart, cantidad);
}


// Get the number of characters in a specific line
int Document::charsInLine(int line) const
{
    int bufferSize = static_cast<int>(lineBuffer.size());

    if (line == bufferSize - 1)
    {
        return static_cast<int>(buffer.getSize()) - lineBuffer[lineBuffer.size() - 1];
    }
    else
    {
        return lineBuffer[line + 1] - lineBuffer[line] - 1;
    }
}

// Get the number of lines in the document
int Document::getLineCount() const
{
    return static_cast<int>(lineBuffer.size());
}

// Add text to a specific position in the document
void Document::addTextToPos(sf::String &text, int line, int charN)
{
    documentHasChanged = true;

    int textSize = static_cast<int>(text.getSize());
    auto bufferInsertPos = getBufferPos(line, charN);

    if (bufferInsertPos < 0) {
        std::cerr << "Can't get buffer pos of: " << charN << std::endl;
        std::cerr << "Buffer last line is: " << lineBuffer.size() - 1 << std::endl;
        return;
    }

    buffer.insert(bufferInsertPos, text);

    // Adjust line buffer for added text
    int lineAmount = static_cast<int>(lineBuffer.size());
    for (int l = line + 1; l < lineAmount; l++)
    {
        lineBuffer[l] += textSize;
    }

    // Find new line starts and insert them into the line buffer
    for (int i = 0; i < textSize; i++)
    {
        if (text[i] == '\n' || text[i] == 13)
        {
            int newLineStart = bufferInsertPos + i + 1;

            lineBuffer.insert(
                std::lower_bound(lineBuffer.begin(), lineBuffer.end(), newLineStart),
                newLineStart);
        }
    }
}



// Remove text from a specific position in the document
void Document::removeTextFromPos(int amount, int lineN, int charN)
{
    // Mark the document as changed
    documentHasChanged = true;

    try {
        // Calculate the position in the buffer to start removing text
        int bufferStartPos = getBufferPos(lineN, charN);
        // Erase the specified amount of text from the buffer
        buffer.erase(bufferStartPos, amount);

        // Update the line buffer to reflect the removal of text
        initLineBuffer();
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// Get text from a specific position in the document
sf::String Document::getTextFromPos(int amount, int line, int charN)
{
    // Calculate the position in the buffer to start getting text
    int bufferPos = getBufferPos(line, charN);
    // Return the substring from the specified position with the specified amount of text
    return buffer.substring(bufferPos, amount);
}

// Initialize the line buffer by splitting the document buffer into lines
bool Document::initLineBuffer()
{
    int lineStart = 0;
    int bufferSize = static_cast<int>(buffer.getSize());

    // Clear the line buffer and reserve space for about 40 lines
    lineBuffer.clear();
    lineBuffer.reserve(bufferSize / 40);
    lineBuffer.push_back(lineStart);

    // Iterate through the document buffer and identify line breaks
    const sf::Uint32 *bufferPtr = buffer.getData();
    for (int i = 0; i < bufferSize; i++, bufferPtr++)
    {
        if (*bufferPtr == '\n' || *bufferPtr == 13)
        {
            lineStart = i + 1;
            // Add the start position of the new line to the line buffer
            lineBuffer.push_back(lineStart);
        }
    }

    return true;
}

int Document::getBufferPos(int line, int charN)
{
    if (line < 0 || line >= static_cast<int>(lineBuffer.size()))
    {
        throw std::out_of_range("Invalid line number");
    }
    // Return the position in the buffer for the specified line and character number
    return lineBuffer[line] + charN;
}


// Convert a UTF-8 encoded string to a UTF-32 encoded sf::String
sf::String Document::toUtf32(const std::string &inString)
{
    sf::String outString;

    // Iterate through the input string and decode UTF-8 characters
    auto iterEnd = inString.cend();
    for (auto iter = inString.cbegin(); iter != iterEnd;)
    {
        sf::Uint32 out;
        iter = sf::Utf8::decode(iter, iterEnd, out);
        // Append the decoded character to the output string
        outString += out;
    }

    return outString;
}
