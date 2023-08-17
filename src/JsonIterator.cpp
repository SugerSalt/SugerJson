// Copyright (c) 2023. SugerSalt

#include "JsonValue.hpp"

namespace suger {
JsonIterator::JsonIterator(JsonType type) : type_(type), value_(nullptr) {

}

JsonIterator::JsonIterator(JsonValue &value) : type_(value.type_), value_(&value) {

}

JsonIterator::JsonIterator(const std::vector<JsonValue>::iterator &value)
  : type_(JsonType::Array), value_(nullptr), array_iter_(value) {

}

JsonIterator::JsonIterator(const ObjectIterator &value)
  : type_(JsonType::Object), value_(nullptr), object_iter_(value) {

}

JsonIterator::JsonIterator(const JsonIterator &other)
  : type_(other.type_), value_(other.value_), array_iter_(other.array_iter_),
    object_iter_(other.object_iter_) {

}

JsonIterator::JsonIterator(JsonIterator &&other) noexcept
  : type_(other.type_), value_(other.value_),
    array_iter_(other.array_iter_),
    object_iter_(other.object_iter_) {
  other.type_ = JsonType::Null;
  other.value_ = nullptr;
}

JsonIterator &JsonIterator::operator=(const JsonIterator &other) {
  type_ = other.type_;
  value_ = other.value_;
  array_iter_ = other.array_iter_;
  object_iter_ = other.object_iter_;
  return *this;
}

JsonIterator &JsonIterator::operator=(JsonIterator &&other) noexcept {
  type_ = other.type_;
  value_ = other.value_;
  array_iter_ = other.array_iter_;
  object_iter_ = other.object_iter_;
  other.type_ = JsonType::Null;
  other.value_ = nullptr;
  return *this;
}

JsonValue &JsonIterator::operator*() const {
  if (type_ == JsonType::Array) {
    return *array_iter_;
  } else if (type_ == JsonType::Object) {
    return object_iter_->second;
  }
  return *value_;
}

JsonValue *JsonIterator::operator->() const {
  if (type_ == JsonType::Array) {
    return &(*array_iter_);
  } else if (type_ == JsonType::Object) {
    return &(object_iter_->second);
  }
  return value_;
}

JsonIterator &JsonIterator::operator++() {
  if (type_ == JsonType::Array) {
    ++array_iter_;
  } else if (type_ == JsonType::Object) {
    ++object_iter_;
  } else {
    value_ = nullptr;
  }
  return *this;
}

JsonIterator JsonIterator::operator++(int) {
  JsonIterator tmp(*this);
  if (type_ == JsonType::Array) {
    ++array_iter_;
  } else if (type_ == JsonType::Object) {
    ++object_iter_;
  } else {
    value_ = nullptr;
  }
  return tmp;
}

bool JsonIterator::operator==(const JsonIterator &rhs) const {
  if (type_ != rhs.type_) return false;
  if (type_ == JsonType::Array) {
    return array_iter_ == rhs.array_iter_;
  } else if (type_ == JsonType::Object) {
    return object_iter_ == rhs.object_iter_;
  }
  return value_ == rhs.value_;
}

bool JsonIterator::operator!=(const JsonIterator &rhs) const {
  return !((*this) == rhs);
}

const std::string &JsonIterator::key() const {
  if (type_ == JsonType::Object) {
    return object_iter_->first;
  }
  static const std::string nullKey;
  return nullKey;
}

JsonValue &JsonIterator::value() const {
  return operator*();
}

JsonConstIterator::JsonConstIterator(JsonType type) : type_(type), value_(nullptr) {

}

JsonConstIterator::JsonConstIterator(const JsonValue &value) : type_(value.type_), value_(&value) {

}

JsonConstIterator::JsonConstIterator(const std::vector<JsonValue>::const_iterator &value)
  : type_(JsonType::Array), value_(nullptr), array_iter_(value) {

}

JsonConstIterator::JsonConstIterator(const ObjectConstIterator &value)
  : type_(JsonType::Object), value_(nullptr), object_iter_(value) {

}

JsonConstIterator::JsonConstIterator(const JsonConstIterator &other)
  : type_(other.type_), value_(other.value_), array_iter_(other.array_iter_),
    object_iter_(other.object_iter_) {

}

JsonConstIterator::JsonConstIterator(const JsonIterator &other)
  : type_(other.type_), value_(other.value_), array_iter_(other.array_iter_),
    object_iter_(other.object_iter_) {
}

JsonConstIterator::JsonConstIterator(JsonConstIterator &&other) noexcept
  : type_(other.type_), value_(other.value_),
    array_iter_(other.array_iter_),
    object_iter_(other.object_iter_) {
  other.type_ = JsonType::Null;
  other.value_ = nullptr;
}

JsonConstIterator &JsonConstIterator::operator=(const JsonConstIterator &other) {
  type_ = other.type_;
  value_ = other.value_;
  array_iter_ = other.array_iter_;
  object_iter_ = other.object_iter_;
  return *this;
}

JsonConstIterator &JsonConstIterator::operator=(const JsonIterator &other) {
  type_ = other.type_;
  value_ = other.value_;
  array_iter_ = other.array_iter_;
  object_iter_ = other.object_iter_;
  return *this;
}

JsonConstIterator &JsonConstIterator::operator=(JsonConstIterator &&other) noexcept {
  type_ = other.type_;
  value_ = other.value_;
  array_iter_ = other.array_iter_;
  object_iter_ = other.object_iter_;
  other.type_ = JsonType::Null;
  other.value_ = nullptr;
  return *this;
}

const JsonValue &JsonConstIterator::operator*() const {
  if (type_ == JsonType::Array) {
    return *array_iter_;
  } else if (type_ == JsonType::Object) {
    return object_iter_->second;
  }
  return *value_;
}

const JsonValue *JsonConstIterator::operator->() const {
  if (type_ == JsonType::Array) {
    return &(*array_iter_);
  } else if (type_ == JsonType::Object) {
    return &(object_iter_->second);
  }
  return value_;
}

JsonConstIterator &JsonConstIterator::operator++() {
  if (type_ == JsonType::Array) {
    ++array_iter_;
  } else if (type_ == JsonType::Object) {
    ++object_iter_;
  } else {
    value_ = nullptr;
  }
  return *this;
}

JsonConstIterator JsonConstIterator::operator++(int) {
  JsonConstIterator tmp(*this);
  if (type_ == JsonType::Array) {
    ++array_iter_;
  } else if (type_ == JsonType::Object) {
    ++object_iter_;
  } else {
    value_ = nullptr;
  }
  return tmp;
}

bool JsonConstIterator::operator==(const JsonConstIterator &rhs) const {
  if (type_ != rhs.type_) return false;
  if (type_ == JsonType::Array) {
    return array_iter_ == rhs.array_iter_;
  } else if (type_ == JsonType::Object) {
    return object_iter_ == rhs.object_iter_;
  }
  return value_ == rhs.value_;
}

bool JsonConstIterator::operator!=(const JsonConstIterator &rhs) const {
  return !((*this) == rhs);
}

const std::string &JsonConstIterator::key() const {
  if (type_ == JsonType::Object) {
    return object_iter_->first;
  }
  static const std::string nullKey;
  return nullKey;
}

const JsonValue &JsonConstIterator::value() const {
  return operator*();
}


} // suger