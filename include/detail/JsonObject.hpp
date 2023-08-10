// Copyright (c) 2023. SugerSalt

#ifndef SUGERJSON_JSONOBJECT_HPP
#define SUGERJSON_JSONOBJECT_HPP

#include <unordered_map>
#include "../JsonBase.hpp"
#include "../JsonValue.hpp"

namespace suger {
namespace detail {

class JsonObject : public JsonBase{
public:
  using ObjectList = std::unordered_map<std::string, JsonValue>;
  
  JsonObject();

  const ObjectList &getValue() const;
  ObjectList &getRef();
  void setValue(const ObjectList &x);

  std::size_t size() const;
  bool empty() const;

  ObjectList::iterator begin();
  ObjectList::const_iterator begin() const;
  ObjectList::iterator end();
  ObjectList::const_iterator end() const;

  void clear();
  bool insert(const std::string &key, const JsonValue &value);
  bool insert(const std::string &key, JsonValue &&value);
  ObjectList::iterator erase(ObjectList::const_iterator pos);
  std::size_t erase(const std::string &key);

  JsonValue &operator[](const std::string &key);
  const JsonValue &operator[](const std::string &key) const;

  void swap(JsonObject &other);
  ObjectList::iterator find(const std::string &key);
  ObjectList::const_iterator find(const std::string &key) const;

  std::string toString() const override;
  std::ostream &toDumpStream(std::ostream &out) const override;
private:
  ObjectList data_;
};

} // suger
} // detail

#endif //SUGERJSON_JSONOBJECT_HPP
