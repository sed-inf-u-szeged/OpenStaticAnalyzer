/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2018 Department of Software Engineering - University of Szeged
 *
 *  Licensed under Version 1.2 of the EUPL (the "Licence");
 *
 *  You may not use this work except in compliance with the Licence.
 *
 *  You may obtain a copy of the Licence in the LICENSE file or at:
 *
 *  https://joinup.ec.europa.eu/software/page/eupl
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the Licence is distributed on an "AS IS" basis,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the Licence for the specific language governing permissions and
 *  limitations under the Licence.
 */

#include "../inc/JVMuniquenameGenerator.h"

using namespace std;

namespace columbus { namespace graphsupport {

  void stringTokenizer(vector<string>& tokenlist, const string& str, char separator) {
    int start = 0;
    for (unsigned int i = 0; i < str.size() ; i++) {
      if (str[i] == separator) {
        tokenlist.push_back(str.substr(start, i-start)); 
        start = i + 1;
      }
    }
    tokenlist.push_back(str.substr(start, str.size()-start)); 
  }


  string generateName(const string& nametoken) {
    vector<string> innerTokens;
    string name = "";

    stringTokenizer(innerTokens, nametoken, '.');
    for(unsigned int i = 0; i < innerTokens.size(); i++) {
      bool isInClass = false;
      if(innerTokens[i] == "Default Package") {
        continue;
      }
      size_t found = innerTokens[i].find("~F");
      size_t found2 = innerTokens[i].find("~T");
      if(found != string::npos) {
        name = name + innerTokens[i].substr(0, innerTokens[i].size()-2);
      } else if(found2 != string::npos) {
        name = name + innerTokens[i].substr(0, found2);
        if(i+1 < innerTokens.size() && innerTokens[i+1].find("~T") != string::npos) {
          name = name + "$";
          isInClass = true;
        }
      } else {
        name = name + innerTokens[i];
      }
      if(i < innerTokens.size() - 1 && !isInClass) {
        name = name + ".";
      }
    }

    return name;
  }


  string generateReturnAndParam(const string& token) {
    vector<string> innerTokens;
    vector<string> types;
    string type = "";

    stringTokenizer(innerTokens, token, ' ');
    if(innerTokens.size() == 1 && innerTokens[0].empty()) {
      return type;
    }

    for(unsigned int i = 0; i < innerTokens.size(); i++) {

      string innerType = "";
      string typetoken;
      if(innerTokens[i].at(innerTokens[i].size()-1) == '$') {
        typetoken = innerTokens[i].substr(0, innerTokens[i].size()-1);
      } else {
        typetoken = innerTokens[i];
      }

      stringTokenizer(types, typetoken, '.');
      bool isClass = false;

      size_t f = types[types.size()-1].find_first_of('[');
      int ar = 0;
      if(f != string::npos) {
        for(unsigned int a = 0; a < types[types.size()-1].size(); a++) {
          if(types[types.size()-1][a] == '[') {
            ar++;
          }
        }
      }
      string s;
      if(f != string::npos) {
        s = types[types.size()-1].substr(0, f);
        types[types.size()-1] = s;
      }

      if(types.size() == 1) {

        string t = types[0];
        if(t == "byte") {
          innerType = innerType + "B";
        } else if(t == "char") {
          innerType = innerType + "C";
        } else if(t == "double") {
          innerType = innerType + "D";
        } else if(t == "float") {
          innerType = innerType + "F";
        } else if(t == "int") {
          innerType = innerType + "I";
        } else if(t == "short") {
          innerType = innerType + "S";
        } else if(t == "boolean") {
          innerType = innerType + "Z";
        } else if(t == "void") {
          innerType = innerType + "V";
        } else {
          innerType = innerType + "Ljava/lang/Object;";
        }

      } else {

        for(unsigned int k = 0; k < types.size(); k++) {
          bool isInClass = false;
          size_t f2 = types[k].find("~T");
          if(f2 != string::npos) {
            isClass = true;
            innerType = innerType + types[k].substr(0, f2);
            if(k+1 < types.size() && types[k+1].find("~T") != string::npos) {
              innerType = innerType + "$";
              isInClass = true;
            }
          } else {
            innerType = innerType + types[k];
          }

          if(k < types.size() - 1 && !isInClass && !isClass) {
            innerType = innerType + "/";
          }
        }

      }

      string tmp = innerType;
      innerType = "";
      for(int a = 1; a <= ar; a++) {
        innerType = innerType + "[";
      }
      if(isClass) {
        innerType = innerType + "L";
      }
      innerType = innerType + tmp;
      if(isClass) {
        innerType = innerType + ";";
      }

      type = type + innerType;
      types.clear();
    }

    return type;
  }


  string generateGenericType(const string& token) {
    string gen = "";
    vector<string> types;

    stringTokenizer(types, token, '$');
    for(unsigned int i = 0; i < types.size(); i++) {

      string part = "";
      string typetoken = types[i];
      bool isClass = false;
      int ar = 0;

      if(typetoken[0] == ' ') {
        typetoken = typetoken.substr(1, typetoken.size()-1);
      }
      for(unsigned int j = 0; j < typetoken.size(); j++) {
        if(typetoken[j] == '.') {
          part = part + "/";
        } else if(typetoken[j] == '<') {
          unsigned int g = j;
          bool inGeneric = true;
          int pairs = 0;
          while(inGeneric && g < typetoken.size()) {
            if(typetoken[g] == '<') {
              pairs++;
            }
            if(typetoken[g] == '>') {
              pairs--;
            }
            if(pairs == 0) {
              inGeneric = false;
            }
            g++;
          }
          j = g;
          continue;
        } else if(typetoken[j] == '~' && j+1 < typetoken.size() && typetoken[j+1] == 'T') {
          isClass = true;
          if(j+2 < typetoken.size() && typetoken[j+2] == '.') {
            part = part + "$";
            j = j+2;
            continue;
          }
          if(j+2 < typetoken.size() && typetoken[j+2] == 'P') {
            j = j+2;
            continue;
          }
          j = j+1;
          continue;
        } else if(typetoken[j] == '[' && j+1 < typetoken.size() && typetoken[j+1] == ']') {
          unsigned int a = j;
          while((typetoken[a] == '[' || typetoken[a] == ']') && a < typetoken.size()) {
            if(typetoken[a] == '[') {
              ar++;
            }
            a++;
          }
        } else {
          part = part + typetoken[j];
        }
      }

      string tmp = part;
      part = "";
      if(ar > 0) {
        for(int a = 1; a <= ar; a++) {
          part = part + "[";
        }
      }
      if(isClass) {
        size_t found = tmp.find_last_of(" ");
        size_t found2 = tmp.find_first_of("<");
        if(found != string::npos && found2 != string::npos && found < found2) {
          string tmp2 = tmp.substr(0, found+1);
          string tmp3 = tmp.substr(found+1, tmp.size()-found-1);
          part = part + tmp2 + "L" + tmp3 + ";";
        } else {
          part = part + "L";
          part = part + tmp;
          part = part + ";";
        }
      } else {
        part = part + tmp;
      }

      gen = gen + part;
    }

    return gen;
  }


  string generateJVMnameForJavaGraph(const string& uniquename) {
    string JVMname = "";
    vector<string> tokenlist;
    string name = "";
    string retType = "";
    string params = "";

    stringTokenizer(tokenlist, uniquename, '@');

//name
    if(!tokenlist.empty()) {
      name = generateName(tokenlist[0]);
    }

//parameters
    if(tokenlist.size() > 2) {
      string paramtoken = tokenlist[tokenlist.size()-1].substr(1, tokenlist[tokenlist.size()-1].size()-2);
      size_t gen = tokenlist[tokenlist.size()-1].find("<");
      if(gen != string::npos) {
        params = generateGenericType(paramtoken);
      } else {
        params = generateReturnAndParam(paramtoken);
      }
    }

//return type
    if(tokenlist.size() > 2 && !tokenlist[1].empty()) {
      size_t gen = tokenlist[1].find("<");
      if(gen != string::npos) {
        retType = generateGenericType(tokenlist[1]);
      } else {
        retType = generateReturnAndParam(tokenlist[1]);
      }
    } else if(tokenlist.size() > 2 && tokenlist[1].empty()) {
      retType = "V";
    }


    JVMname = name;
    if(tokenlist.size() > 2) {
      JVMname = JVMname + "(" + params + ")" + retType;
    }

    return JVMname;
  }

}}
