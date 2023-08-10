// Copyright (c) 2023. SugerSalt

#include <iostream>
#include "JsonValue.hpp"
#include "JsonError.hpp"

using namespace std;

int main() {
  suger::JsonValue json1;
  json1["intValue"] = 123;
  json1["longValue"] = 123456789012345L;
  json1["string"] = "String value";
  json1["array"] = {1, 2, 3};
  json1["object"]["a"] = 1;
  json1["object"]["b"] = "2";
  cout << json1 << endl;
  cout << "json1.isObject(): " << json1.isObject() << endl;
  cout << "json1.isMember(\"string\"): " << json1.isMember("string") << endl;
  cout << "json1.isMember(\"suger\"): " << json1.isMember("suger") << endl;
  cout << "json1[\"array\"][1]: " << json1["array"][1] << endl;
  cout << "json1[\"object\"].isMember(\"a\"): " << json1["object"].isMember("a") << endl;
  json1["object"].removeMember("a");
  cout << "json1[\"object\"].isMember(\"a\"): " << json1["object"].isMember("a") << endl;
  cout << "-------------------------------------" << endl;

  for (auto &itme: json1) {
    cout << itme << endl;
  }
  cout << "-------------------------------------" << endl;

  for (auto it = json1.begin(); it != json1.end(); ++it) {
    cout << it.key() << ": " << it.value() << endl;
  }
  cout << "-------------------------------------" << endl;

  suger::JsonValue json2 = std::move(json1);
  cout << "json1.isNull() : " << json1.isNull() << endl;
  cout << "json2.isObject() : " << json2.isObject() << endl;

  auto printInt = [](int x) { cout << x << endl; };
  printInt(json2["intValue"]);
  json2.push_back("intValue2", 5);
  printInt(json2["intValue2"]);
  return 0;
}
