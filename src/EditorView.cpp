#include "EditorView.h"

EditorView::EditorView(const sf::RenderWindow &window, const sf::String &workingDirectory, EditorContent &editorContent)
{
}

void EditorView::draw(sf::RenderWindow &window)
{
}

void EditorView::setFontSize(int fontSize)
{
}

void EditorView::scrollUp(sf::RenderWindow &window)
{
}

void EditorView::scrollDown(sf::RenderWindow &window)
{
}

void EditorView::scrollLeft(sf::RenderWindow &window)
{
}

void EditorView::scrollRight(sf::RenderWindow &window)
{
}

void EditorView::scrollTo(float x, float y)
{
}

void EditorView::rotateLeft()
{
}

void EditorView::rotateRight()
{
}

int EditorView::getLineHeight()
{
    return 0;
}

int EditorView::getCharWidth()
{
    return 0;
}

float EditorView::getRightLimitPx()
{
    return 0.0f;
}

    float EditorView::getBottomLimitPx()
{
    return 0.0f;
}

sf::View EditorView::getCameraView()
{
    return sf::View();
}

void EditorView::setCameraBounds(int width, int height)
{
}

std::pair<int, int> EditorView::getDocumentCoords(float mouseX, float mouseY)
{
    return std::pair<int, int>();
}

void EditorView::drawLines(sf::RenderWindow &window)
{
}

void EditorView::drawCursor(sf::RenderWindow &window)
{
}
