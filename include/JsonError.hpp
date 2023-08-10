// Copyright (c) 2023. SugerSalt

#ifndef SUGERJSON_JSONERROR_HPP
#define SUGERJSON_JSONERROR_HPP

#include <stdexcept>
#include "JsonType.hpp"

namespace suger {

class parse_error : public std::runtime_error{
public:
  explicit parse_error(const std::string& msg);
};

class type_error : public std::runtime_error{
public:
  explicit type_error(const std::string& msg);
  type_error(JsonType src, JsonType dst);
  static const std::string & getTypeName(JsonType type);
};

class key_error : public std::runtime_error{
public:
  explicit key_error(const std::string& key);
};

} // suger

#endif //SUGERJSON_JSONERROR_HPP
