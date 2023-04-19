#include <vector>
#include <iostream>
using namespace std;

#include "EditorContent.h"
#include "Cursor.h"
#include "Document.h"
#include "unit_test_framework.h"

// Helper function to convert sfString to string
std::string sfStringToString(const sf::String &sfStr)
{
  std::string result;
  for (const auto &ch : sfStr)
  {
    if (ch != '\r')
    {
      std::string utf8_char;
      sf::Utf8::encode(ch, std::back_inserter(utf8_char));
      result += utf8_char;
    }
  }
  return result;
}

TEST(EditorContentAddTextInCursorPos) {
    Document doc;
    doc.init("testEditorContentTest.txt");
    EditorContent ec(doc);
    ec.addTextInCursorPos("Hello ");
    ec.addTextInCursorPos("world");
    ASSERT_EQUAL(ec.getLine(0), "Hello world");
}

TEST(EditorContentDeleteTextAfterCursorPos) {
    Document doc;
    doc.init("testEditorContentTest.txt");
    EditorContent ec(doc);
    ec.addTextInCursorPos("Hello world");
    ec.resetCursor(0, 5);
    ec.deleteTextAfterCursorPos(2);
    ASSERT_EQUAL(sfStringToString(ec.getLine(0)), "Helloorld");
}

TEST(EditorContentDeleteTextBeforeCursorPos) {
    Document doc;
    doc.init("test.txt");
    EditorContent ec(doc);
    ec.addTextInCursorPos("Hello world");
    ec.resetCursor(0, 6);
    ec.deleteTextBeforeCursorPos(2);
    ASSERT_EQUAL(ec.getLine(0), "Hellworld");
}

TEST(EditorContentMoveCursorLeft) {
    Document doc;
    doc.init("test.txt");
    EditorContent ec(doc);
    ec.addTextInCursorPos("Hello");
    ec.moveCursorLeft();
    ASSERT_EQUAL(ec.cursorPosition().second, 4);
}

TEST(EditorContentMoveCursorRight) {
    Document doc;
    doc.init("test.txt");
    EditorContent ec(doc);
    ec.addTextInCursorPos("Hello");
    ec.moveCursorRight();
    ASSERT_EQUAL(ec.cursorPosition().second, 5);
}

TEST(EditorContentMoveCursorUp) {
    Document doc;
    doc.init("test.txt");
    EditorContent ec(doc);
    ec.addTextInCursorPos("Hello\nWorld");
    ec.moveCursorDown();
    ec.moveCursorUp();
    ASSERT_EQUAL(ec.cursorPosition().first, 0);
}

TEST(EditorContentMoveCursorDown) {
    Document doc;
    doc.init("test.txt");
    EditorContent ec(doc);
    ec.addTextInCursorPos("Hello\nWorld");
    ec.moveCursorDown();
    ASSERT_EQUAL(ec.cursorPosition().first, 1);
}

TEST(EditorContentGetLineCount) {
    Document doc;
    doc.init("test.txt");
    EditorContent ec(doc);
    ec.addTextInCursorPos("Hello\nWorld\n");
    ASSERT_EQUAL(ec.linesCount(), 3);
}

TEST(EditorContentGetColsInLine) {
    Document doc;
    doc.init("test.txt");
    EditorContent ec(doc);
    ec.addTextInCursorPos("Hello\nWorld\n");
    ASSERT_EQUAL(ec.colsInLine(1), 5);
}

TEST(EditorContentGetLine) {
    Document doc;
    doc.init("test.txt");
    EditorContent ec(doc);
    ec.addTextInCursorPos("Hello\nWorld\n");
    ASSERT_EQUAL(ec.getLine(1), "World");
}

TEST(EditorContentGetCursorLine) {
    Document doc;
    doc.init("test.txt");
    EditorContent ec(doc);
    ec.addTextInCursorPos("Hello\nWorld\n");
    ASSERT_EQUAL(ec.getCursorLine(), "");
}

TEST(EditorContentResetCursor) {
    Document doc;
    doc.init("test.txt");
    EditorContent ec(doc);
    ec.addTextInCursorPos("Hello\nWorld\n");
    ec.resetCursor(1, 2);
    ASSERT_EQUAL(ec.cursorPosition().first, 1);
    ASSERT_EQUAL(ec.cursorPosition().second, 2);
}

TEST(EditorContentGetCharIndexOfColumn) {
    Document doc;
    doc.init("test.txt");
    EditorContent ec(doc);
    ec.addTextInCursorPos("Hello\nWorld\n");
    ASSERT_EQUAL(ec.getCharIndexOfColumn(1, 2), 2);
}

TEST(EditorContentGetColumnFromCharN) {
    Document doc;
    doc.init("test.txt");
    EditorContent ec(doc);
    ec.addTextInCursorPos("Hello\nWorld\n");
    ASSERT_EQUAL(ec.getColumnFromCharN(1, 2), 2);
}

TEST_MAIN()



