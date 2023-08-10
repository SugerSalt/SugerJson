// Copyright (c) 2023. SugerSalt

#include "detail/JsonString.hpp"
#include "detail/tool.hpp"

namespace suger {
namespace detail {
JsonString::JsonString() : JsonBase(JsonType::String), data_() {

}

JsonString::JsonString(const std::string &value) : JsonBase(JsonType::String), data_(value) {

}

JsonString::JsonString(const char *value) : JsonBase(JsonType::String), data_(value) {

}

const std::string &JsonString::getValue() const {
  return data_;
}

std::string &JsonString::getRef() {
  return data_;
}

void JsonString::setValue(const std::string &x) {
  data_ = x;
}

std::string JsonString::toString() const {
  return data_;
}

std::ostream &JsonString::toDumpStream(std::ostream &out) const {
  out << '\"';
  addTranslatedChar(data_, out);
  out << '\"';
  return out;
}

} // suger
} // detail