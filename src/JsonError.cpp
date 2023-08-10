// Copyright (c) 2023. SugerSalt

#include "JsonError.hpp"

namespace suger {

type_error::type_error(const std::string& msg) : std::runtime_error(msg){
}

type_error::type_error(JsonType src, JsonType dst)
  : std::runtime_error(
  "Type \"" + getTypeName(src) + R"(" can not 'as' to ")" + getTypeName(dst) + "\"") {
}

const std::string &type_error::getTypeName(JsonType type) {
  switch (type) {
    case JsonType::Null:
      static const std::string nullType("null");
      return nullType;
    case JsonType::Boolean:
      static const std::string boolType("bool");
      return boolType;
    case JsonType::Int:
      static const std::string intType("int");
      return intType;
    case JsonType::Long:
      static const std::string longType("long");
      return longType;
    case JsonType::Double:
      static const std::string doubleType("double");
      return doubleType;
    case JsonType::String:
      static const std::string stringType("string");
      return stringType;
    case JsonType::Array:
      static const std::string arrayType("array");
      return arrayType;
    case JsonType::Object:
      static const std::string objectType("object");
      return objectType;
  }
  static const std::string emptyType;
  return emptyType;
}

key_error::key_error(const std::string &key)
  : std::runtime_error("Can not find key: " + key) {
}

parse_error::parse_error(const std::string &msg) : runtime_error(msg) {

}
} // suger