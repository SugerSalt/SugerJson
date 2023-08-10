// Copyright (c) 2023. SugerSalt

#ifndef SUGERJSON_JSONBASE_HPP
#define SUGERJSON_JSONBASE_HPP

#include <memory>
#include <ostream>
#include "JsonType.hpp"

namespace suger {

class JsonBase {
public:
  using SharePtr = std::shared_ptr<JsonBase>;
  using WeakPtr = std::weak_ptr<JsonBase>;
  using UniquePtr = std::unique_ptr<JsonBase>;

  explicit JsonBase(JsonType type) : type_(type) {};
  ~JsonBase() = default;

  virtual std::string toString() const = 0;
  virtual std::ostream &toDumpStream(std::ostream &out) const = 0;
private:
  JsonType type_;
};

} // suger

#endif //SUGERJSON_JSONBASE_HPP
