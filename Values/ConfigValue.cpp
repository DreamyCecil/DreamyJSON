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

// Garbage collector debug output
#ifdef DREAMY_JSON_GC
  #define JSON_GC_CREATE \
    ce_iGCIndex = _aConfigGarbage.Add(this); \
    JSON_Print("[JSON GC]: Created CConfigValue (%s) at %d\n", _astrConfigValueTypes[cv_eType], ce_iGCIndex)

  #define JSON_GC_TYPE \
    JSON_Print("- Assigned %s type to CConfigValue at %d\n\n", _astrConfigValueTypes[cv_eType], ce_iGCIndex)

#else
  #define JSON_GC_CREATE
  #define JSON_GC_TYPE
#endif

// Constructors
CConfigValue::CConfigValue(void) : CConfigElement(CET_VALUE) {
  SetNull();
  JSON_GC_CREATE;
};

CConfigValue::CConfigValue(const int &iValue) : CConfigElement(CET_VALUE) {
  SetValue(iValue);
  JSON_GC_CREATE;
};

CConfigValue::CConfigValue(const float &fValue) : CConfigElement(CET_VALUE) {
  SetValue(fValue);
  JSON_GC_CREATE;
};

CConfigValue::CConfigValue(const JSON_String &strValue) : CConfigElement(CET_VALUE) {
  SetValue(strValue);
  JSON_GC_CREATE;
};

CConfigValue::CConfigValue(CConfigArray *caValue) : CConfigElement(CET_VALUE) {
  SetValue(caValue);
  JSON_GC_CREATE;
};

CConfigValue::CConfigValue(CConfigBlock *cbValue) : CConfigElement(CET_VALUE) {
  SetValue(cbValue);
  JSON_GC_CREATE;
};

// Set new value
void CConfigValue::SetNull(void) {
  cv_eType = CVT_NULL;
  cv_iValue = 0;
  JSON_GC_TYPE;
};

void CConfigValue::SetValue(const int &iValue) {
  cv_eType = CVT_INDEX;
  cv_iValue = iValue;
  JSON_GC_TYPE;
};

void CConfigValue::SetValue(const float &fValue) {
  cv_eType = CVT_FLOAT;
  cv_fValue = fValue;
  JSON_GC_TYPE;
};

void CConfigValue::SetValue(const JSON_String &strValue) {
  cv_eType = CVT_STRING;
  strcpy(cv_strValue, strValue.c_str());
  JSON_GC_TYPE;
};

void CConfigValue::SetValue(CConfigArray *caValue) {
  cv_eType = CVT_ARRAY;
  cv_caValue = caValue;
  JSON_GC_TYPE;
};

void CConfigValue::SetValue(CConfigBlock *cbValue) {
  cv_eType = CVT_BLOCK;
  cv_cbValue = cbValue;
  JSON_GC_TYPE;
};

// Destructor
CConfigValue::~CConfigValue(void) {
  #ifdef DREAMY_JSON_GC
    JSON_Print("[JSON GC]: Deleting CConfigValue (%s): ", _astrConfigValueTypes[cv_eType]);
    
    switch (cv_eType) {
      case CVT_INDEX:
      case CVT_FLOAT:
      case CVT_STRING: {
        JSON_String strVal;
        PrintValue(strVal, 0, true);
        JSON_Print("%s\n", strVal.c_str());
      } break;

      case CVT_ARRAY: JSON_Print("<array>\n"); break;
      case CVT_BLOCK: JSON_Print("<block>\n"); break;

      default: JSON_Print("\n");
    }
    
    int iPos = _aConfigGarbage.FindIndex(this);

    if (iPos != -1) {
      JSON_Print("- Deleted CConfigValue at %d/%d\n", iPos+1, _aConfigGarbage.Count());
      _aConfigGarbage.Delete(iPos);
    } else {
      JSON_Print("- Couldn't remove the reference from CConfigValue (%d/%d)\n", ce_iGCIndex+1, _aConfigGarbage.Count());
    }

    JSON_Print("\n");
  #endif
  
  Clear();
};

void CConfigValue::Clear(void) {
  switch (cv_eType) {
    case CVT_ARRAY: delete cv_caValue; break;
    case CVT_BLOCK: delete cv_cbValue; break;
  }
};

// Print the value
void CConfigValue::PrintValue(JSON_String &strValue, const int &iLevel, bool bHasKey) {
  const int iKeyLevel = iLevel * !bHasKey;

  switch (cv_eType) {
    case CVT_NULL:  strValue = JSON_ConfigPrintF("%snull", JSON_ConfigTabs(iKeyLevel).c_str()); break;
    case CVT_INDEX: strValue = JSON_ConfigPrintF("%s%d", JSON_ConfigTabs(iKeyLevel).c_str(), cv_iValue); break;
    case CVT_FLOAT: strValue = JSON_ConfigPrintF("%s%f", JSON_ConfigTabs(iKeyLevel).c_str(), cv_fValue); break;

    case CVT_STRING:
      strValue = JSON_ConfigPrintF("%s\"%s\"", JSON_ConfigTabs(iKeyLevel).c_str(), cv_strValue);
      break;

    case CVT_ARRAY:
      cv_caValue->Print(strValue, iLevel);
      strValue = JSON_ConfigPrintF("%s%s", JSON_ConfigTabs(iKeyLevel).c_str(), strValue.c_str());
      break;
      
    case CVT_BLOCK:
      cv_cbValue->Print(strValue, iLevel);
      strValue = JSON_ConfigPrintF("%s%s", JSON_ConfigTabs(iKeyLevel).c_str(), strValue.c_str());
      break;
    
    default: strValue = "<error type>";
  }
};
