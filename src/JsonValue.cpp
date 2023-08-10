// Copyright (c) 2023. SugerSalt

#include "JsonValue.hpp"
#include "detail/JsonImp.hpp"
#include "JsonError.hpp"


namespace suger {
using namespace detail;

JsonValue::JsonValue() : type_(JsonType::Null) {

}

#if __cplusplus < 201103L
#error "The compiler should support at least c++11."
#elif __cplusplus < 201402L
JsonValue::JsonValue(JsonType type) : type_(type) {
  switch (type) {
    case JsonType::Null:
      break;
    case JsonType::Boolean:
      data_ = std::unique_ptr<JsonBool>();
      break;
    case JsonType::Int:
      data_ = std::unique_ptr<JsonNumber>(new JsonNumber(0));
      break;
    case JsonType::Long:
      data_ = std::unique_ptr<JsonNumber>(new JsonNumber(0L));
      break;
    case JsonType::Double:
      data_ = std::unique_ptr<JsonNumber>(new JsonNumber(0.0));
      break;
    case JsonType::String:
      data_ = std::unique_ptr<JsonString>(new JsonString());
      break;
    case JsonType::Array:
      data_ = std::unique_ptr<JsonArray>(new JsonArray());
      break;
    case JsonType::Object:
      data_ = std::unique_ptr<JsonObject>(new JsonObject());
      break;
  }
}

JsonValue::JsonValue(bool value)
  : type_(JsonType::Boolean), data_(new JsonBool(value)) {
}

JsonValue::JsonValue(int value)
  : type_(JsonType::Int), data_(new JsonNumber(value)) {
}

JsonValue::JsonValue(int64_t value)
  : type_(JsonType::Long), data_(new JsonNumber(value)) {
}

JsonValue::JsonValue(double value)
  : type_(JsonType::Double), data_(new JsonNumber(value)) {
}

JsonValue::JsonValue(const std::string &value)
  : type_(JsonType::String), data_(new JsonString(value)) {
}

JsonValue::JsonValue(const char *value)
  : type_(JsonType::String), data_(new JsonString(value)) {
}

JsonValue::JsonValue(const std::vector<JsonValue> &value)
  : type_(JsonType::Array), data_(new JsonArray(value)) {
}

JsonValue::JsonValue(const std::vector<bool> &value)
  : type_(JsonType::Array), data_(new JsonArray(value)) {
}

JsonValue::JsonValue(const std::vector<int> &value)
  : type_(JsonType::Array), data_(new JsonArray(value)) {
}

JsonValue::JsonValue(const std::vector<int64_t> &value)
  : type_(JsonType::Array), data_(new JsonArray(value)) {
}

JsonValue::JsonValue(const std::vector<double> &value)
  : type_(JsonType::Array), data_(new JsonArray(value)) {
}

JsonValue::JsonValue(const std::vector<std::string> &value)
  : type_(JsonType::Array), data_(new JsonArray(value)) {
}

JsonValue::JsonValue(const std::initializer_list<bool> &value)
  : type_(JsonType::Array), data_(new JsonArray(value)) {
}

JsonValue::JsonValue(const std::initializer_list<int> &value)
  : type_(JsonType::Array), data_(new JsonArray(value)) {
}

JsonValue::JsonValue(const std::initializer_list<int64_t> &value)
  : type_(JsonType::Array), data_(new JsonArray(value)) {
}

JsonValue::JsonValue(const std::initializer_list<double> &value)
  : type_(JsonType::Array), data_(new JsonArray(value)) {
}

JsonValue::JsonValue(const std::initializer_list<std::string> &value)
  : type_(JsonType::Array), data_(new JsonArray(value)) {
}

JsonValue::JsonValue(const std::initializer_list<const char *> &value)
  : type_(JsonType::Array),
    data_(new JsonArray(std::vector<std::string>(value.begin(), value.end()))) {
}

JsonValue::JsonValue(const JsonValue &other) {
  type_ = other.type_;
  switch (other.type_) {
    case JsonType::Null:
      break;
    case JsonType::Boolean:
      data_ = std::unique_ptr<JsonBool>(new JsonBool(*static_cast<JsonBool *>(other.data_.get())));
      break;
    case JsonType::Int:
    case JsonType::Long:
    case JsonType::Double:
      data_ = std::unique_ptr<JsonNumber>(
        new JsonNumber(*static_cast<JsonNumber *>(other.data_.get())));
      break;
    case JsonType::String:
      data_ = std::unique_ptr<JsonString>(
        new JsonString(*static_cast<JsonString *>(other.data_.get())));
      break;
    case JsonType::Array:
      data_ = std::unique_ptr<JsonArray>(
        new JsonArray(*static_cast<JsonArray *>(other.data_.get())));
      break;
    case JsonType::Object:
      data_ = std::unique_ptr<JsonObject>(
        new JsonObject(*static_cast<JsonObject *>(other.data_.get())));
      break;
  }
}
#else

JsonValue::JsonValue(JsonType type) : type_(type) {
  switch (type) {
    case JsonType::Null:
      break;
    case JsonType::Boolean:
      data_ = std::make_unique<JsonBool>();
      break;
    case JsonType::Int:
      data_ = std::make_unique<JsonNumber>(0);
      break;
    case JsonType::Long:
      data_ = std::make_unique<JsonNumber>(0L);
      break;
    case JsonType::Double:
      data_ = std::make_unique<JsonNumber>(0.0);
      break;
    case JsonType::String:
      data_ = std::make_unique<JsonString>();
      break;
    case JsonType::Array:
      data_ = std::make_unique<JsonArray>();
      break;
    case JsonType::Object:
      data_ = std::make_unique<JsonObject>();
      break;
  }
}

JsonValue::JsonValue(bool value)
  : type_(JsonType::Boolean), data_(std::make_unique<JsonBool>(value)) {
}

JsonValue::JsonValue(int value)
  : type_(JsonType::Int), data_(std::make_unique<JsonNumber>(value)) {
}

JsonValue::JsonValue(int64_t value)
  : type_(JsonType::Long), data_(std::make_unique<JsonNumber>(value)) {
}

JsonValue::JsonValue(double value)
  : type_(JsonType::Double), data_(std::make_unique<JsonNumber>(value)) {
}

JsonValue::JsonValue(const std::string &value)
  : type_(JsonType::String), data_(std::make_unique<JsonString>(value)) {
}

JsonValue::JsonValue(const char *value)
  : type_(JsonType::String), data_(std::make_unique<JsonString>(value)) {
}

JsonValue::JsonValue(const std::vector<JsonValue> &value)
  : type_(JsonType::Array), data_(std::make_unique<JsonArray>(value)) {
}

JsonValue::JsonValue(const std::vector<bool> &value)
  : type_(JsonType::Array), data_(std::make_unique<JsonArray>(value)) {
}

JsonValue::JsonValue(const std::vector<int> &value)
  : type_(JsonType::Array), data_(std::make_unique<JsonArray>(value)) {
}

JsonValue::JsonValue(const std::vector<int64_t> &value)
  : type_(JsonType::Array), data_(std::make_unique<JsonArray>(value)) {
}

JsonValue::JsonValue(const std::vector<double> &value)
  : type_(JsonType::Array), data_(std::make_unique<JsonArray>(value)) {
}

JsonValue::JsonValue(const std::vector<std::string> &value)
  : type_(JsonType::Array), data_(std::make_unique<JsonArray>(value)) {
}

JsonValue::JsonValue(const std::initializer_list<bool> &value)
  : type_(JsonType::Array), data_(std::make_unique<JsonArray>(value)) {
}

JsonValue::JsonValue(const std::initializer_list<int> &value)
  : type_(JsonType::Array), data_(std::make_unique<JsonArray>(value)) {
}

JsonValue::JsonValue(const std::initializer_list<int64_t> &value)
  : type_(JsonType::Array), data_(std::make_unique<JsonArray>(value)) {
}

JsonValue::JsonValue(const std::initializer_list<double> &value)
  : type_(JsonType::Array), data_(std::make_unique<JsonArray>(value)) {
}

JsonValue::JsonValue(const std::initializer_list<std::string> &value)
  : type_(JsonType::Array), data_(std::make_unique<JsonArray>(value)) {
}

JsonValue::JsonValue(const std::initializer_list<const char *> &value)
  : type_(JsonType::Array),
    data_(std::make_unique<JsonArray>(std::vector<std::string>(value.begin(), value.end()))) {
}

JsonValue::JsonValue(const JsonValue &other) {
  type_ = other.type_;
  switch (other.type_) {
    case JsonType::Null:
      break;
    case JsonType::Boolean:
      data_ = std::make_unique<JsonBool>(*static_cast<JsonBool *>(other.data_.get()));
      break;
    case JsonType::Int:
    case JsonType::Long:
    case JsonType::Double:
      data_ = std::make_unique<JsonNumber>(*static_cast<JsonNumber *>(other.data_.get()));
      break;
    case JsonType::String:
      data_ = std::make_unique<JsonString>(*static_cast<JsonString *>(other.data_.get()));
      break;
    case JsonType::Array:
      data_ = std::make_unique<JsonArray>(*static_cast<JsonArray *>(other.data_.get()));
      break;
    case JsonType::Object:
      data_ = std::make_unique<JsonObject>(*static_cast<JsonObject *>(other.data_.get()));
      break;
  }
}

#endif

JsonValue::JsonValue(JsonValue &&other) noexcept {
  type_ = other.type_;
  other.type_ = JsonType::Null;
  data_ = std::move(other.data_);
}

JsonValue &JsonValue::operator=(const JsonValue &value) {
  JsonValue(value).swap(*this);
  return *this;
}

JsonValue &JsonValue::operator=(JsonValue &&value) noexcept {
  JsonValue(std::move(value)).swap(*this);
  return *this;
}

void JsonValue::swap(JsonValue &other) {
  std::swap(type_, other.type_);
  std::swap(data_, other.data_);
}

JsonType JsonValue::getType() const {
  return type_;
}

bool JsonValue::isNull() const {
  return type_ == JsonType::Null;
}

bool JsonValue::isBoolean() const {
  return type_ == JsonType::Boolean;
}

bool JsonValue::isNumber() const {
  return type_ == JsonType::Int || type_ == JsonType::Long || type_ == JsonType::Double;
}

bool JsonValue::isInt() const {
  return type_ == JsonType::Int;
}

bool JsonValue::isLong() const {
  return type_ == JsonType::Long;
}

bool JsonValue::isDouble() const {
  return type_ == JsonType::Double;
}

bool JsonValue::isString() const {
  return type_ == JsonType::String;
}

bool JsonValue::isArray() const {
  return type_ == JsonType::Array;
}

bool JsonValue::isObject() const {
  return type_ == JsonType::Object;
}

bool JsonValue::asBoolean() const {
  if (!isBoolean()) throw type_error(type_, JsonType::Boolean);
  auto data = static_cast<JsonBool *>(data_.get());
  return data->getValue();
}

int JsonValue::asInt() const {
  if (!isInt()) throw type_error(type_, JsonType::Int);
  auto data = static_cast<JsonNumber *>(data_.get());
  return data->getInt();
}

int64_t JsonValue::asLong() const {
  auto data = static_cast<JsonNumber *>(data_.get());
  if (isLong()) {
    return data->getInt64();
  } else if (isInt()) {
    return data->getInt();
  }
  throw type_error(type_, JsonType::Long);
}

double JsonValue::asDouble() const {
  auto data = static_cast<JsonNumber *>(data_.get());
  if (isDouble()) {
    return data->getDouble();
  } else if (isInt()) {
    return data->getInt();
  }
  throw type_error(type_, JsonType::Double);
}

const std::string &JsonValue::asString() const {
  if (!isString()) throw type_error(type_, JsonType::String);
  auto data = static_cast<JsonString *>(data_.get());
  return data->getValue();
}

const std::vector<JsonValue> &JsonValue::asArray() const {
  if (!isArray()) throw type_error(type_, JsonType::Array);
  auto data = static_cast<JsonArray *>(data_.get());
  return data->getValue();
}

const JsonValue &JsonValue::asObject() const {
  if (!isObject()) throw type_error(type_, JsonType::Object);
  return *this;
}

JsonValue::operator bool() const {
  return asBoolean();
}

JsonValue::operator int() const {
  return asInt();
}

JsonValue::operator int64_t() const {
  return asLong();
}

JsonValue::operator double() const {
  return asDouble();
}

JsonValue::operator std::string() const {
  return asString();
}

JsonValue &JsonValue::operator[](const std::string &key) {
  if (isNull()) {
    setToObject();
  } else if (!isObject()) {
    throw type_error("operator[](std::string) can only be used by object type");
  }
  auto &data = *static_cast<JsonObject *>(data_.get());
  return data[key];
}

JsonValue &JsonValue::operator[](const char *key) {
  if (isNull()) {
    setToObject();
  } else if (!isObject()) {
    throw type_error("operator[](char *) can only be used by object type");
  }
  auto &data = *static_cast<JsonObject *>(data_.get());
  return data[key];
}

const JsonValue &JsonValue::operator[](const std::string &key) const {
  if (!isObject()) throw type_error("operator[](std::string) can only be used by object type");
  const auto &data = *static_cast<JsonObject *>(data_.get());
  return data[key];
}

const JsonValue &JsonValue::operator[](const char *key) const {
  if (!isObject()) throw type_error("operator[](char *) can only be used by object type");
  const auto &data = *static_cast<JsonObject *>(data_.get());
  return data[key];
}

JsonValue &JsonValue::operator[](std::size_t index) {
  if (!isArray()) throw type_error("operator[](std::size_t) can only be used by array type");
  auto &data = *static_cast<JsonArray *>(data_.get());
  return data[index];
}

const JsonValue &JsonValue::operator[](std::size_t index) const {
  if (!isArray()) throw type_error("operator[](std::size_t) can only be used by array type");
  const auto &data = *static_cast<JsonArray *>(data_.get());
  return data[index];
}

std::size_t JsonValue::size() const {
  switch (type_) {
    case JsonType::Null:
    case JsonType::Boolean:
    case JsonType::Int:
    case JsonType::Long:
    case JsonType::Double:
    case JsonType::String:
      return 0;
    case JsonType::Array:
      return static_cast<JsonArray *>(data_.get())->size();
    case JsonType::Object:
      return static_cast<JsonObject *>(data_.get())->size();
  }
  return 0;
}

bool JsonValue::empty() const {
  switch (type_) {
    case JsonType::Null:
    case JsonType::Boolean:
    case JsonType::Int:
    case JsonType::Long:
    case JsonType::Double:
    case JsonType::String:
      throw type_error("empty() can only be used by array or object type");
    case JsonType::Array:
      return static_cast<JsonArray *>(data_.get())->empty();
    case JsonType::Object:
      return static_cast<JsonObject *>(data_.get())->empty();
  }
  return true;
}

JsonIterator JsonValue::begin() {
  if (isArray()) {
    auto &data = *static_cast<JsonArray *>(data_.get());
    return JsonIterator(data.begin());
  } else if (isObject()) {
    auto &data = *static_cast<JsonObject *>(data_.get());
    return JsonIterator(data.begin());
  }
  return JsonIterator(*this);
}

JsonConstIterator JsonValue::begin() const {
  if (isArray()) {
    const auto &data = *static_cast<JsonArray *>(data_.get());
    return JsonConstIterator(data.begin());
  } else if (isObject()) {
    const auto &data = *static_cast<JsonObject *>(data_.get());
    return JsonConstIterator(data.begin());
  }
  return JsonConstIterator(*this);
}

JsonIterator JsonValue::end() {
  if (isArray()) {
    auto &data = *static_cast<JsonArray *>(data_.get());
    return JsonIterator(data.end());
  } else if (isObject()) {
    auto &data = *static_cast<JsonObject *>(data_.get());
    return JsonIterator(data.end());
  }
  return JsonIterator(type_);
}


JsonConstIterator JsonValue::end() const {
  if (isArray()) {
    const auto &data = *static_cast<JsonArray *>(data_.get());
    return JsonConstIterator(data.end());
  } else if (isObject()) {
    const auto &data = *static_cast<JsonObject *>(data_.get());
    return JsonConstIterator(data.end());
  }
  return JsonConstIterator(type_);
}

JsonIterator JsonValue::find(const std::string &key) {
  if (!isObject()) throw type_error("find(std::string) can only be used by object type");
  auto &data = *static_cast<JsonObject *>(data_.get());
  return JsonIterator(data.find(key));
}

JsonConstIterator JsonValue::find(const std::string &key) const {
  if (!isObject()) throw type_error("find(std::string) can only be used by object type");
  const auto &data = *static_cast<JsonObject *>(data_.get());
  return JsonConstIterator(data.find(key));
}

JsonIterator JsonValue::at(std::size_t index) {
  if (!isArray()) throw type_error("at(std::size_t) can only be used by array type");
  auto &data = *static_cast<JsonArray *>(data_.get());
  if (index >= data.size()) {
    return JsonIterator(data.end());
  }
  auto it = data.begin();
  it += index;
  return JsonIterator(it);
}

JsonConstIterator JsonValue::at(std::size_t index) const {
  if (!isArray()) throw type_error("at(std::size_t) can only be used by array type");
  const auto &data = *static_cast<JsonArray *>(data_.get());
  if (index >= data.size()) {
    return JsonConstIterator(data.end());
  }
  auto it = data.begin();
  it += index;
  return JsonConstIterator(it);
}

void JsonValue::reset() {
  type_ = JsonType::Null;
  data_.reset(nullptr);
}

void JsonValue::clear() {
  if (isArray()) {
    static_cast<JsonArray *>(data_.get())->clear();
  } else if (isObject()) {
    static_cast<JsonObject *>(data_.get())->clear();
  } else {
    type_ = JsonType::Null;
    data_.reset(nullptr);
  }
}

bool JsonValue::push_back(const std::string &key, const JsonValue &value) {
  if (isNull()) {
    setToObject();
  } else if (!isObject()) {
    throw type_error("push_back(std::string, JsonValue) can only be used by object type");
  }
  auto &data = *static_cast<JsonObject *>(data_.get());
  return data.insert(key, value);
}

bool JsonValue::push_back(const std::string &key, JsonValue &&value) {
  if (isNull()) {
    setToObject();
  } else if (!isObject()) {
    throw type_error("push_back(std::string, JsonValue) can only be used by object type");
  }
  auto &data = *static_cast<JsonObject *>(data_.get());
  return data.insert(key, std::move(value));
}

void JsonValue::push_back(const JsonValue &value) {
  if (isNull()) {
    setToArray();
  } else if (!isArray()) {
    throw type_error("push_back(JsonValue) can only be used by array type");
  }
  auto &data = *static_cast<JsonArray *>(data_.get());
  data.push_back(value);
}

void JsonValue::push_back(JsonValue &&value) {
  if (isNull()) {
    setToArray();
  } else if (!isArray()) {
    throw type_error("push_back(JsonValue) can only be used by array type");
  }
  auto &data = *static_cast<JsonArray *>(data_.get());
  data.push_back(std::move(value));
}

JsonIterator JsonValue::insert(JsonConstIterator pos, const JsonValue &value) {
  if (!isArray())
    throw type_error("insert(JsonConstIterator,JsonValue) can only be used by array type");
  if (pos.type_ != type_) throw type_error("Insert type mismatch");
  auto &data = *static_cast<JsonArray *>(data_.get());
  return JsonIterator(data.insert(pos.array_iter_, value));
}

JsonIterator JsonValue::insert(JsonConstIterator pos, JsonValue &&value) {
  if (!isArray())
    throw type_error("insert(JsonConstIterator,JsonValue) can only be used by array type");
  if (pos.type_ != type_) throw type_error("Insert type mismatch");
  auto &data = *static_cast<JsonArray *>(data_.get());
  return JsonIterator(data.insert(pos.array_iter_, std::move(value)));
}

JsonIterator JsonValue::erase(JsonConstIterator pos) {
  if (pos.type_ != type_) throw type_error("Erase type mismatch");
  if (isArray()) {
    auto &data = *static_cast<JsonArray *>(data_.get());
    return JsonIterator(data.erase(pos.array_iter_));
  } else if (isObject()) {
    auto &data = *static_cast<JsonObject *>(data_.get());
    return JsonIterator(data.erase(pos.object_iter_));
  }
  throw type_error("erase(JsonConstIterator) can only be used by array or object type");
}

bool JsonValue::erase(const std::string &key) {
  return removeMember(key);
}

bool JsonValue::isMember(const std::string &key) const {
  if (!isObject()) throw type_error("isMember(std::string) can only be used by object type");
  const auto &data = *static_cast<JsonObject *>(data_.get());
  return data.find(key) != data.end();
}

bool JsonValue::removeMember(const std::string &key) {
  if (!isObject()) throw type_error("isMember(std::string) can only be used by object type");
  auto &data = *static_cast<JsonObject *>(data_.get());
  return data.erase(key) != 0;
}

std::string JsonValue::toString() const {
  if (isNull()) {
    static const std::string null("null");
    return null;
  }
  return data_->toString();
}

std::ostream &JsonValue::toDumpStream(std::ostream &out) const {
  if (isNull()) {
    out << "null";
    return out;
  }
  return data_->toDumpStream(out);
}

std::ostream &operator<<(std::ostream &out, const JsonValue &value) {
  return value.toDumpStream(out);
}

#if __cplusplus < 201402L
void JsonValue::setToObject() {
  type_ = JsonType::Object;
  data_ = std::unique_ptr<JsonObject>(new JsonObject());
}

void JsonValue::setToArray() {
  type_ = JsonType::Object;
  data_ = std::unique_ptr<JsonArray>(new JsonArray());
}
#else

void JsonValue::setToObject() {
  type_ = JsonType::Object;
  data_ = std::make_unique<JsonObject>();
}

void JsonValue::setToArray() {
  type_ = JsonType::Object;
  data_ = std::make_unique<JsonArray>();
}

#endif

} // suger