#include <SFML/Graphics.hpp>
class MockRenderWindow {
public:
    sf::Vector2i getPosition() {
        // Replace with a suitable implementation for your use case
        return sf::Vector2i(0, 0);
    }

    sf::Vector2f mapPixelToCoords(const sf::Vector2i& point) {
        // Replace with a suitable implementation for your use case
        return sf::Vector2f(static_cast<float>(point.x), static_cast<float>(point.y));
    }
};

