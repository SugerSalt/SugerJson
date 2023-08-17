// Copyright (c) 2023. SugerSalt

#ifndef SUGERJSON_JSONOBJECT_HPP
#define SUGERJSON_JSONOBJECT_HPP

#include <unordered_map>
#include <list>
#include "JsonBase.hpp"
#include "JsonValue.hpp"

namespace suger {
namespace detail {

class JsonObject : public JsonBase {
public:
  using MemberType = std::pair<std::string, JsonValue>;
  using ObjectList = std::list<MemberType>;
  using ObjectMap = std::unordered_map<std::string, const ObjectList::iterator>;

  JsonObject();

  const ObjectList &getValue() const;

  std::size_t size() const;
  bool empty() const;

  ObjectList::iterator begin();
  ObjectList::const_iterator begin() const;
  ObjectList::iterator end();
  ObjectList::const_iterator end() const;

  void clear();
  bool insert(const std::string &key, const JsonValue &value);
  bool insert(const std::string &key, JsonValue &&value);
  std::pair<ObjectList::iterator, bool> insert(
    ObjectList::const_iterator pos, const std::string &key, const JsonValue &value);
  std::pair<ObjectList::iterator, bool> insert(
    ObjectList::const_iterator pos, const std::string &key, JsonValue &&value);
  ObjectList::iterator erase(ObjectList::const_iterator pos);
  bool erase(const std::string &key);

  JsonValue &operator[](const std::string &key);
  const JsonValue &operator[](const std::string &key) const;

  void swap(JsonObject &other);
  ObjectList::iterator find(const std::string &key);
  ObjectList::const_iterator find(const std::string &key) const;

  std::string toString() const override;
  std::ostream &toDumpStream(std::ostream &out) const override;
private:
  ObjectList data_;
  ObjectMap map_;
};

} // suger
} // detail

#endif //SUGERJSON_JSONOBJECT_HPP
