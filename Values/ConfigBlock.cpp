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

#include "ConfigBlock.h"

#define ASSERT_KEY(_Key, _Name) \
  int _Key = FindKeyIndex(_Name); \
  if (_Key == -1) { \
    return false; \
  }

// Get null value
bool CConfigBlock::GetNull(DJSON_String strKey) {
  return GetType(strKey) == CVT_NULL;
};

// Get integer value
bool CConfigBlock::GetValue(DJSON_String strKey, __int64 &iValue) {
  ASSERT_KEY(iKey, strKey);

  // get the value
  CConfigValue &cv = DJSON_Block::GetValue(iKey);

  if (cv.cv_eType == CVT_INDEX) {
    iValue = cv.cv_iValue;
    return true;
  }
  return false;
};

// Get float value
bool CConfigBlock::GetValue(DJSON_String strKey, double &dValue) {
  ASSERT_KEY(iKey, strKey);

  // get the value
  CConfigValue &cv = DJSON_Block::GetValue(iKey);

  if (cv.cv_eType == CVT_FLOAT) {
    dValue = cv.cv_dValue;
    return true;
  }
  return false;
};

// Get string value
bool CConfigBlock::GetValue(DJSON_String strKey, DJSON_String &strValue) {
  ASSERT_KEY(iKey, strKey);

  // get the value
  CConfigValue &cv = DJSON_Block::GetValue(iKey);

  if (cv.cv_eType == CVT_STRING) {
    strValue = cv.cv_strValue;
    return true;
  }
  return false;
};

// Get array
bool CConfigBlock::GetValue(DJSON_String strKey, DJSON_Array &aArray) {
  ASSERT_KEY(iKey, strKey);

  // get the value
  CConfigValue &cv = DJSON_Block::GetValue(iKey);

  if (cv.cv_eType == CVT_ARRAY) {
    aArray.CopyArray(cv.cv_aArray);
    return true;
  }
  return false;
};

// Get block
bool CConfigBlock::GetValue(DJSON_String strKey, DJSON_Block &mapBlock) {
  ASSERT_KEY(iKey, strKey);

  // get the value
  CConfigValue &cv = DJSON_Block::GetValue(iKey);

  if (cv.cv_eType == CVT_BLOCK) {
    mapBlock.CopyMap(cv.cv_mapBlock);
    return true;
  }
  return false;
};

// Get config value
bool CConfigBlock::GetValue(DJSON_String strKey, CConfigValue &cvValue) {
  ASSERT_KEY(iKey, strKey);

  // get the value
  cvValue = DJSON_Block::GetValue(iKey);
  return true;
};
