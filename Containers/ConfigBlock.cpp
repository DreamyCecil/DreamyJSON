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

#include "ConfigBlock.h"

// Constructor
CConfigBlock::CConfigBlock(void) : CConfigElement(CET_BLOCK) {
  #ifdef DREAMY_JSON_GC
    ce_iGCIndex = _aConfigGarbage.Add(this);
    JSON_Print("[JSON GC]: Created CConfigBlock at %d\n", ce_iGCIndex);
  #endif
};

// Destructor
CConfigBlock::~CConfigBlock(void) {
  #ifdef DREAMY_JSON_GC
    JSON_Print("[JSON GC]: Deleting CConfigBlock (%d elements):\n", Count());
    
    int iPos = _aConfigGarbage.FindIndex(this);

    if (iPos != -1) {
      JSON_Print("- Deleted CConfigBlock at %d/%d\n", iPos+1, _aConfigGarbage.Count());
      _aConfigGarbage.Delete(iPos);
    } else {
      JSON_Print("- Couldn't remove the reference from CConfigBlock (%d/%d)\n", ce_iGCIndex+1, _aConfigGarbage.Count());
    }

    JSON_Print("\n");
  #endif
  
  Clear();
};

// Clear the block
void CConfigBlock::Clear(void) {
  if (cb_mapValues.Count() > 0) {
    for (int i = 0; i < cb_mapValues.Count(); i++) {
      delete cb_mapValues.GetValue(i);
    }
  
    cb_mapValues.Clear();
  }
};

// Print the block
void CConfigBlock::Print(JSON_String &strPrint, const int &iLevel) {
  strPrint = "{}";
  
  if (cb_mapValues.Count() > 0) {
    strPrint = "{\n";

    for (int i = 0; i < cb_mapValues.Count(); i++) {
      // add the key
      JSON_String strName = cb_mapValues.GetKey(i);
      CConfigValue *cv = cb_mapValues.GetValue(i);
      strPrint = JSON_ConfigPrintF("%s%s\"%s\" : ", strPrint.c_str(), JSON_ConfigTabs(iLevel+1).c_str(), strName.c_str());
      
      // add the value
      JSON_String strValue = "";
      cv->PrintValue(strValue, iLevel+1, true);
      
      strPrint = JSON_ConfigPrintF("%s%s,\n", strPrint.c_str(), strValue.c_str());
    }
    strPrint = JSON_ConfigPrintF("%s%s}", strPrint.c_str(), JSON_ConfigTabs(iLevel).c_str());
  }
};

// Add values
int CConfigBlock::AddNull(const JSON_String &strKey) {
  CConfigValue *cv = new CConfigValue();
  return cb_mapValues.Add(strKey, cv);
};

int CConfigBlock::AddValue(const JSON_String &strKey, const int &iValue) {
  CConfigValue *cv = new CConfigValue(iValue);
  return cb_mapValues.Add(strKey, cv);
};

int CConfigBlock::AddValue(const JSON_String &strKey, const float &fValue) {
  CConfigValue *cv = new CConfigValue(fValue);
  return cb_mapValues.Add(strKey, cv);
};

int CConfigBlock::AddValue(const JSON_String &strKey, const JSON_String &strValue) {
  CConfigValue *cv = new CConfigValue(strValue);
  return cb_mapValues.Add(strKey, cv);
};

int CConfigBlock::AddValue(const JSON_String &strKey, CConfigArray *caArray) {
  CConfigValue *cv = new CConfigValue(caArray);
  return cb_mapValues.Add(strKey, cv);
};

int CConfigBlock::AddValue(const JSON_String &strKey, CConfigBlock *cbBlock) {
  CConfigValue *cv = new CConfigValue(cbBlock);
  return cb_mapValues.Add(strKey, cv);
};

int CConfigBlock::AddValue(const JSON_String &strKey, CConfigValue *cvValue) {
  return cb_mapValues.Add(strKey, cvValue);
};

// Check types
int CConfigBlock::IsIndex(const JSON_String &strKey) {
  for (int iKey = 0; iKey < cb_mapValues.Count(); iKey++) {
    JSON_String strName = cb_mapValues.GetKey(iKey);
    CConfigValue *cv = cb_mapValues.GetValue(iKey);

    // wrong key name or not a number
    if (strName != strKey || cv->cv_eType != CVT_INDEX) {
      continue;
    }

    return iKey;
  }

  // couldn't find anything
  return -1;
};

int CConfigBlock::IsFloat(const JSON_String &strKey) {
  for (int iKey = 0; iKey < cb_mapValues.Count(); iKey++) {
    JSON_String strName = cb_mapValues.GetKey(iKey);
    CConfigValue *cv = cb_mapValues.GetValue(iKey);

    // wrong key name or not a number
    if (strName != strKey || cv->cv_eType != CVT_FLOAT) {
      continue;
    }

    return iKey;
  }

  // couldn't find anything
  return -1;
};

int CConfigBlock::IsString(const JSON_String &strKey) {
  for (int iKey = 0; iKey < cb_mapValues.Count(); iKey++) {
    JSON_String strName = cb_mapValues.GetKey(iKey);
    CConfigValue *cv = cb_mapValues.GetValue(iKey);

    // wrong key name or not a number
    if (strName != strKey || cv->cv_eType != CVT_STRING) {
      continue;
    }

    return iKey;
  }

  // couldn't find anything
  return -1;
};

int CConfigBlock::IsArray(const JSON_String &strKey) {
  for (int iKey = 0; iKey < cb_mapValues.Count(); iKey++) {
    JSON_String strName = cb_mapValues.GetKey(iKey);
    CConfigValue *cv = cb_mapValues.GetValue(iKey);

    // wrong key name or not a number
    if (strName != strKey || cv->cv_eType != CVT_ARRAY) {
      continue;
    }

    return iKey;
  }

  // couldn't find anything
  return -1;
};

int CConfigBlock::IsBlock(const JSON_String &strKey) {
  for (int iKey = 0; iKey < cb_mapValues.Count(); iKey++) {
    JSON_String strName = cb_mapValues.GetKey(iKey);
    CConfigValue *cv = cb_mapValues.GetValue(iKey);

    // wrong key name or not a number
    if (strName != strKey || cv->cv_eType != CVT_BLOCK) {
      continue;
    }

    return iKey;
  }

  // couldn't find anything
  return -1;
};

// Get values
bool CConfigBlock::GetValue(const JSON_String &strKey, int &iValue) {
  int iIndex = IsIndex(strKey);

  if (iIndex != -1) {
    iValue = cb_mapValues.GetValue(iIndex)->cv_iValue;
    return true;
  }

  return false;
};

bool CConfigBlock::GetValue(const JSON_String &strKey, float &fValue) {
  int iIndex = IsFloat(strKey);

  if (iIndex != -1) {
    fValue = cb_mapValues.GetValue(iIndex)->cv_fValue;
    return true;
  }

  return false;
};

bool CConfigBlock::GetValue(const JSON_String &strKey, JSON_String &strValue) {
  int iIndex = IsString(strKey);

  if (iIndex != -1) {
    strValue = cb_mapValues.GetValue(iIndex)->cv_strValue;
    return true;
  }

  return false;
};

bool CConfigBlock::GetValue(const JSON_String &strKey, CConfigArray *&caArray) {
  int iIndex = IsArray(strKey);

  if (iIndex != -1) {
    caArray = cb_mapValues.GetValue(iIndex)->cv_caValue;
    return true;
  }

  return false;
};

bool CConfigBlock::GetValue(const JSON_String &strKey, CConfigBlock *&cbValue) {
  int iIndex = IsBlock(strKey);

  if (iIndex != -1) {
    cbValue = cb_mapValues.GetValue(iIndex)->cv_cbValue;
    return true;
  }

  return false;
};
