#include "EditorView.h"

EditorView::EditorView(const sf::RenderWindow &window, const sf::String &workingDirectory, EditorContent &editorContent) : content(editorContent),
camera(sf::FloatRect(-50, 0, window.getSize().x, window.getSize().y))
{
    this->font.loadFromFile(workingDirectory + "fonts/FreeMono.ttf");

    this->bottomLimitPx = 1;
    this->rightLimitPx = 1;

    this->setFontSize(18); 

    this->marginXOffset = 45;
    this->colorMargin = sf::Color(32, 44, 68);

    this->colorChar = sf::Color::White;
    this->colorSelection = sf::Color(106, 154, 232);
}

void EditorView::draw(sf::RenderWindow &window)
{
   
    this->drawLines(window);


    for (int lineNumber = 1; lineNumber <= this->content.linesCount(); lineNumber++) {
        int lineHeight = 1;

        int blockHeight = lineHeight * this->fontSize;

        sf::Text lineNumberText;
        lineNumberText.setFillColor(sf::Color::White);
        lineNumberText.setFont(this->font);
        lineNumberText.setString(std::to_string(lineNumber));
        lineNumberText.setCharacterSize(this->fontSize - 1);
        lineNumberText.setPosition(-this->marginXOffset, blockHeight * (lineNumber - 1));

        sf::RectangleShape marginRect(sf::Vector2f(this->marginXOffset - 5, blockHeight));
        marginRect.setFillColor(this->colorMargin);
        marginRect.setPosition(-this->marginXOffset, blockHeight * (lineNumber - 1));

        window.draw(marginRect);
        window.draw(lineNumberText);
    }

    this->drawCursor(window);
}

void EditorView::setFontSize(int fontSize)
{
    this->fontSize = fontSize;
    this->lineHeight = fontSize;

    sf::Text tmpText;
    tmpText.setFont(this->font);
    tmpText.setCharacterSize(this->fontSize);
    tmpText.setString("_");
    float textwidth = tmpText.getLocalBounds().width;
    this->charWidth = textwidth;
}


float EditorView::getRightLimitPx() {
    return this->rightLimitPx;
}

float EditorView::getBottomLimitPx() {
    return this->bottomLimitPx;
}

int EditorView::getLineHeight() {
    return this->lineHeight;
}

int EditorView::getCharWidth() {
    return this->charWidth;
}

sf::View EditorView::getCameraView() {
    return this->camera;
}

void EditorView::setCameraBounds(int width, int height) {
    this->camera = sf::View(sf::FloatRect(-50, 0, width, height));
}


std::pair<int, int> EditorView::getDocumentCoords(float mouseX, float mouseY)
{
    int lineN = mouseY / this->getLineHeight();
    int charN = 0;

    int lastLine = this->content.linesCount() - 1;

    if (lineN < 0) {
        lineN = 0;
        charN = 0;
    } else if (lineN > lastLine) {
        lineN = lastLine;
        charN = this->content.colsInLine(lineN);
    } else {
        lineN = std::max(lineN, 0);
        lineN = std::min(lineN, lastLine);

        int column = std::round(mouseX / this->getCharWidth());
        charN = this->content.getCharIndexOfColumn(lineN, column);

        charN = std::max(charN, 0);
        charN = std::min(charN, this->content.colsInLine(lineN));
    }

    return std::pair<int, int>(lineN, charN);
}

void EditorView::drawLines(sf::RenderWindow &window)
{
    this->bottomLimitPx = this->content.linesCount() * this->fontSize;

    for (int lineNumber = 0; lineNumber < this->content.linesCount(); lineNumber++) {
        sf::String line = this->content.getLine(lineNumber);
        sf::String currentLineText = "";

        this->rightLimitPx = std::max((int)this->rightLimitPx, (int)(this->charWidth * line.getSize()));

        float offsetx = 0;

        for (int charIndexInLine = 0; charIndexInLine <= (int)line.getSize(); charIndexInLine++) {

            if (charIndexInLine == (int)line.getSize()) {
                sf::Text text;
                text.setFillColor(this->colorChar);
                text.setFont(font);
                text.setString(currentLineText);
                text.setCharacterSize(this->fontSize);
                text.setPosition(offsetx, lineNumber * this->fontSize);


                window.draw(text);

                currentLineText = "";
            }

            currentLineText += line[charIndexInLine];
        }
    }
}

void EditorView::drawCursor(sf::RenderWindow &window)
{
    int offsetY = 2;
    int cursorDrawWidth = 2;

    int charWidth = getCharWidth();
    int lineHeight = getLineHeight();   

    std::pair<int, int> cursorPos = this->content.cursorPosition();
    int lineN = cursorPos.first;
    int column = cursorPos.second;

    sf::RectangleShape cursorRect(sf::Vector2f(cursorDrawWidth, lineHeight));
    cursorRect.setFillColor(sf::Color::White);

    cursorRect.setPosition(
        column * charWidth,
        (lineN * lineHeight) + offsetY);

    window.draw(cursorRect);
}
