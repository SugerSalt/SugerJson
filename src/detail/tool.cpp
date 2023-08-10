// Copyright (c) 2023. SugerSalt

#include "detail/tool.hpp"
#include <sstream>

namespace suger{

std::string addTranslatedChar(const std::string &str){
  std::stringstream ss;
  addTranslatedChar(str,ss);
  return ss.str();
}

std::ostream &addTranslatedChar(const std::string &str, std::ostream &out){
  for(auto & ch:str){
    if (ch=='\"'||ch=='\''||ch=='\\'){
      out << '\\';
    }
    out << ch;
  }
  return out;
}

}  // suger