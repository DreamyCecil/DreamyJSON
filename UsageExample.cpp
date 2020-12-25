/* Copyright (c) 2020 Dreamy Cecil

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

// Config parser
#include "DreamyJSON.h"
// Output
#include <iostream>

// Compatibility
extern void (*DJSON_pPrintFunction)(const char *);
extern DJSON_String (*DJSON_pLoadConfigFile)(DJSON_String);

// String type
typedef DJSON_String string;

// Custom print function
void CustomPrint(const char *strOut) {
  std::cout << "- " << strOut;
};

int main() {
  // Hook print function
  DJSON_pPrintFunction = (void (*)(const char *))CustomPrint;

  DJSON_Block mapConfig;
  const char *strFile = "Test.json";

  // Try to parse the file
  if (ParseConfig(strFile, mapConfig) == DJSON_OK)
  {
    // Check for value existence
    if (mapConfig.FindKeyIndex("Hello") != -1) {
      mapConfig["Hello"] = string("How are you?");

    } else {
      CustomPrint("\"Hello\" key does not exist!\n");
    }

    // Check for some value type
    if (mapConfig.FindKeyIndex("String") != -1) {
      CConfigValue &cvString = mapConfig["String"];

      if (cvString.cv_eType == CVT_INDEX) {
        cvString = 10;
        CustomPrint("Changed \"String\" to a number!\n");

      } else {
        cvString = string("New string!");
        CustomPrint("Changed \"String\" value!\n");
      }

    } else {
      CustomPrint("\"String\" key does not exist!\n");
    }

    // Print out the loaded config
    string strConfig;
    DJSON_PrintBlock(mapConfig, strConfig, 0);

    std::cout << "\nJSON file:\n" << strConfig << "\n\n";
  }

  return 0;
};
