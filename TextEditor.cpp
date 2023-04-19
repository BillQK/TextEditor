#include <SFML/Graphics.hpp>
#include "EditorView.h"
#include "Document.h"
#include "InputController.h"
#include "Utils.h"

int main(int argc, char* argv[]) {

    // Set working directory
    std::string workingDirectory = Utils::getWorkingDirectory(argv[0]);

    // Define file paths for save and load operations
    std::string saveFileName;
    std::string loadFileName;

    if (argc == 2) {
        saveFileName = workingDirectory + argv[1];
        loadFileName = workingDirectory + argv[1];
    } else {
        saveFileName = workingDirectory + "txt/samples.txt";
        loadFileName = workingDirectory + "txt/samples.txt";
    }

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(720, 405), saveFileName);
    sf::Color backgroundColor = sf::Color(21, 29, 45);

    // Initialize the text document
    Document textDocument;
    textDocument.init(loadFileName);

    // Initialize the editor content, view, and input controller
    EditorContent editorContent(textDocument);
    EditorView editorView(window, workingDirectory, editorContent);
    InputController inputController(editorContent);

    // Main event loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close the window when requested
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Adjust camera bounds when the window is resized
            if (event.type == sf::Event::Resized) {
                editorView.setCameraBounds(event.size.width, event.size.height);
            }

            // Save the file if the user presses Ctrl + S
            if (event.key.code == sf::Keyboard::S && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                if (textDocument.hasChanged()){
                    if (textDocument.saveFile(saveFileName)) {
                        std::cout << "SAVED TO: " << saveFileName << "\n";
                    } else {
                        std::cerr << "Error: Failed to save file " << saveFileName << std::endl;
                    }
                }
            }

            // Handle other input events
            inputController.handleEvents(editorView, window, event);
        }

        // Clear the window, update the view, and draw the editor
        window.clear(backgroundColor);
        window.setView(editorView.getCameraView());
        editorView.draw(window);
        window.display();
    }

    return 0;
}
