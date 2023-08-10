// Copyright (c) 2023. SugerSalt

#include "detail/JsonObject.hpp"
#include <sstream>
#include "JsonError.hpp"
#include "detail/tool.hpp"

namespace suger {
namespace detail {
JsonObject::JsonObject() : JsonBase(JsonType::Object), data_() {

}

const JsonObject::ObjectList &JsonObject::getValue() const {
  return data_;
}

JsonObject::ObjectList &JsonObject::getRef() {
  return data_;
}

void JsonObject::setValue(const JsonObject::ObjectList &x) {
  data_ = x;
}

std::size_t JsonObject::size() const {
  return data_.size();
}

bool JsonObject::empty() const {
  return data_.empty();
}

JsonObject::ObjectList::iterator JsonObject::begin() {
  return data_.begin();
}

JsonObject::ObjectList::const_iterator JsonObject::begin() const {
  return data_.begin();
}

JsonObject::ObjectList::iterator JsonObject::end() {
  return data_.end();
}

JsonObject::ObjectList::const_iterator JsonObject::end() const {
  return data_.end();
}

void JsonObject::clear() {
  data_.clear();
}

bool JsonObject::insert(const std::string &key, const JsonValue &value) {
  return data_.emplace(key, value).second;
}

bool JsonObject::insert(const std::string &key, JsonValue &&value) {
  return data_.emplace(key, std::move(value)).second;
}

JsonObject::ObjectList::iterator JsonObject::erase(JsonObject::ObjectList::const_iterator pos) {
  return data_.erase(pos);
}

std::size_t JsonObject::erase(const std::string &key) {
  return data_.erase(key);
}

JsonValue &JsonObject::operator[](const std::string &key) {
  return data_[key];
}

const JsonValue &JsonObject::operator[](const std::string &key) const {
  auto it = data_.find(key);
  if (it == data_.end()) {
    throw key_error(key);
  }
  return it->second;
}

void JsonObject::swap(JsonObject &other) {
  data_.swap(other.data_);
}

JsonObject::ObjectList::iterator JsonObject::find(const std::string &key) {
  return data_.find(key);
}

JsonObject::ObjectList::const_iterator JsonObject::find(const std::string &key) const {
  return data_.find(key);
}

std::string JsonObject::toString() const {
  std::stringstream ss;
  toDumpStream(ss);
  return ss.str();
}

std::ostream &JsonObject::toDumpStream(std::ostream &out) const {
  out << '{';
  bool not_first = false;
  for (auto &item: data_) {
    if (not_first) {
      out << ',';
    }
    not_first = true;
    addTranslatedChar(item.first, out << '\"') << "\":" << item.second;
  }
  out << '}';
  return out;
}

} // suger
} // detail