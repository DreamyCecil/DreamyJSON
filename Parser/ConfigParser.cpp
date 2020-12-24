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

#include "ConfigParser.h"

#ifdef DREAMY_JSON_GC
  extern CDList<CConfigElement *> _aConfigGarbage = CDList<CConfigElement *>();
#endif

static CDList<CParserToken> _aptTokens; // Config tokens
static int _iToken = 0; // Current token
static int _ctTokens = 0; // Amount of tokens

// Config parser
JSON_ERROR ParseConfig(const char *strConfigFile, CConfigBlock &cbConfig) {
  _aptTokens.Clear();
  
  JSON_String strConfig = "";

  try {
    // try to load the file
    strConfig = JSON_LoadConfigFile(strConfigFile);
  
    int ctLen = strlen(strConfig.c_str());
    int iPos = 0;
    int iLine = 1;
    
    while (iPos < ctLen) {
      char iChar = strConfig[iPos];
      int iStart = iPos;
      
      // start the check from the next symbol
      iPos++;
      
      // check the first symbol
      switch (iChar) {
        // skip spaces
        case ' ': case '\t': case '\r': break;
        
        // count lines
        case '\n':
          iLine++;
          break;
          
        // comments
        case '/':
          // check the next symbol
          iChar = strConfig[iPos++];
          
          // one-line comment
          if (iChar == '/') {
            // reach the end of the line
            while (iPos < ctLen)
            {
              if (strConfig[iPos] == '\n') {
                break;
              }
              
              iPos++;
            }
            
          // multiline comment
          } else if (iChar == '*') {
            // reach the end of the multiline comment
            while (iPos < ctLen)
            {
              if (strConfig[iPos++] == '*') {
                if (strConfig[iPos] == '/') {
                  break;
                }
              }
              
              iPos++;
            }
            
          // invalid symbol
          } else {
            JSON_Throw("Unexpected character '%c' on line %d", DJSON_CHAR, iChar, iLine);
          }
          break;
          
        // colon
        case ':': AddToken(EPT_COLON, iLine); break;
        
        // brackets
        case '{': AddToken(EPT_OPEN_C, iLine); break;
        case '}': AddToken(EPT_CLOSE_C, iLine); break;
        case '[': AddToken(EPT_OPEN_S, iLine); break;
        case ']': AddToken(EPT_CLOSE_S, iLine); break;
        
        // comma
        case ',': AddToken(EPT_COMMA, iLine); break;
        
        // strings
        case '"': {
          // parse through the text until the closing quote
          while (iPos < ctLen)
          {
            if (strConfig[iPos] == iChar) {
              break;
            }
            
            iPos++;
          }
          
          // save the string
          if (iPos < ctLen) {
            iPos++;
            
            JSON_String strString = strConfig.substr(iStart+1, iPos - iStart - 2);
            AddToken(EPT_STRING, iLine, strString);
          
          // couldn't find the closing quote
          } else {
            JSON_Throw("Unclosed string on line %d", DJSON_STRING, iLine);
          }
        } break;
        
        // constants
        default:
          if ((iChar >= '0' && iChar <= '9') || iChar == '-') {
            bool bPreDot = true;
            bool bNegative = false;
            
            // parse through numbers
            while (iPos < ctLen) {
              iChar = strConfig[iPos];
              
              // encountered a dot
              if (iChar == '.') {
                // can't have another dot
                if (!bPreDot) {
                  break;
                }
                
                // register as a float
                bPreDot = false;
                iPos++;
                
              // copy other numbers
              } else if (iChar >= '0' && iChar <= '9') {
                iPos++;
                
              // negative number
              } else if (iChar == '-' && !bNegative) {
                bNegative = true;
                iPos++;

              // invalid symbol
              } else {
                break;
              }
            }
            
            // save the number
            JSON_String strString = strConfig.substr(iStart, iPos - iStart);
            float fValue = 0.0f;
            sscanf(strString.c_str(), "%f", &fValue);
            
            AddToken((bPreDot ? EPT_INDEX : EPT_FLOAT), iLine, fValue);
          
          // start identifier names with an underscore or letters
          } else if (iChar == '_'
                 || (iChar >= 'a' && iChar <= 'z')
                 || (iChar >= 'A' && iChar <= 'Z')) {
            // parse name symbols
            while (iPos < ctLen) {
              iChar = strConfig[iPos];
              
              // allow underscore, letters and numbers
              if (iChar == '_'
              || (iChar >= '0' && iChar <= '9')
              || (iChar >= 'a' && iChar <= 'z')
              || (iChar >= 'A' && iChar <= 'Z')) {
                iPos++;
                
              // invalid symbol
              } else {
                break;
              }
            }
            
            // copy the name
            JSON_String strName = strConfig.substr(iStart, iPos - iStart);
            
            if (strName == "true") {
              AddToken(EPT_INDEX, iLine, 1);
              
            } else if (strName == "false") {
              AddToken(EPT_INDEX, iLine, 0);

            } else if (strName == "null") {
              AddToken(EPT_NULL, iLine, 0);
              
            } else {
              JSON_Throw("Unknown constant '%s' on line %d", DJSON_CONST, strName.c_str(), iLine);
            }
          
          // unknown characters
          } else {
            JSON_Throw("Unexpected character '%c' on line %d", DJSON_CHAR, iChar, iLine);
          }
      }
    }
    
  // parsing failed
  } catch (JSON_Exception exError) {
    JSON_Print("%s\n", exError.strError);
    return exError.eCode;
  }
  
  // fill the config block
  _iToken = 0;
  _ctTokens = _aptTokens.Count();

  // no tokens
  if (_ctTokens <= 0) {
    JSON_Print("Cannot parse the config: JSON config is empty!\n");
    return DJSON_EMPTY;
  }
  
  CParserToken &pt = _aptTokens[_iToken++];
  int iFailed = 0;
  
  // check for an opening bracket
  if (pt.pt_eTokenType != EPT_OPEN_C) {
    iFailed = pt.pt_iLine;
    
  } else {
    iFailed = ParseBlock(&cbConfig);
  }
  
  if (iFailed > 0) {
    JSON_Print("Cannot parse the config \"%s\" (Invalid token on line %d)\n", strConfigFile, iFailed);
    
    cbConfig.Clear();
    return DJSON_TOKEN;
  }
  
  // parsed successfully
  return DJSON_OK;
};

// Array parser
int ParseArray(CConfigArray *caArray)
{
  while (_iToken < _ctTokens) {
    CParserToken &pt = _aptTokens[_iToken];
    
    // close the array
    if (pt.pt_eTokenType == EPT_CLOSE_S) {
      _iToken++;
      return 0;
    }
    
    CConfigValue *cvValue = new CConfigValue();
    int iFailed = ParseValue(cvValue);
  
    if (iFailed > 0) {
      return iFailed;
    }
    
    caArray->AddValue(cvValue);
  
    // next value
    CParserToken &ptComma = _aptTokens[_iToken++];

    // close the array
    if (ptComma.pt_eTokenType == EPT_CLOSE_S) {
      return 0;
    }
    
    if (ptComma.pt_eTokenType != EPT_COMMA) {
      return ptComma.pt_iLine;
    }
  }
  
  return 0;
};

// Block parser
int ParseBlock(CConfigBlock *cbConfig)
{
  while (_iToken < _ctTokens) {
    CParserToken &pt = _aptTokens[_iToken];
    
    // close the block
    if (pt.pt_eTokenType == EPT_CLOSE_C) {
      _iToken++;
      return 0;
    }
    
    int iFailed = ParseKey(cbConfig);
    
    if (iFailed > 0) {
      return iFailed;
    }
  }
  
  return 0;
};

// Key parser
int ParseKey(CConfigBlock *cbConfig)
{
  CParserToken &ptName = _aptTokens[_iToken++];
  
  if (ptName.pt_eTokenType != EPT_STRING) {
    return ptName.pt_iLine;
  }
  
  CParserToken &ptColon = _aptTokens[_iToken++];
    
  if (ptColon.pt_eTokenType != EPT_COLON) {
    return ptColon.pt_iLine;
  }
  
  CConfigValue *cvValue = new CConfigValue();
  int iFailed = ParseValue(cvValue);
  
  if (iFailed > 0) {
    return iFailed;
  }
  
  cbConfig->AddValue(ptName.pt_strValue, cvValue);
  
  // next key
  CParserToken &ptComma = _aptTokens[_iToken++];
  
  if (ptComma.pt_eTokenType != EPT_COMMA
   && ptComma.pt_eTokenType != EPT_CLOSE_C) {
    return ptComma.pt_iLine;
  }
  
  return 0;
};

// Value parser
int ParseValue(CConfigValue *cvValue)
{
  CParserToken &ptValue = _aptTokens[_iToken++];
      
  switch (ptValue.pt_eTokenType) {
    // null value
    case EPT_NULL:
      cvValue->SetNull();
      break;

    // index value
    case EPT_INDEX:
      cvValue->SetValue((int)ptValue.pt_fValue);
      break;
      
    // float value
    case EPT_FLOAT:
      cvValue->SetValue(ptValue.pt_fValue);
      break;
    
    // string value
    case EPT_STRING:
      cvValue->SetValue(ptValue.pt_strValue);
      break;
    
    // array of values
    case EPT_OPEN_S: {
      CConfigArray *caValue = new CConfigArray();
      int iFailed = ParseArray(caValue);
      
      // couldn't read the block
      if (iFailed > 0) {
        delete caValue;
        return iFailed;
      }
      
      cvValue->SetValue(caValue);
    } break;
    
    // block of values
    case EPT_OPEN_C: {
      CConfigBlock *cbValue = new CConfigBlock();
      int iFailed = ParseBlock(cbValue);
      
      // couldn't read the block
      if (iFailed > 0) {
        delete cbValue;
        return iFailed;
      }
      
      cvValue->SetValue(cbValue);
    } break;
      
    default: return ptValue.pt_iLine;
  }
  
  return 0;
};

// Add one token to the list
void AddToken(const EParserToken &eType, const int &iLine) {
  _aptTokens.Add(CParserToken(eType, iLine));
};

void AddToken(const EParserToken &eType, const int &iLine, const float &fValue) {
  _aptTokens.Add(CParserToken(eType, iLine, fValue));
};

void AddToken(const EParserToken &eType, const int &iLine, const JSON_String &strValue) {
  _aptTokens.Add(CParserToken(eType, iLine, strValue));
};