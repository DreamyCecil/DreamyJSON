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

#pragma once

#include "../ConfigElement.h"
#include "../Values/ConfigValue.h"

class DJSON_API CConfigBlock : CConfigElement {
  public:
    CDMap<JSON_String, CConfigValue *> cb_mapValues; // map of values
    
    // Constructor & Destructor
    CConfigBlock(void);
    ~CConfigBlock(void);
    
    const int Count(void) { return cb_mapValues.Count(); };
    void Clear(void); // clear the block
    
    // print the block
    void Print(JSON_String &strValue, const int &iLevel);
    void Print(JSON_String &strValue) { Print(strValue, 0); };
    
    // add values
    int AddNull(const JSON_String &strKey);
    int AddValue(const JSON_String &strKey, const int &iValue);
    int AddValue(const JSON_String &strKey, const float &fValue);
    int AddValue(const JSON_String &strKey, const JSON_String &strValue);
    int AddValue(const JSON_String &strKey, CConfigArray *caArray);
    int AddValue(const JSON_String &strKey, CConfigBlock *cbBlock);
    // add existing value
    int AddValue(const JSON_String &strKey, CConfigValue *cvValue);

    // check types (returns index of a key if true, otherwise -1)
    int IsIndex(const JSON_String &strKey);
    int IsFloat(const JSON_String &strKey);
    int IsString(const JSON_String &strKey);
    int IsArray(const JSON_String &strKey);
    int IsBlock(const JSON_String &strKey);

    // get values
    bool GetValue(const JSON_String &strKey, int &iValue);
    bool GetValue(const JSON_String &strKey, float &fValue);
    bool GetValue(const JSON_String &strKey, JSON_String &strValue);
    bool GetValue(const JSON_String &strKey, CConfigArray *&caArray);
    bool GetValue(const JSON_String &strKey, CConfigBlock *&cbValue);
};
