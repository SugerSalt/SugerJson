// Copyright (c) 2023. SugerSalt

#include "detail/JsonObject.hpp"
#include <sstream>
#include "JsonError.hpp"
#include "detail/tool.hpp"

namespace suger {
namespace detail {
JsonObject::JsonObject() : JsonBase(JsonType::Object) {

}

const JsonObject::ObjectList &JsonObject::getValue() const {
  return data_;
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
  map_.clear();
}

bool JsonObject::insert(const std::string &key, const JsonValue &value) {
  if (map_.count(key)) {
    return false;
  }
  data_.emplace_back(key, value);
  auto it = std::prev(data_.end());
  map_.emplace(key, it);
  return true;
}

bool JsonObject::insert(const std::string &key, JsonValue &&value) {
  if (map_.count(key)) {
    return false;
  }
  data_.emplace_back(key, std::move(value));
  auto it = std::prev(data_.end());
  map_.emplace(key, it);
  return true;
}

std::pair<JsonObject::ObjectList::iterator, bool> JsonObject::insert(
  JsonObject::ObjectList::const_iterator pos,
  const std::string &key, const JsonValue &value) {
  auto it_map = map_.find(key);
  if (it_map != map_.end()) {
    return {it_map->second, false};
  }
  auto it = data_.emplace(pos, key, value);
  map_.emplace(key, it);
  return {it, true};
}

std::pair<JsonObject::ObjectList::iterator, bool> JsonObject::insert(
  JsonObject::ObjectList::const_iterator pos,
  const std::string &key, JsonValue &&value) {
  auto it_map = map_.find(key);
  if (it_map != map_.end()) {
    return {it_map->second, false};
  }
  auto it = data_.emplace(pos, key, std::move(value));
  map_.emplace(key, it);
  return {it, true};
}

JsonObject::ObjectList::iterator JsonObject::erase(JsonObject::ObjectList::const_iterator pos) {
  auto it = map_.find(pos->first);
  map_.erase(it);
  return data_.erase(pos);
}

bool JsonObject::erase(const std::string &key) {
  auto it = map_.find(key);
  if (it == map_.end()) {
    return false;
  }
  data_.erase(it->second);
  map_.erase(it);
  return true;
}

JsonValue &JsonObject::operator[](const std::string &key) {
  auto it = map_.find(key);
  if (it == map_.end()) {
    data_.emplace_back(key, JsonValue());
    it = map_.emplace(key, std::prev(data_.end())).first;
  }
  return it->second->second;
}

const JsonValue &JsonObject::operator[](const std::string &key) const {
  auto it = map_.find(key);
  if (it == map_.end()) {
    throw key_error(key);
  }
  return it->second->second;
}

void JsonObject::swap(JsonObject &other) {
  data_.swap(other.data_);
  map_.swap(other.map_);
}

JsonObject::ObjectList::iterator JsonObject::find(const std::string &key) {
  auto it = map_.find(key);
  if (it == map_.end()) {
    return data_.end();
  }
  return it->second;
}

JsonObject::ObjectList::const_iterator JsonObject::find(const std::string &key) const {
  auto it = map_.find(key);
  if (it == map_.end()) {
    return data_.end();
  }
  return it->second;
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