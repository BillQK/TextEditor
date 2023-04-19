#include <utility>
class MockEditorView {
public:
    std::pair<int, int> getDocumentCoords(float x, float y) {
        // Replace with a suitable implementation for your use case
        return std::make_pair(static_cast<int>(x), static_cast<int>(y));
    }
};