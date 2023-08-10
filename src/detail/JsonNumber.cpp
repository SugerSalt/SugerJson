// Copyright (c) 2023. SugerSalt

#include "detail/JsonNumber.hpp"

namespace suger {
namespace detail {
JsonNumber::JsonNumber() : JsonBase(JsonType::Int), value_type_(Int) {
  data_.i = 0;
}

JsonNumber::JsonNumber(int value) : JsonBase(JsonType::Int), value_type_(Int) {
  data_.i = value;
}

JsonNumber::JsonNumber(int64_t value) : JsonBase(JsonType::Long), value_type_(Long) {
  data_.i64 = value;
}

JsonNumber::JsonNumber(double value) : JsonBase(JsonType::Double), value_type_(Double) {
  data_.d = value;
}

int JsonNumber::getInt() const {
  return data_.i;
}

int64_t JsonNumber::getInt64() const {
  return data_.i64;
}

double JsonNumber::getDouble() const {
  return data_.d;
}

int &JsonNumber::getIntRef() {
  return data_.i;
}

int64_t &JsonNumber::getInt64Ref() {
  return data_.i64;
}

double &JsonNumber::getDoubleRef() {
  return data_.d;
}

void JsonNumber::setValue(int x) {
  value_type_ = Int;
  data_.i = x;
}

void JsonNumber::setValue(int64_t x) {
  value_type_ = Long;
  data_.i64 = x;
}

void JsonNumber::setValue(double x) {
  value_type_ = Double;
  data_.d = x;
}

std::string JsonNumber::toString() const {
  switch (value_type_) {
    case Int:
      return std::to_string(data_.i);
    case Long:
      return std::to_string(data_.i64);
    case Double:
      return std::to_string(data_.d);
  }
  return "0";
}

std::ostream &JsonNumber::toDumpStream(std::ostream &out) const {
  switch (value_type_) {
    case Int:
      out << data_.i;
      break;
    case Long:
      out << data_.i64;
      break;
    case Double:
      out << data_.d;
      break;
  }
  return out;
}

} // detail
} // suger