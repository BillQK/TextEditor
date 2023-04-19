#include "InputController.h"
#include "EditorContent.h"
#include "EditorView.h"

InputController::InputController(EditorContent &editorContent)
    : editorContent(editorContent) {
    this->mouseDown = false;
    this->shiftPressed = false;
}

void InputController::handleEvents(EditorView & textView, sf::RenderWindow & window, sf::Event & event)
{
    this->handleMouseEvents(textView, window, event);
    this->handleKeyPressedEvents(textView, event);
    this->handleKeyReleasedEvents(event);
    this->handleTextEnteredEvent(textView, event);
}

void InputController::handleMouseEvents(
    EditorView &textView,
    sf::RenderWindow &window,
    sf::Event &event) {

    if (event.type == sf::Event::MouseButtonPressed) {
        auto mousepos = sf::Mouse::getPosition(window);
        auto mousepos_text = window.mapPixelToCoords(mousepos);

        std::pair<int, int> docCoords = textView.getDocumentCoords(mousepos_text.x, mousepos_text.y);
        this->editorContent.resetCursor(docCoords.first, docCoords.second);

        this->mouseDown = true;
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        this->mouseDown = false;
    }
}

bool InputController::isMouseDown()
{
    return this->mouseDown;
}

void InputController::handleKeyPressedEvents(EditorView &textView, sf::Event &event)
{   
    if (event.type == sf::Event::KeyPressed) {

        if (event.key.code == sf::Keyboard::Up) {
            editorContent.moveCursorUp();
        }
        if (event.key.code == sf::Keyboard::Down) {
            editorContent.moveCursorDown();
        }
        if (event.key.code == sf::Keyboard::Left) {
            editorContent.moveCursorLeft();
        }
        if (event.key.code == sf::Keyboard::Right) {
            editorContent.moveCursorRight();
        }
    }
}

void InputController::handleKeyReleasedEvents(sf::Event &event)
{
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::RShift) {
            this->shiftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);
        }
    }
}

void InputController::handleTextEnteredEvent(EditorView &view, sf::Event &event)
{   
    if (event.type == sf::Event::TextEntered) {
        bool ctrlPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);
        sf::String input(event.text.unicode);

        if (event.text.unicode == '\b') {
            editorContent.deleteTextBeforeCursorPos(1);
        } else if (event.text.unicode == 127) { 
            editorContent.deleteTextAfterCursorPos(1);
        } else if (!ctrlPressed) {
            editorContent.addTextInCursorPos(input);
        }
    }
}

void InputController::updateCursorInEditor(EditorView &textView, float mouseX, float mouseY)
{
    std::pair<int, int> docCoords = textView.getDocumentCoords(mouseX, mouseY);
    int line = docCoords.first;
    int column = docCoords.second;

    this->editorContent.resetCursor(line, column);
}

