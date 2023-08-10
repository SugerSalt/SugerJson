// Copyright (c) 2023. SugerSalt

#ifndef SUGERJSON_JSONBOOL_HPP
#define SUGERJSON_JSONBOOL_HPP

#include "../JsonBase.hpp"

namespace suger {
namespace detail {

class JsonBool : public JsonBase {
public:
  JsonBool();
  JsonBool(bool value);

  bool getValue() const;
  bool &getRef();
  void setValue(bool x);
  std::string toString() const override;
  std::ostream &toDumpStream(std::ostream &out) const override;
private:
  bool data_;
};

} // suger
} // detail

#endif //SUGERJSON_JSONBOOL_HPP
