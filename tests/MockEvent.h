#include <SFML/Window.hpp>
class MockEvent : public sf::Event {
public:
    MockEvent(Type eventType, sf::Keyboard::Key key = sf::Keyboard::Unknown) {
        type = eventType;
        if (eventType == KeyPressed || eventType == KeyReleased) {
            key.code = key;
        }
    }

    MockEvent(Type eventType, sf::Mouse mouse = sf::Mouse::Unknown) {
        type = eventType;
        if (type == sf::Event::MouseButtonPressed, mouse == sf::Mouse::Left) {
            ;
        }
    }
};

