// Copyright (c) 2023. SugerSalt

#include "detail/JsonBool.hpp"

namespace suger {
namespace detail {
JsonBool::JsonBool() : JsonBase(JsonType::Boolean), data_(false) {

}

JsonBool::JsonBool(bool value) : JsonBase(JsonType::Boolean), data_(value) {

}

bool JsonBool::getValue() const {
  return data_;
}

bool &JsonBool::getRef() {
  return data_;
}

void JsonBool::setValue(bool x) {
  data_ = x;
}

std::string JsonBool::toString() const {
  return data_ ? "true" : "false";
}

std::ostream &JsonBool::toDumpStream(std::ostream &out) const {
  out << (data_ ? "true" : "false");
  return out;
}
} // suger
} // detail