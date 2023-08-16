// Copyright (c) 2023. SugerSalt

#ifndef SUGERJSON_JSONREADER_HPP
#define SUGERJSON_JSONREADER_HPP

#include <istream>
#include "JsonValue.hpp"

namespace suger {

class JsonReader {
public:
  JsonReader();

  JsonValue parse(const std::string &document);
  JsonValue parse(std::istream &in);
  bool parse(const std::string &document, JsonValue &json);
  bool parse(std::istream &in, JsonValue &json);


private:
  enum TokenType {
    BeginOfStream,
    EndOfStream,
    ObjectBegin,  // {
    ObjectEnd,    // }
    ArrayBegin,   // [
    ArrayEnd,     // ]
    String,       // "
    Number,       // 0-9 + -
    True,         // true
    False,        // false
    Null,         // null
    Separator,    // ,
    MemberSeparator,  // :
    Comment,          // /
    Error
  };
  TokenType token_;
  const char *pos_;
  const char *end_;
  int64_t col_pos_;
  int64_t row_pos_;

  std::string doc_;

  TokenType getNextToken();
  void ignoreBlank();
  bool readValue(JsonValue &json);
  bool readObject(JsonValue &json);
  bool readArray(JsonValue &json);
  bool readString(JsonValue &json);
  bool readNumber(JsonValue &json);

  std::string getString();
  bool strMatch(const char *pattern, int len);
  void throwParseError(const char *msg) const;
};

std::istream &operator>>(std::istream &in, JsonValue &json);

} // suger

#endif //SUGERJSON_JSONREADER_HPP
