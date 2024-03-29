#ifndef TextView_H
#define TextView_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "EditorContent.h"

class EditorView {
   public:
    EditorView(const sf::RenderWindow &window,
        const sf::String &workingDirectory,
        EditorContent &editorContent);

    void draw(sf::RenderWindow &window);
    void setFontSize(int fontSize);

    int getLineHeight();
    int getCharWidth();

    float getRightLimitPx();
    float getBottomLimitPx();

    sf::View getCameraView();
    void setCameraBounds(int width, int height);

    std::pair<int,int> getDocumentCoords(float mouseX, float mouseY);

   private:
    EditorContent &content;

    void drawLines(sf::RenderWindow &window);
    void drawCursor(sf::RenderWindow &window);

    sf::Font font;
    int fontSize;
    int marginXOffset;
    sf::Color colorMargin;

    int lineHeight;
    int charWidth;

    float rightLimitPx;
    float bottomLimitPx;

    sf::Color colorChar;

    sf::View camera;
};

#endif
