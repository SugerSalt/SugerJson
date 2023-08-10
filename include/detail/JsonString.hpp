// Copyright (c) 2023. SugerSalt

#ifndef SUGERJSON_JSONSTRING_HPP
#define SUGERJSON_JSONSTRING_HPP

#include "../JsonBase.hpp"

namespace suger {
namespace detail {

class JsonString : public JsonBase {
public:
  JsonString();
  JsonString(const std::string &value);
  JsonString(const char *value);

  const std::string &getValue() const;
  std::string &getRef();
  void setValue(const std::string &x);

  std::string toString() const override;
  std::ostream &toDumpStream(std::ostream &out) const override;
private:
  std::string data_;
};

} // suger
} // detail

#endif //SUGERJSON_JSONSTRING_HPP
