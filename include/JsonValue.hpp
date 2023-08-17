// Copyright (c) 2023. SugerSalt

#ifndef SUGERJSON_JSONVALUE_HPP
#define SUGERJSON_JSONVALUE_HPP

#include <vector>
#include <unordered_map>
#include <list>
#include "JsonBase.hpp"

namespace suger {

class JsonIterator;
class JsonConstIterator;

class JsonValue {
  friend class JsonIterator;
  friend class JsonConstIterator;

public:
  JsonValue();
  explicit JsonValue(JsonType type);
  JsonValue(bool value);
  JsonValue(int value);
  JsonValue(int64_t value);
  JsonValue(double value);
  JsonValue(const std::string &value);
  JsonValue(const char *value);
  JsonValue(const std::vector<JsonValue> &value);
  JsonValue(const std::vector<bool> &value);
  JsonValue(const std::vector<int> &value);
  JsonValue(const std::vector<int64_t> &value);
  JsonValue(const std::vector<double> &value);
  JsonValue(const std::vector<std::string> &value);
  JsonValue(const std::initializer_list<bool> &value);
  JsonValue(const std::initializer_list<int> &value);
  JsonValue(const std::initializer_list<int64_t> &value);
  JsonValue(const std::initializer_list<double> &value);
  JsonValue(const std::initializer_list<std::string> &value);
  JsonValue(const std::initializer_list<const char *> &value);
  JsonValue(const JsonValue &other);
  JsonValue(JsonValue &&other) noexcept;
  JsonValue &operator=(const JsonValue &value);
  JsonValue &operator=(JsonValue &&value) noexcept;

  void swap(JsonValue &other);
  JsonType getType() const;

  bool isNull() const;
  bool isBoolean() const;
  bool isNumber() const;
  bool isInt() const;
  bool isLong() const;
  bool isDouble() const;
  bool isString() const;
  bool isArray() const;
  bool isObject() const;

  bool asBoolean() const;
  int asInt() const;
  int64_t asLong() const;
  double asDouble() const;
  const std::string &asString() const;
  const std::vector<JsonValue> &asArray() const;
  const JsonValue &asObject() const;

  operator bool() const;
  operator int() const;
  operator int64_t() const;
  operator double() const;
  operator std::string() const;

  JsonValue &operator[](const std::string &key);
  JsonValue &operator[](const char *key);
  const JsonValue &operator[](const std::string &key) const;
  const JsonValue &operator[](const char *key) const;
  JsonValue &operator[](std::size_t index);
  JsonValue &operator[](int index);
  const JsonValue &operator[](std::size_t index) const;
  const JsonValue &operator[](int index) const;

  std::size_t size() const;
  bool empty() const;
  JsonIterator begin();
  JsonConstIterator begin() const;
  JsonIterator end();
  JsonConstIterator end() const;
  JsonIterator find(const std::string &key);
  JsonConstIterator find(const std::string &key) const;
  bool isMember(const std::string &key) const;
  JsonIterator at(std::size_t index);
  JsonConstIterator at(std::size_t index) const;

  void reset();
  void clear();
  bool push_back(const std::string &key, const JsonValue &value);
  bool push_back(const std::string &key, JsonValue &&value);
  void push_back(const JsonValue &value);
  void push_back(JsonValue &&value);
  JsonIterator insert(JsonConstIterator pos, const JsonValue &value);
  JsonIterator insert(JsonConstIterator pos, JsonValue &&value);
  std::pair<JsonIterator, bool> insert(JsonConstIterator pos, const std::string &key, const JsonValue &value);
  std::pair<JsonIterator, bool> insert(JsonConstIterator pos, const std::string &key, JsonValue &&value);
  JsonIterator erase(JsonConstIterator pos);
  bool erase(const std::string &key);
  bool removeMember(const std::string &key);

  std::string toString() const;
  std::ostream &toDumpStream(std::ostream &out) const;
  friend std::ostream &operator<<(std::ostream &out, const JsonValue &value);
private:
  JsonType type_;
  JsonBase::UniquePtr data_;

  void setToObject();
  void setToArray();
};

using ArrayIterator = std::vector<JsonValue>::iterator;
using ObjectIterator = std::list<std::pair<std::string, JsonValue>>::iterator;

class JsonIterator : public std::iterator<std::forward_iterator_tag, JsonValue> {
  friend class JsonValue;
  friend class JsonConstIterator;

public:
  JsonIterator(const JsonIterator &other);
  JsonIterator(JsonIterator &&other) noexcept;
  JsonIterator &operator=(const JsonIterator &other);
  JsonIterator &operator=(JsonIterator &&other) noexcept;

  JsonValue &operator*() const;
  JsonValue *operator->() const;
  JsonIterator &operator++();
  JsonIterator operator++(int);
  bool operator==(const JsonIterator &rhs) const;
  bool operator!=(const JsonIterator &rhs) const;

  const std::string &key() const;
  JsonValue &value() const;

private:
  explicit JsonIterator(JsonType type);
  explicit JsonIterator(JsonValue &value);
  explicit JsonIterator(const ArrayIterator &value);
  explicit JsonIterator(const ObjectIterator &value);

  JsonType type_;
  JsonValue *value_;
  ArrayIterator array_iter_;
  ObjectIterator object_iter_;
};

using ArrayConstIterator = std::vector<JsonValue>::const_iterator;
using ObjectConstIterator = std::list<std::pair<std::string, JsonValue>>::const_iterator;

class JsonConstIterator : public std::iterator<std::forward_iterator_tag, JsonValue> {
  friend class JsonValue;

public:
  JsonConstIterator(const JsonConstIterator &other);
  JsonConstIterator(const JsonIterator &other);
  JsonConstIterator(JsonConstIterator &&other) noexcept;
  JsonConstIterator &operator=(const JsonConstIterator &other);
  JsonConstIterator &operator=(const JsonIterator &other);
  JsonConstIterator &operator=(JsonConstIterator &&other) noexcept;

  const JsonValue &operator*() const;
  const JsonValue *operator->() const;
  JsonConstIterator &operator++();
  JsonConstIterator operator++(int);
  bool operator==(const JsonConstIterator &rhs) const;
  bool operator!=(const JsonConstIterator &rhs) const;

  const std::string &key() const;
  const JsonValue &value() const;

private:
  explicit JsonConstIterator(JsonType type);
  explicit JsonConstIterator(const JsonValue &value);
  explicit JsonConstIterator(const ArrayConstIterator &value);
  explicit JsonConstIterator(const ObjectConstIterator &value);

  JsonType type_;
  const JsonValue *value_;
  ArrayConstIterator array_iter_;
  ObjectConstIterator object_iter_;
};

} // suger

#endif //SUGERJSON_JSONVALUE_HPP
