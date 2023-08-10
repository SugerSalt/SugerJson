// Copyright (c) 2023. SugerSalt

#ifndef SUGERJSON_JSONNUMBER_HPP
#define SUGERJSON_JSONNUMBER_HPP

#include "../JsonBase.hpp"

namespace suger {
namespace detail {

class JsonNumber : public JsonBase {
public:
  JsonNumber();
  JsonNumber(int value);
  JsonNumber(int64_t value);
  JsonNumber(double value);

  int getInt() const;
  int64_t getInt64() const;
  double getDouble() const;
  int &getIntRef();
  int64_t &getInt64Ref();
  double &getDoubleRef();
  void setValue(int x);
  void setValue(int64_t x);
  void setValue(double x);

  std::string toString() const override;
  std::ostream &toDumpStream(std::ostream &out) const override;
private:
  enum {
    Int,
    Long,
    Double
  } value_type_;
  union {
    int i;
    int64_t i64;
    double d;
  } data_;
};

} // detail
} // suger

#endif //SUGERJSON_JSONNUMBER_HPP
