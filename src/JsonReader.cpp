// Copyright (c) 2023. SugerSalt

#include "JsonReader.hpp"
#include <iostream>
#include "JsonError.hpp"

namespace suger {

JsonReader::JsonReader() : token_(BeginOfStream), pos_(nullptr), end_(nullptr), col_pos_(0),
                           row_pos_(0) {

}

JsonValue JsonReader::parse(const std::string &document) {
  JsonValue json;
  doc_ = document;
  token_ = BeginOfStream;
  pos_ = doc_.data();
  end_ = doc_.data() + doc_.size();
  readValue(json);
  return json;
}

JsonValue JsonReader::parse(std::istream &in) {
  JsonValue json;
  doc_ = std::string(std::istreambuf_iterator<char>(in), {});
  token_ = BeginOfStream;
  pos_ = doc_.data();
  end_ = doc_.data() + doc_.size();
  readValue(json);
  return json;
}

bool JsonReader::parse(const std::string &document, JsonValue &json) {
  doc_ = document;
  token_ = BeginOfStream;
  pos_ = doc_.data();
  end_ = doc_.data() + doc_.size();
  return readValue(json);
}

bool JsonReader::parse(std::istream &in, JsonValue &json) {
  doc_ = std::string(std::istreambuf_iterator<char>(in), {});
  token_ = BeginOfStream;
  pos_ = doc_.data();
  end_ = doc_.data() + doc_.size();
  return readValue(json);
}

JsonReader::TokenType JsonReader::getNextToken() {
  ignoreBlank();
  switch (*pos_) {
    case '{':
      token_ = ObjectBegin;
      break;
    case '}':
      token_ = ObjectEnd;
      break;
    case '[':
      token_ = ArrayBegin;
      break;
    case ']':
      token_ = ArrayEnd;
      break;
    case '\"':
      token_ = String;
      break;
    case ',':
      token_ = ArraySeparator;
      break;
    case ':':
      token_ = MemberSeparator;
      break;
    case '/':
      token_ = Comment;
      break;
    case 't':
      if (strMatch("true", 4)) {
        pos_ += 3;
        col_pos_ += 3;
        token_ = True;
      } else {
        token_ = Error;
      }
      break;
    case 'f':
      if (strMatch("false", 5)) {
        pos_ += 4;
        col_pos_ += 4;
        token_ = False;
      } else {
        token_ = Error;
      }
      break;
    case 'n':
      if (strMatch("null", 4)) {
        pos_ += 3;
        col_pos_ += 3;
        token_ = Null;
      } else {
        token_ = Error;
      }
      break;
    case '\0':
      token_ = EndOfStream;
      break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '+':
    case '-':
      token_ = Number;
      break;
    default:
      token_ = Error;
      break;
  }
  return token_;
}

void JsonReader::ignoreBlank() {
  while (pos_ != end_) {
    char ch = *pos_;
    if (ch == ' ' || ch == '\t' || ch == '\r') {
      ++pos_;
      ++col_pos_;
    } else if (ch == '\n') {
      ++pos_;
      ++row_pos_;
      col_pos_ = 0;
    } else {
      break;
    }
  }
}

//
bool JsonReader::readValue(JsonValue &json) {
  getNextToken();
  switch (token_) {
    case ObjectBegin:
      return readObject(json);
    case ArrayBegin:
      return readArray(json);
    case String:
      return readString(json);
    case Number:
      return readNumber(json);
    case True:
      json = true;
      break;
    case False:
      json = false;
      break;
    case Null:
      json.reset();
      break;
    default:
      throwParseError("Syntax error: value, object or array expected.");
  }
  ++pos_;
  ++col_pos_;
  return true;
}

bool JsonReader::readObject(JsonValue &json) {
  json = JsonValue(JsonType::Object);
  while (true) {
    // name
    ++pos_;
    ++col_pos_;
    if (getNextToken() != String) {
      throwParseError("Syntax error: key should be a string.");
    }
    auto name = getString();
    if (json.isMember(name)) {
      throwParseError(("Syntax error: Duplicate key \"" + name + "\".").c_str());
    }
    if (getNextToken() != MemberSeparator) {
      throwParseError("Syntax error: missing ':' after object member name.");
    }
    // member
    ++pos_;
    ++col_pos_;
    JsonValue member;
    readValue(member);
    json.push_back(name, std::move(member));
    getNextToken();
    if (token_ == ObjectEnd) {
      break;
    } else if (token_ != ArraySeparator) {
      throwParseError("Syntax error: missing ',' or '}' in object declaration");
    }
  }
  ++pos_;
  ++col_pos_;
  return true;
}

bool JsonReader::readArray(JsonValue &json) {
  json = JsonValue(JsonType::Array);
  while (true) {
    ++pos_;
    ++col_pos_;
    JsonValue member;
    readValue(member);
    json.push_back(std::move(member));
    getNextToken();
    if (token_ == ArrayEnd) {
      break;
    } else if (token_ != ArraySeparator) {
      throwParseError("Syntax error: missing ',' or ']' in array declaration");
    }
  }
  ++pos_;
  ++col_pos_;
  return true;
}

bool JsonReader::readString(JsonValue &json) {
  json = getString();
  return true;
}

bool JsonReader::readNumber(JsonValue &json) {
  size_t i = 0;
  bool negative = false;
  bool is_int = true;
  double double_result = 0.0;
  int64_t long_result = 0;

  auto isDigit = [](char ch) { return ch >= '0' && ch <= '9'; };

  if (pos_[i] == '-') {
    negative = true;
    ++i;
  } else if (pos_[i] == '+') {
    ++i;
  }
  while (pos_ + i < end_ && isDigit(pos_[i])) {
    double_result = double_result * 10 + (pos_[i] - '0');
    long_result = long_result * 10 + (pos_[i] - '0');
    ++i;
  }
  if (pos_ + i < end_ && pos_[i] == '.') {
    is_int = false;
    double fraction = 0.1;
    ++i;
    while (pos_ + i < end_ && isDigit(pos_[i])) {
      double_result = double_result + (pos_[i] - '0') * fraction;
      fraction *= 0.1;
      ++i;
    }
  }
  if (pos_ + i < end_ && (pos_[i] == 'e' || pos_[i] == 'E')) {
    is_int = false;
    ++i;
    bool exponentNegative = false;
    if (pos_[i] == '-') {
      exponentNegative = true;
      ++i;
    } else if (pos_[i] == '+') {
      ++i;
    }
    int exponent = 0;
    while (pos_ + i < end_ && isDigit(pos_[i])) {
      exponent = exponent * 10 + (pos_[i] - '0');
      ++i;
    }
    double power = 1.0;
    for (int j = 0; j < exponent; j++) {
      power *= 10.0;
    }
    if (exponentNegative) {
      double_result /= power;
    } else {
      double_result *= power;
    }
  }
  if (negative) {
    double_result = -double_result;
  }
  if (is_int && long_result<INT32_MAX && long_result>INT32_MIN) {
    json = static_cast<int>(long_result);
  } else if (is_int) {
    json = long_result;
  } else {
    json = double_result;
  }
  pos_ += i;
  col_pos_ += i;
  return true;
}

bool JsonReader::strMatch(const char *pattern, int len) {
  if (end_ - pos_ < len) {
    return false;
  }
  for (int i = 0; i < len; ++i) {
    if (pos_[i] != pattern[i]) {
      return false;
    }
  }
  return true;
}

void JsonReader::throwParseError(const char *msg) const {
  std::string error_msg = msg;
  error_msg +=
    " At row: " + std::to_string(row_pos_ + 1) + ", col: " + std::to_string(col_pos_ + 1);
  throw parse_error(error_msg);
}

// get from " to "
std::string JsonReader::getString() {
  std::string str;
  const char *pos = pos_ + 1;
  while (pos != end_) {
    char ch = *pos;
    if (ch == '\"') {
      ++pos;
      break;
    } else if (ch == '\\') {
      ++pos;
      ch = *pos;
      switch (ch) {
        case 'b':
          str += '\b';
          break;
        case 'f':
          str += '\f';
          break;
        case 'n':
          str += '\n';
          break;
        case 'r':
          str += '\r';
          break;
        case 't':
          str += '\t';
          break;
        default:
          str += ch;
      }
    } else if (ch == '\n') {
      throwParseError("Syntax error: incomplete string.");
    } else {
      str += ch;
    }
    ++pos;
  }
  if (pos == end_) {
    throwParseError("Syntax error: incomplete string.");
  }
  col_pos_ += pos - pos_;
  pos_ = pos;
  return str;
}

std::istream &operator>>(std::istream &in, JsonValue &json){
  JsonReader().parse(in, json);
  return in;
}
} // suger