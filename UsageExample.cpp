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

  CConfigBlock mapConfig;
  const char *strFile = "Test.json";

  // Try to parse the file
  if (ParseConfig(strFile, mapConfig) == DJSON_OK)
  {
    // Check for value existence
    if (mapConfig.FindKeyIndex("Hello") != -1) { // Also valid: mapConfig.GetValue("Hello", <reference>)
      mapConfig["Hello"] = string("How are you?");

    } else {
      CustomPrint("\"Hello\" key does not exist!\n");
    }

    // Check for integer type and change it
    int iVal;
    if (mapConfig.GetValue("String", iVal)) {
      CConfigValue &cvString = mapConfig["String"];

      cvString = 10;
      CustomPrint("Changed number of a \"String\"!\n");

    } else {
      CustomPrint("\"String\" is not a number!\n");
    }
    
    // Check for any type and change it
    CConfigValue cvVal;
    if (mapConfig.GetValue("String", cvVal)) {
      CConfigValue &cvString = mapConfig["String"];

      cvString = string("New string!");
      CustomPrint("Changed \"String\" value!\n");

    } else {
      CustomPrint("\"String\" is not a string!\n");
    }

    // Check for null value
    CConfigBlock cbPerson;
    if (mapConfig.GetValue("PERSONAL BLOCK", cbPerson))
    {
      // Uncomment to see a different result
      // cbPerson["spouse"] = string("Jane Doe");

      if (cbPerson.GetNull("spouse")) {
        CustomPrint("No spouse!\n");

      } else {
        string strSpouse;
        cbPerson["spouse"].PrintValue(strSpouse, 0);

        std::cout << "Spouse: " << strSpouse << "\n";
      }
    }

    // Directly change the value
    CConfigValue &cvArrayElement = mapConfig["array"].cv_aArray[2];       // String: "nice"
    cvArrayElement = string(cvArrayElement.cv_strValue) + string(" one"); // String: "nice one"

    // Print out the loaded config
    string strConfig;
    DJSON_PrintBlock(mapConfig, strConfig, 0);

    std::cout << "\nJSON file:\n" << strConfig << "\n\n";
  }

  return 0;
};
