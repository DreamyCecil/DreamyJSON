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

#include "ConfigArray.h"

// Constructor
CConfigArray::CConfigArray(void) : CConfigElement(CET_ARRAY) {
  #ifdef DREAMY_JSON_GC
    ce_iGCIndex = _aConfigGarbage.Add(this);
    JSON_Print("[JSON GC]: Created CConfigArray at %d\n", ce_iGCIndex);
  #endif
};

// Destructor
CConfigArray::~CConfigArray(void) {
  #ifdef DREAMY_JSON_GC
    JSON_Print("[JSON GC]: Deleting CConfigArray (%d elements):\n", Count());
    
    int iPos = _aConfigGarbage.FindIndex(this);

    if (iPos != -1) {
      JSON_Print("- Deleted CConfigArray at %d/%d\n", iPos+1, _aConfigGarbage.Count());
      _aConfigGarbage.Delete(iPos);
    } else {
      JSON_Print("- Couldn't remove the reference from CConfigArray (%d/%d)\n", ce_iGCIndex+1, _aConfigGarbage.Count());
    }

    JSON_Print("\n");
  #endif
  
  Clear();
};

// Clear the array
void CConfigArray::Clear(void) {
  if (ca_acvValues.Count() > 0) {
    for (int i = 0; i < ca_acvValues.Count(); i++) {
      delete ca_acvValues[i];
    }
  
    ca_acvValues.Clear();
  }
};

// Add values
int CConfigArray::AddNull(void) {
  CConfigValue *cv = new CConfigValue();
  return ca_acvValues.Add(cv);
};

int CConfigArray::AddValue(const int &iValue) {
  CConfigValue *cv = new CConfigValue(iValue);
  return ca_acvValues.Add(cv);
};

int CConfigArray::AddValue(const float &fValue) {
  CConfigValue *cv = new CConfigValue(fValue);
  return ca_acvValues.Add(cv);
};

int CConfigArray::AddValue(const JSON_String &strValue) {
  CConfigValue *cv = new CConfigValue(strValue);
  return ca_acvValues.Add(cv);
};

int CConfigArray::AddValue(CConfigArray *caArray) {
  CConfigValue *cv = new CConfigValue(caArray);
  return ca_acvValues.Add(cv);
};

int CConfigArray::AddValue(CConfigBlock *cbBlock) {
  CConfigValue *cv = new CConfigValue(cbBlock);
  return ca_acvValues.Add(cv);
};

int CConfigArray::AddValue(CConfigValue *cvValue) {
  return ca_acvValues.Add(cvValue);
};

// Print the array
void CConfigArray::Print(JSON_String &strPrint, const int &iLevel) {
  JSON_StringStream strReturn;
  
  if (ca_acvValues.Count() > 0) {
    // array opening
    strReturn << "[\n";

    // print each value
    for (int i = 0; i < ca_acvValues.Count(); i++) {
      CConfigValue *cv = ca_acvValues[i];
      
      JSON_String strValue = "";
      cv->PrintValue(strValue, iLevel+1, false);
      
      strReturn << strValue.c_str() << ",\n";
    }
    
    // array closing
    strReturn << JSON_ConfigTabs(iLevel).c_str() << "]";
    
  } else {
    // empty array
    strReturn << "[]";
  }
  
  strPrint = strReturn.str();
};
