#include <vector>
#include <iostream>
#include <string>
using namespace std;

#include "src/InputController.h"
#include "src/EditorContent.h"
#include "src/EditorView.h"
#include "src/TextDocument.h"
#include "unit_test_framework.h"
#include "MockEditorView.h"        // Replace with the mock class
#include "MockRenderWindow.h"      // Replace with the mock class
#include "MockEvent.h"             // Replace with the mock class


TEST(InputControllerTestInitialization)
{   
    TextDocument document.init('test.txt');
    EditorContent editorContent(document);
    InputController inputController(editorContent);

    // Check if the initial state of the InputController object is as expected
    ASSERT_FALSE(inputController.getMouseDown());
    ASSERT_FALSE(inputController.getShiftPressed());
}

TEST(InputControllerTestIsMouseDown)
{
    TextDocument document.init('test.txt');
    EditorContent editorContent(document);
    InputController inputController(editorContent);

    // Test different mouse scenarios and verify the expected behavior    
    ASSERT_FALSE(inputController.getMouseDown());
    inputController.handleMouseEvents()

}

TEST(InputControllerTestHandleMouseEvents)
{
  EditorContent editorContent;
  InputController inputController(editorContent);

  EditorView view;
  sf::RenderWindow window;
  sf::Event event;

  // Test different mouse events and verify the expected behavior
}

TEST(InputControllerTestHandleKeyPressedEvents)
{
  EditorContent editorContent;
  InputController inputController(editorContent);

  EditorView view;
  sf::Event event;

  // Test different key press events and verify the expected behavior
}

TEST(InputControllerTestHandleKeyReleasedEvents)
{
  EditorContent editorContent;
  InputController inputController(editorContent);

  sf::Event event;

  // Test different key release events and verify the expected behavior
}

TEST(InputControllerTestHandleTextEnteredEvent)
{
  EditorContent editorContent;
  InputController inputController(editorContent);

  EditorView view;
  sf::Event event;

  // Test different text input events and verify the expected behavior
}

TEST(InputControllerTestUpdateCursorInEditor)
{
  EditorContent editorContent;
  InputController inputController(editorContent);

  EditorView view;
  float mouseX, mouseY;

  // Test different cursor positions and verify the expected behavior
}

TEST(InputControllerTestHandleKeyPressedEvents)
{
  EditorContent editorContent;
  InputController inputController(editorContent);

  EditorView view;

  // Create a mock key press event for 'A'
  sf::Event event;
  event.type = sf::Event::KeyPressed;
  event.key.code = sf::Keyboard::A;

  // Test pressing 'A' and verify the expected behavior
  inputController.handleKeyPressedEvents(view, event);
  // Check any changes in EditorContent or EditorView after pressing 'A'

  // Create a mock key press event for 'Enter'
  event.key.code = sf::Keyboard::Enter;

  // Test pressing 'Enter' and verify the expected behavior
  inputController.handleKeyPressedEvents(view, event);
  // Check any changes in EditorContent or EditorView after pressing 'Enter'

  // Add more test cases for other key press events
}


TEST_MAIN()
