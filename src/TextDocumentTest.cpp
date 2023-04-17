#include <vector>
#include <iostream>
using namespace std;

#include "TextDocument.h"
#include "unit_test_framework.h"


TEST(TextDocumentTestInitialization)
{
  TextDocument document; 
  string filename = "test/test.txt";
  document.init(filename);
}


TEST_MAIN()
