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

// Constructors
CConfigValue::CConfigValue(void) : CConfigElement() {
  SetNull();
};

CConfigValue::CConfigValue(const int &iValue) : CConfigElement() {
  SetValue(iValue);
};

CConfigValue::CConfigValue(const float &fValue) : CConfigElement() {
  SetValue(fValue);
};

CConfigValue::CConfigValue(const DJSON_String &strValue) : CConfigElement() {
  SetValue(strValue);
};

CConfigValue::CConfigValue(const DJSON_Array &aArray) : CConfigElement() {
  SetValue(aArray);
};

CConfigValue::CConfigValue(const DJSON_Block &mapBlock) : CConfigElement() {
  SetValue(mapBlock);
};

// Set new value
void CConfigValue::SetNull(void) {
  cv_eType = CVT_NULL;
  cv_iValue = 0;
};

void CConfigValue::SetValue(const int &iValue) {
  cv_eType = CVT_INDEX;
  cv_iValue = iValue;
};

void CConfigValue::SetValue(const float &fValue) {
  cv_eType = CVT_FLOAT;
  cv_fValue = fValue;
};

void CConfigValue::SetValue(const DJSON_String &strValue) {
  cv_eType = CVT_STRING;
  strcpy(cv_strValue, strValue.c_str());
};

void CConfigValue::SetValue(const DJSON_Array &aArray) {
  cv_eType = CVT_ARRAY;
  cv_aArray = aArray;
};

void CConfigValue::SetValue(const DJSON_Block &mapBlock) {
  cv_eType = CVT_BLOCK;
  cv_mapBlock = mapBlock;
};

// Destructor
CConfigValue::~CConfigValue(void) {
  Clear();
};

void CConfigValue::Clear(void) {
  switch (cv_eType) {
    case CVT_ARRAY: cv_aArray.Clear(); break;
    case CVT_BLOCK: cv_mapBlock.Clear(); break;
  }
};

// Print the value
void CConfigValue::PrintValue(DJSON_String &strValue, const int &iLevel, bool bHasKey) {
  const int iKeyLevel = iLevel * !bHasKey;
  DJSON_StringStream strPrint;

  switch (cv_eType) {
    case CVT_NULL:   strPrint << DJSON_ConfigTabs(iKeyLevel).c_str() << "null"; break;
    case CVT_INDEX:  strPrint << DJSON_ConfigTabs(iKeyLevel).c_str() << cv_iValue; break;
    case CVT_FLOAT:  strPrint << DJSON_ConfigTabs(iKeyLevel).c_str() << cv_fValue; break;
    case CVT_STRING: strPrint << DJSON_ConfigTabs(iKeyLevel).c_str() << "\"" << cv_strValue << "\""; break;

    case CVT_ARRAY: {
      DJSON_String strArray;
      DJSON_PrintArray(cv_aArray, strArray, iLevel);
      
      strPrint << DJSON_ConfigTabs(iKeyLevel).c_str() << strArray.c_str();
    } break;
      
    case CVT_BLOCK: {
      DJSON_String strBlock;
      DJSON_PrintBlock(cv_mapBlock, strBlock, iLevel);
      
      strPrint << DJSON_ConfigTabs(iKeyLevel).c_str() << strBlock.c_str();
    } break;
    
    default: strPrint << DJSON_ConfigTabs(iKeyLevel).c_str() << "<error type>";
  }
  
  strValue = strPrint.str();
};
