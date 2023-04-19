#include "InputController.h"
#include "EditorContent.h"
#include "EditorView.h"

InputController::InputController(EditorContent &editorContent)
    :mouseDown(false),  shiftPressed(false), editorContent(editorContent) {
}

void InputController::handleEvents(EditorView &textView, sf::RenderWindow &window, sf::Event &event) {
    handleMouseEvents(textView, window, event);
    handleKeyPressedEvents(textView, event);
    handleKeyReleasedEvents(event);
    handleTextEnteredEvent(textView, event);
}

void InputController::handleMouseEvents(EditorView &textView, sf::RenderWindow &window, sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        auto mousepos = sf::Mouse::getPosition(window);
        auto mousepos_text = window.mapPixelToCoords(mousepos);

        std::pair<int, int> docCoords = textView.getDocumentCoords(mousepos_text.x, mousepos_text.y);
        editorContent.resetCursor(docCoords.first, docCoords.second);

        mouseDown = true;
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        mouseDown = false;
    }
}

bool InputController::isMouseDown() {
    return mouseDown;
}

bool InputController::isShiftPressed()
{
    return shiftPressed;
}

void InputController::handleKeyPressedEvents(EditorView &textView, sf::Event &event) {   
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Up:
                editorContent.moveCursorUp();
                break;
            case sf::Keyboard::Down:
                editorContent.moveCursorDown();
                break;
            case sf::Keyboard::Left:
                editorContent.moveCursorLeft();
                break;
            case sf::Keyboard::Right:
                editorContent.moveCursorRight();
                break;
            default:
                break;
        }
    }
}

void InputController::handleKeyReleasedEvents(sf::Event &event) {
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::RShift) {
            shiftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);
        }
    }
}

void InputController::handleTextEnteredEvent(EditorView &view, sf::Event &event) {   
    if (event.type == sf::Event::TextEntered) {
        sf::String input(event.text.unicode);
        switch (event.text.unicode) {
            case '\b':
                editorContent.deleteTextBeforeCursorPos(1); 
                break;
            case 127: 
                editorContent.deleteTextAfterCursorPos(1);
                break;
            default: 
                editorContent.addTextInCursorPos(input); 
                break;
        }
    }
}

void InputController::updateCursorInEditor(EditorView &textView, float mouseX, float mouseY) {
    std::pair<int, int> docCoords = textView.getDocumentCoords(mouseX, mouseY);
    int line = docCoords.first;
    int column = docCoords.second;

    editorContent.resetCursor(line, column);
}
