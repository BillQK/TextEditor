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

void InputController::handleConstantInput(EditorView &textView, sf::RenderWindow &window)
{
    if (this->isMouseDown())
    {
        auto mousepos = sf::Mouse::getPosition(window);
        auto mousepos_text = window.mapPixelToCoords(mousepos);

        updateCursorInEditor(textView, mousepos_text.x, mousepos_text.y);

        float textViewTop = 0;
        float textViewBottom = window.getView().getSize().y - 5;
        float textViewLeft = 0;
        float textViewRight = window.getView().getSize().x;

        if (mousepos.x < textViewLeft) {
            textView.scrollLeft(window);
        } else if (mousepos.x > textViewRight) {
            textView.scrollRight(window);
        }

        if (mousepos.y < textViewTop) {
            textView.scrollUp(window);
        } else if (mousepos.y > textViewBottom) {
            textView.scrollDown(window);
        }
    }
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
        bool isCtrlPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);

        bool isShiftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);

        bool isEndPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::End);

        bool isHomePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Home);

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

