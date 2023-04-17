#include "InputController.h"

InputController::InputController(EditorContent &editorContent)
    : editorContent(editorContent) {
    this->mouseDown = false;
    this->shiftPressed = false;
}

void InputController::handleConstantInput(EditorView &view, sf::RenderWindow &window)
{
}

void InputController::handleEvents(
    EditorView &textView,
    sf::RenderWindow &window,
    sf::Event &event) {

    this->handleMouseEvents(textView, window, event);
    this->handleKeyPressedEvents(textView, event);
    this->handleKeyReleasedEvents(event);
    this->handleTextEnteredEvent(textView, event);
}

bool InputController::isMouseDown()
{
    return false;
}

void InputController::handleMouseEvents(
    EditorView &textView,
    sf::RenderWindow &window,
    sf::Event &event) {

    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
            if (event.mouseWheelScroll.delta > 0) {
                textView.scrollUp(window);
            } else {
                textView.scrollDown(window);
            }
        } else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel) {
            if (event.mouseWheelScroll.delta > 0) {
                textView.scrollLeft(window);
            } else {
                textView.scrollRight(window);
            }
        }
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        // this->editorContent.removeSelections();
        auto mousepos = sf::Mouse::getPosition(window);
        auto mousepos_text = window.mapPixelToCoords(mousepos);

    
        std::pair<int, int> docCoords = textView.getDocumentCoords(mousepos_text.x, mousepos_text.y);
        // this->editorContent.createNewSelection(docCoords.first, docCoords.second);

        this->mouseDown = true;
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        this->mouseDown = false;
    }
}

void InputController::handleKeyPressedEvents(EditorView &view, sf::Event &event)
{
}

void InputController::handleKeyReleasedEvents(sf::Event &event)
{
}

void InputController::handleTextEnteredEvent(EditorView &view, sf::Event &event)
{
}

void InputController::updateCursorInEditor(EditorView &textView, float mouseX, float mouseY)
{
}
