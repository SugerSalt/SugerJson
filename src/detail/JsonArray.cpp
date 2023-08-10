// Copyright (c) 2023. SugerSalt

#include "detail/JsonArray.hpp"
#include <sstream>
#include <utility>

namespace suger {
namespace detail {
JsonArray::JsonArray() : JsonBase(JsonType::Array), data_() {

}

JsonArray::JsonArray(const std::vector<bool> &value) : JsonBase(JsonType::Array) {
  for (auto item: value) {
    data_.emplace_back(item);
  }
}

JsonArray::JsonArray(const std::vector<int> &value) : JsonBase(JsonType::Array) {
  for (auto item: value) {
    data_.emplace_back(item);
  }
}
JsonArray::JsonArray(const std::vector<int64_t> &value) : JsonBase(JsonType::Array) {
  for (auto item: value) {
    data_.emplace_back(item);
  }
}

JsonArray::JsonArray(const std::vector<double> &value) : JsonBase(JsonType::Array) {
  for (auto item: value) {
    data_.emplace_back(item);
  }
}

JsonArray::JsonArray(const std::vector<std::string> &value) : JsonBase(JsonType::Array) {
  for (const auto &item: value) {
    data_.emplace_back(item);
  }
}

JsonArray::JsonArray(const JsonArray::JsonList &value) : JsonBase(JsonType::Array), data_(value) {

}

const JsonArray::JsonList &JsonArray::getValue() const {
  return data_;
}

JsonArray::JsonList & JsonArray::getRef() {
  return data_;
}

void JsonArray::setValue(const JsonArray::JsonList &x) {
  data_ = x;
}

std::size_t JsonArray::size() const {
  return data_.size();
}

bool JsonArray::empty() const {
  return data_.empty();
}

std::vector<JsonValue>::iterator JsonArray::begin() {
  return data_.begin();
}

std::vector<JsonValue>::const_iterator JsonArray::begin() const {
  return data_.begin();
}

std::vector<JsonValue>::iterator JsonArray::end() {
  return data_.end();
}

std::vector<JsonValue>::const_iterator JsonArray::end() const {
  return data_.end();
}

void JsonArray::clear() {
  data_.clear();
}

std::vector<JsonValue>::iterator
JsonArray::insert(std::vector<JsonValue>::const_iterator pos, const JsonValue &value) {
  return data_.insert(pos, value);
}

std::vector<JsonValue>::iterator
JsonArray::insert(std::vector<JsonValue>::const_iterator pos, JsonValue &&value) {
  return data_.insert(pos, std::move(value));
}

void JsonArray::push_back(const JsonValue &value) {
  data_.push_back(value);
}

void JsonArray::push_back(JsonValue &&value) {
  data_.emplace_back(std::move(value));
}

std::vector<JsonValue>::iterator JsonArray::erase(std::vector<JsonValue>::const_iterator pos) {
  return data_.erase(pos);
}

std::vector<JsonValue>::iterator JsonArray::erase(std::vector<JsonValue>::const_iterator first,
  std::vector<JsonValue>::const_iterator last) {
  return data_.erase(first, last);
}

void JsonArray::pop_back() {
  data_.pop_back();
}

JsonValue &JsonArray::operator[](std::size_t pos) {
  return data_[pos];
}

const JsonValue &JsonArray::operator[](std::size_t pos) const {
  return data_[pos];
}

void JsonArray::swap(JsonArray &other) {
  data_.swap(other.data_);
}

std::string JsonArray::toString() const {
  std::stringstream out;
  toDumpStream(out);
  return out.str();
}

std::ostream &JsonArray::toDumpStream(std::ostream &out) const {
  out << '[';
  bool not_first = false;
  for (auto &value: data_) {
    if (not_first) {
      out << ',';
    }
    not_first = true;
    out << value;
  }
  out << ']';
  return out;
}
} // detail
} // suger