// Copyright (c) 2023. SugerSalt

#include "JsonReader.hpp"
#include <iostream>
#include "JsonError.hpp"

namespace suger {

JsonReader::JsonReader() : token_(BeginOfStream), col_pos_(0),
                           row_pos_(0), good_(true) {

}

JsonValue JsonReader::parse(const std::string &document) {
  reset();
  JsonValue json;
  // doc_ = document;
  token_ = BeginOfStream;
  pos_.type_ = Iterator::StringIt;
  pos_.string_it = document.begin();
  end_.type_ = Iterator::StringIt;
  end_.string_it = document.end();
  readValue(json);
  return json;
}

JsonValue JsonReader::parse(std::istream &in) {
  reset();
  JsonValue json;
  // doc_ = std::string(std::istreambuf_iterator<char>(in), {});
  token_ = BeginOfStream;
  pos_.type_ = Iterator::StreamIt;
  pos_.stream_it = std::istreambuf_iterator<char>(in);
  end_.type_ = Iterator::StreamIt;
  end_.stream_it = std::istreambuf_iterator<char>();
  readValue(json);
  return json;
}

bool JsonReader::parse(const std::string &document, JsonValue &json) noexcept {
  reset();
  // doc_ = document;
  token_ = BeginOfStream;
  pos_.type_ = Iterator::StringIt;
  pos_.string_it = document.begin();
  end_.type_ = Iterator::StringIt;
  end_.string_it = document.end();
  try {
    readValue(json);
  } catch (std::exception &e) {
    good_ = false;
    err_ = e.what();
  }
  return good_;
}

bool JsonReader::parse(std::istream &in, JsonValue &json) noexcept {
  reset();
  // doc_ = std::string(std::istreambuf_iterator<char>(in), {});
  token_ = BeginOfStream;
  pos_.type_ = Iterator::StreamIt;
  pos_.stream_it = std::istreambuf_iterator<char>(in);
  end_.type_ = Iterator::StreamIt;
  end_.stream_it = std::istreambuf_iterator<char>();
  try {
    readValue(json);
  } catch (std::exception &e) {
    good_ = false;
    err_ = e.what();
  }
  return good_;
}

bool JsonReader::good() const {
  return good_;
}

const std::string &JsonReader::getErrorString() const {
  return err_;
}

void JsonReader::reset() {
  col_pos_ = 0;
  row_pos_ = 0;
  good_ = true;
  err_.clear();
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
      token_ = Separator;
      break;
    case ':':
      token_ = MemberSeparator;
      break;
    case '/':
      token_ = Comment;
      ignoreComment();
      getNextToken();
      break;
    case 't':
      if (strMatch("rue", 3)) {
        token_ = True;
      } else {
        token_ = Error;
      }
      break;
    case 'f':
      if (strMatch("alse", 4)) {
        token_ = False;
      } else {
        token_ = Error;
      }
      break;
    case 'n':
      if (strMatch("ull", 3)) {
        token_ = Null;
      } else {
        token_ = Error;
      }
      break;
    case '\0':
    case -1:
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

void JsonReader::ignoreComment() {
  ++pos_;
  ++col_pos_;
  if (*pos_ == '/') {  // 单行注释
    while (pos_ != end_ && *pos_ != '\n') {
      ++pos_;
      ++col_pos_;
    }
    if (*pos_ == '\n') {
      ++pos_;
      ++row_pos_;
      col_pos_ = 0;
    }
  } else if (*pos_ == '*') {  // 块注释
    auto col_s = col_pos_;
    auto row_s = row_pos_;
    ++pos_;
    ++col_pos_;
    bool get_star = false;
    while (pos_ != end_) {
      char ch = *pos_;
      if (ch == '*') {
        get_star = true;
        ++pos_;
        ++col_pos_;
      } else if (get_star && ch == '/') {
        break;
      } else if (ch == '\n') {
        get_star = false;
        ++pos_;
        ++row_pos_;
        col_pos_ = 0;
      } else {
        get_star = false;
        ++pos_;
        ++col_pos_;
      }
    }
    if (pos_ == end_) {
      col_pos_ = col_s;
      row_pos_ = row_s;
      throwParseError("Syntax error: Incomplete block comment.");
    }
    ++pos_;
    ++col_pos_;
  } else {
    throwParseError("Syntax error: Comment should begin with // or /*.");
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
  bool not_first = false;
  ++pos_;
  ++col_pos_;
  while (getNextToken() != ObjectEnd) {
    if (not_first) {
      if (token_ != Separator) {
        throwParseError("Syntax error: missing ',' or '}' in object declaration");
      } else {
        ++pos_;
        ++col_pos_;
        getNextToken();
      }
    }
    not_first = true;
    // name
    if (token_ != String) {
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
  }
  ++pos_;
  ++col_pos_;
  return true;
}

bool JsonReader::readArray(JsonValue &json) {
  json = JsonValue(JsonType::Array);
  bool not_first = false;
  ++pos_;
  ++col_pos_;
  while (getNextToken() != ArrayEnd) {
    if (not_first) {
      if (token_ != Separator) {
        throwParseError("Syntax error: missing ',' or ']' in array declaration");
      } else {
        ++pos_;
        ++col_pos_;
        getNextToken();
      }
    }
    not_first = true;
    JsonValue member;
    readValue(member);
    json.push_back(std::move(member));
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
  // size_t i = 0;
  bool negative = false;
  bool is_int = true;
  double double_result = 0.0;
  int64_t long_result = 0;

  auto isDigit = [](char ch) { return ch >= '0' && ch <= '9'; };

  if (*pos_ == '-') {
    negative = true;
    ++pos_;
    ++col_pos_;
  } else if (*pos_ == '+') {
    ++pos_;
    ++col_pos_;
  }
  while (pos_ != end_ && isDigit(*pos_)) {
    double_result = double_result * 10 + (*pos_ - '0');
    long_result = long_result * 10 + (*pos_ - '0');
    ++pos_;
    ++col_pos_;
  }
  if (pos_ != end_ && *pos_ == '.') {
    is_int = false;
    double fraction = 0.1;
    ++pos_;
    ++col_pos_;
    while (pos_ != end_ && isDigit(*pos_)) {
      double_result = double_result + (*pos_ - '0') * fraction;
      fraction *= 0.1;
      ++pos_;
      ++col_pos_;
    }
  }
  if (pos_ != end_ && (*pos_ == 'e' || *pos_ == 'E')) {
    is_int = false;
    ++pos_;
    ++col_pos_;
    bool exponentNegative = false;
    if (*pos_ == '-') {
      exponentNegative = true;
      ++pos_;
      ++col_pos_;
    } else if (*pos_ == '+') {
      ++pos_;
      ++col_pos_;
    }
    int exponent = 0;
    while (pos_ != end_ && isDigit(*pos_)) {
      exponent = exponent * 10 + (*pos_ - '0');
      ++pos_;
      ++col_pos_;
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
    long_result = -long_result;
  }
  if (is_int && long_result < INT32_MAX && long_result > INT32_MIN) {
    json = static_cast<int>(long_result);
  } else if (is_int) {
    json = long_result;
  } else {
    json = double_result;
  }
  return true;
}

bool JsonReader::strMatch(const char *pattern, int len) {
  while (len--) {
    ++pos_;
    ++col_pos_;
    if (*pos_ != *pattern || pos_ == end_) {
      return false;
    }
    ++pattern;
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
  auto col_begin = col_pos_;
  ++pos_;
  ++col_pos_;
  while (pos_ != end_) {
    char ch = *pos_;
    if (ch == '\"') {
      ++pos_;
      ++col_pos_;
      break;
    } else if (ch == '\\') {
      ++pos_;
      ++col_pos_;
      ch = *pos_;
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
      col_pos_ = col_begin;
      throwParseError("Syntax error: incomplete string.");
    } else {
      str += ch;
    }
    ++pos_;
    ++col_pos_;
  }
  if (pos_ == end_) {
    col_pos_ = col_begin;
    throwParseError("Syntax error: incomplete string.");
  }
  return str;
}

void JsonReader::Iterator::operator++() {
  if (type_ == StringIt) {
    ++string_it;
  } else {
    ++stream_it;
  }
}

char JsonReader::Iterator::operator*() const {
  if (type_ == StringIt) {
    return *string_it;
  } else {
    return *stream_it;
  }
}

bool JsonReader::Iterator::operator==(const JsonReader::Iterator &rhs) const {
  if (type_ != rhs.type_) {
    return false;
  }
  if (type_ == StringIt) {
    return string_it == rhs.string_it;
  } else {
    return stream_it == rhs.stream_it;
  }
}

bool JsonReader::Iterator::operator!=(const JsonReader::Iterator &rhs) const {
  return !(*this == rhs);
}

std::istream &operator>>(std::istream &in, JsonValue &json) {
  json = JsonReader().parse(in);
  return in;
}
} // suger