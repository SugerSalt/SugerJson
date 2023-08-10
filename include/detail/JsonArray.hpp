// Copyright (c) 2023. SugerSalt

#ifndef SUGERJSON_JSONARRAY_HPP
#define SUGERJSON_JSONARRAY_HPP

#include <vector>
#include "../JsonBase.hpp"
#include "../JsonValue.hpp"

namespace suger {
namespace detail {

class JsonArray : public JsonBase {
public:
  using JsonList = std::vector<JsonValue>;

  JsonArray();
  JsonArray(const JsonList &value);
  JsonArray(const std::vector<bool> &value);
  JsonArray(const std::vector<int> &value);
  JsonArray(const std::vector<int64_t> &value);
  JsonArray(const std::vector<double> &value);
  JsonArray(const std::vector<std::string> &value);

  const JsonList &getValue() const;
  JsonList & getRef();
  void setValue(const JsonList &x);

  std::size_t size() const;
  bool empty() const;

  JsonList::iterator begin();
  JsonList::const_iterator begin() const;
  JsonList::iterator end();
  JsonList::const_iterator end() const;

  void clear();
  JsonList::iterator insert(JsonList::const_iterator pos, const JsonValue &value);
  JsonList::iterator insert(JsonList::const_iterator pos, JsonValue &&value);
  void push_back(const JsonValue &value);
  void push_back(JsonValue &&value);
  JsonList::iterator erase(JsonList::const_iterator pos);
  JsonList::iterator erase(JsonList::const_iterator first, JsonList::const_iterator last);
  void pop_back();

  JsonList::reference operator[](std::size_t pos);
  JsonList::const_reference operator[](std::size_t pos) const;

  void swap(JsonArray &other);

  std::string toString() const override;
  std::ostream &toDumpStream(std::ostream &out) const override;
private:
  std::vector<JsonValue> data_;
};
} // suger
} // detail

#endif //SUGERJSON_JSONARRAY_HPP
