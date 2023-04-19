#ifndef InputController_H
#define InputController_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "EditorView.h"
#include "EditorContent.h"

class InputController {
   public:
    InputController(EditorContent &editorContent);
    void handleEvents(EditorView &textView, sf::RenderWindow &window, sf::Event &event);
    bool isMouseDown();

    void handleMouseEvents(EditorView &view, sf::RenderWindow &window, sf::Event &event);
    void handleKeyPressedEvents(EditorView &view, sf::Event &event);
    void handleKeyReleasedEvents(sf::Event &event);
    void handleTextEnteredEvent(EditorView &view, sf::Event &event);

    void updateCursorInEditor(EditorView &textView, float mouseX, float mouseY);

   private:
    bool mouseDown;
    bool shiftPressed;
    sf::String stringCopied;

    EditorContent& editorContent;
};

#endif
