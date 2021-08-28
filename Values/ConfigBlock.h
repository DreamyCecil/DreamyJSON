/* Copyright (c) 2020-2021 Dreamy Cecil

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

#pragma once

#include "ConfigValue.h"

class DJSON_API CConfigBlock : public DJSON_Block {
  public:
    // Get value type
    inline EConfigValueType GetType(DJSON_String strKey) {
      return operator[](strKey).cv_eType;
    };

    // Get null value
    inline bool GetNull(DJSON_String strKey);

    // Get integer value
    bool GetValue(DJSON_String strKey, __int64 &iValue);
    bool GetValue(DJSON_String strKey, int &iValue);
    // Get float value
    bool GetValue(DJSON_String strKey, double &dValue);
    bool GetValue(DJSON_String strKey, float &fValue);
    // Get string value
    bool GetValue(DJSON_String strKey, DJSON_String &strValue);
    // Get array
    bool GetValue(DJSON_String strKey, DJSON_Array &aArray);
    // Get block
    bool GetValue(DJSON_String strKey, DJSON_Block &mapBlock);

    // Get config value
    bool GetValue(DJSON_String strKey, CConfigValue &cvValue);
};
