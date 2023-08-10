// Copyright (c) 2023. SugerSalt

#include <iostream>
#include <fstream>
#include "JsonValue.hpp"
#include "JsonReader.hpp"
#include "JsonError.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  string str = R"({
  "intValue": 123,
  "longValue": 123456789012345,
  "stringValue": "This is \"SugerJson\"",
  "array": [1, 2, 3],
  "stringArray": ["1", "2", "3"],
  "object": {
    "a": 3,
    "b": [
      {
        "id": 1,
        "name": "first"
      },
      {
        "id": 2,
        "name": "second"
      }
    ]
  }
})";
  suger::JsonReader reader;
  auto json = reader.parse(str);
  cout << json << endl;
  if (argc > 1) {
    cout << "--------------------------------------" << endl;
    suger::JsonValue j2;
    fstream fin(argv[1]);
    if (fin.is_open()) {
      try {
        reader.parse(fin, j2);
        cout << j2 << endl;
      } catch (suger::parse_error &e) {
        cerr << e.what() << endl;
      }
    }
  }
  return 0;
}
