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
extern void (*_pJSON_PrintFunction)(const char *);
extern JSON_String (*_pJSON_LoadConfigFile)(JSON_String);

// Custom print function
void CustomPrint(const char *strOut) {
  std::cout << "- " << strOut;
};

int main() {
  // Hook print function
  _pJSON_PrintFunction = (void (*)(const char *))CustomPrint;

  CConfigBlock cbConfig;
  const char *strFile = "Test.json";

  // Try to parse the file
  if (ParseConfig(strFile, cbConfig) == JSONERROR::OK) {
    // Print out the loaded config
    JSON_String strConfig;
    cbConfig.Print(strConfig);

    std::cout << "JSON file:\n" << strConfig << "\n";
  }

  return 0;
};
