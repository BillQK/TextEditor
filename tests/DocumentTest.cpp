#include <vector>
#include <iostream>
#include <string>
using namespace std;

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

TEST(TextDocumentTestInitialization)
{
  TextDocument document;
  string filename = "test.txt";
  ASSERT_TRUE(document.init(filename));
}

TEST(TextDocumentTestSaveFile)
{
  TextDocument document;
  string filename = "test.txt";
  ASSERT_TRUE(document.init(filename));
  ASSERT_TRUE(document.saveFile(filename));
}

TEST(TextDocumentTestInitializationFailure)
{
  TextDocument document;
  string filename = "nonexistent.txt";
  ASSERT_FALSE(document.init(filename));
}

TEST(TextDocumentTestSaveFileFailure)
{
  TextDocument document;
  string incorrectFilename = "nonexistent_directory/nonexistent.txt";
  string correctFilename = "test.txt";
  ASSERT_TRUE(document.init(correctFilename));
  ASSERT_FALSE(document.saveFile(incorrectFilename));
}

TEST(TextDocumentTestOperations)
{
  TextDocument document;
  string filename = "test.txt";
  ASSERT_TRUE(document.init(filename));

  // Test line count
  ASSERT_EQUAL(document.getLineCount(), 3);

  // Test getting lines
  ASSERT_EQUAL(sfStringToString(document.getLine(0)), "hi this is a TEST");
  ASSERT_EQUAL(sfStringToString(document.getLine(1)), "3");
  ASSERT_EQUAL(sfStringToString(document.getLine(2)), "4");

  // Test characters in lines
  ASSERT_EQUAL(document.charsInLine(0), 17);
  ASSERT_EQUAL(document.charsInLine(1), 1);
  ASSERT_EQUAL(document.charsInLine(2), 1);
}

TEST(TextDocumentTestMutation)
{
  TextDocument document;
  string filename = "test2.txt";
  ASSERT_TRUE(document.init(filename));

  // Test getting lines from text file 
  ASSERT_EQUAL(document.getLineCount(), 3);
  ASSERT_EQUAL(sfStringToString(document.getLine(0)), "Line1");
  ASSERT_EQUAL(sfStringToString(document.getLine(1)), "Line2");
  ASSERT_EQUAL(sfStringToString(document.getLine(2)), "Line3");
  ASSERT_EQUAL(sfStringToString(document.getLine(3)), "");
  
  // Test adding text to the document
  sf::String addedText = document.toUtf32("hi");
  document.addTextToPos(addedText, 1, 5);
  ASSERT_EQUAL(document.getLineCount(), 3);
  ASSERT_EQUAL(sfStringToString(document.getLine(0)), "Line1");
  ASSERT_EQUAL(sfStringToString(document.getLine(1)), "Line2hi");

  // Test removing text from the document
  document.removeTextFromPos(2, 1, 5);
  ASSERT_EQUAL(document.getLineCount(), 3);
  ASSERT_EQUAL(sfStringToString(document.getLine(1)), "Line2");

  // Test getting text from position
  sf::String expectedText = document.toUtf32("Line");
  ASSERT_EQUAL(sfStringToString(document.getTextFromPos(4, 1, 0)), expectedText);

  // Test document change status
  document.documentHasChanged = false;
  document.addTextToPos(addedText, 1, 4);
  ASSERT_TRUE(document.hasChanged());
}

TEST_MAIN()
