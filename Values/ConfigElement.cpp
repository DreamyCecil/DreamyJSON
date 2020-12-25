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

#include "ConfigValue.h"

// Print the array
void DJSON_PrintArray(DJSON_Array &aArray, DJSON_String &strPrint, const int &iLevel) {
  DJSON_StringStream strReturn;
  
  if (aArray.Count() > 0) {
    // array opening
    strReturn << "[\n";

    // print each value
    for (int i = 0; i < aArray.Count(); i++) {
      CConfigValue &cv = aArray[i];
      
      DJSON_String strValue = "";
      cv.PrintValue(strValue, iLevel+1, false);
      
      strReturn << strValue.c_str() << ",\n";
    }
    
    // array closing
    strReturn << DJSON_ConfigTabs(iLevel).c_str() << "]";
    
  } else {
    // empty array
    strReturn << "[]";
  }
  
  strPrint = strReturn.str();
};

// Print the block
void DJSON_PrintBlock(DJSON_Block &mapBlock, DJSON_String &strPrint, const int &iLevel) {
  DJSON_StringStream strReturn;
  
  if (mapBlock.Count() > 0) {
    // block opening
    strReturn << "{\n";

    for (int i = 0; i < mapBlock.Count(); i++) {
      // add the key
      DJSON_String strName = mapBlock.GetKey(i);
      CConfigValue &cv = mapBlock.GetValue(i);

      strReturn << DJSON_ConfigTabs(iLevel+1).c_str() << "\"" << strName.c_str() << "\" : ";
      
      // add the value
      DJSON_String strValue = "";
      cv.PrintValue(strValue, iLevel+1, true);
      
      strReturn << strValue.c_str() << ",\n";
    }
    
    // block closing
    strReturn << DJSON_ConfigTabs(iLevel).c_str() << "}";
    
  } else {
    // empty block
    strReturn << "{}";
  }
  
  strPrint = strReturn.str();
};
