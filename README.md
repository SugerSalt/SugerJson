# SugerJson
一个轻量级的Json解析库

## 依赖

程序使用CMake进行构建，编译器最低应支持C++11语法，推荐使用C++17以上版本。程序所有代码只依赖SLT，未使用其他任何外部库。

## 构建
```shell
mkdir _build
cd _build
cmake .. -DBUILD_EXAMPLE=OFF # -DBUILD_EXAMPLE 控制是否构建样例程序
make
```

在cmake步骤中一共有四个选项：
1. -DBUILD_SHARED_LIBS 是否构建动态库 默认为ON
2. -DBUILD_STATIC_LIBS 是否构建静态库 默认为ON
3. -DBUILD_CMAKE_PACKAGE 是否构建CMake导出包 默认为ON
4. -DBUILD_EXAMPLE 是否构建样例程序 默认为OFF，其依赖-DBUILD_SHARED_LIBS

上述步骤完成后，可以在`_build/result`目录下获得产出

其中`lib`中为库文件，`bin`中为样例程序，`include`中为导出头文件

## 样例程序

如果设置了`-DBUILD_EXAMPLE=ON`，则可以在`_build/result/bin`中找到两个样例程序

1. readJson实现了简单的Json解析样例，其可以从字符串或者流中读取。使用`./_build/result/bin/readJson ./_build/result/bin/readJson.json`从一个文件解析Json。
2. useJson实现了Json的创建和使用样例。

## 使用方法

### json解析
```c++
// 引入json解析头文件
#include "JsonReader.hpp"
```

SugerJaon可以解析注释，但不存储任何注释信息，即所有注释将直接被忽略

#### 从字符串解析
```c++
std::string jsonStr = R"({
    "intValue": 123,
    "stringValue": "This is \"SugerJson\"",
    "array": [1, 2, 3]
})";

// json解析类
suger::JsonReader reader;
// 直接获得返回值
auto json = reader.parse(jsonStr);
// 传参解析
suger::JsonValue json;
reader.parse(jsonStr, json);  // 返回解析是否成功
```

#### 从流中解析
```c++
std::ifstream fin("/path/to/json");
// json解析类
suger::JsonReader reader;
// 直接获得返回值
auto json = reader.parse(fin);
// 使用>>
fin >> json;
// 传参解析
suger::JsonValue json;
reader.parse(fin, json);  // 返回解析是否成功
```

#### 解析异常

如果解析发生错误将产生`suger::parse_error`异常
```c++
suger::JsonValue json;
try {
  json = reader.parse(jsonStr);
} catch (suger::parse_error &e) {
  std::cout << e.what() << std::endl;
}
```

### json使用
```c++
// 引入json头文件
#include "JsonValue.hpp"
using namespace suger;
```

#### 创建json变量
```c++
JsonValue json;  // 创建一个空json，即Null
JsonValue json(JsonType::Object);  // 传入JsonType，创建指定类型的json
JsonValue json("this is string");  // 创建指定类型json，并赋值
JsonValue json = "this is string";  // 同上等价
JsonValue json = {1, 2, 3};  // 可以使用初始化列表创建Array类型json
JsonValue json = jsonOld;  // 从其他json拷贝
JsonValue json = std::move(jsonOld);  // 从其他json移动构造，这之后jsonOld变为空
```

#### json类型判断
```c++
getType();  // 获得json类型
isNull();
isBoolean();
isNumber();
isInt();
isLong();
isDouble();
isString();
isArray();
isObject();
```

#### json类型转换
```c++
// 将json转换为指定类型
asBoolean();
asInt();
asLong();  // Int类型会被隐式转换
asDouble();  // Int类型会被隐式转换
asString();
asArray();
asObject();  // 如果是Object类型，返回的是本身

// 如果转换类型与自身类型不匹配，则会抛出type_error异常
suger::JsonValue json = 1;  // Int类型
try {
  std::string str = json.asString();  // 解析为String类型，会报异常
} catch (type_error &e) {
  std::cout << e.what() << std::endl;
}

// 隐式转换
// json变量可以向bool、int、long、double、std::string自动隐式转换
auto printInt = [](int x){std::cout << x << std::endl; };
suger::JsonValue json = 1;
printInt(json);  // 隐式转换类型不匹配，同样会抛出type_error异常
```

#### 查找
```c++
// 查找方法是针对Object类型与Array类型
std::string jsonStr = R"({
    "intValue": 123,
    "stringValue": "This is \"SugerJson\"",
    "array": [1, 2, 3]
})";
JsonValue json = reader.parse(jsonStr);

// 使用[]进行访问
// Object类型：使用键访问
json["intValue"]  // 123
JsonValue& jsonArray = json["array"];  // 注意如果不使用引用获取会发生拷贝
json["newValue"] = true;  // 如果键不存在会自动创建
// Array类型：使用下标访问
jsonArray[1]  // 2
jsonArray[3]  // 下标越界会报异常

// 迭代器访问
json.begin();  // 获得开始位置的迭代器
json.end();  // 获得末尾位置的迭代器
json.find("intValue");  // Object类型，获得指定键的迭代器，不存在的键会返回end()
jsonArray.at(1);  // Array类型，获得指定下标的迭代器，越界会返回end()

json.isMember("intValue");  // Object类型，判断是否含有指定键
json.size();  // 大小，Object与Array返回对应大小，其他类型返回0
json.empty();  // 是否为空，只能Object与Array类型
```

#### 修改
```c++
// 插入
json.push_back("newIntValue", 456);  // Object类型，插入键值
// 上述等价于 json["newIntValue"] = 456; 但效率更高
jsonArray.push_back(4);  // Array类型，在末尾插入值

// 迭代器插入
auto it = jsonArray.at(1);
jsonArray.insert(it, 5);  // Array类型，在指定迭代器位置前插入值

// 删除
json.erase("intValue");  // Object类型，删除指定键，返回是否成功
jsonArray.erase(it);  // Object与Array类型，删除迭代器位置，返回删除位置的下一个位置的迭代器
json.removeMember("intValue");  // 等价于json.erase("intValue")

// 清除
json.reset();  // 重置json为Null
json.clear();  // Object与Array类型则清空存储的值，其他类型则重置为Null

// 交换
json.swap(otherJson);  // 与其他json交换，分别获得对方的类型与值
```

#### 显示
```c++
json.toString();  // 无论类型都转换为字符串
json.toDumpStream(std::cout);  // 格式化输出到流中，String类型可能会添加转译字符
std::cout << json;  // 和上述代码等价
```

### 迭代器

SugerJson完全支持C++风格的迭代器。

该迭代器属于向前迭代器，即只支持`++`操作。

```c++
std::string jsonStr = R"({
    "intValue": 123,
    "stringValue": "This is \"SugerJson\"",
    "array": [1, 2, 3]
})";
JsonValue json = reader.parse(jsonStr);

// 遍历Object
for (auto it = json.begin(); it != json.end(); ++it) {
  std::cout << "key: " << it.key() << " value: " << it.value() << std::endl;
  // 使用*也可以访问value  *it == it.value()
  // 使用->可以直接调用value的函数  it->isInt() == it.value().isInt()
}
// foreach遍历Object只能获得值
for (auto &item : json) {
  std::cout << "value: " << item.toString() << std::endl;
}

auto& jsonArray = json["array"];
// 遍历Array
for (auto it = jsonArray.begin(); it != jsonArray.end(); ++it) {
  std::cout << "value: " << it.value() << std::endl;
  // Array的it.key()永远返回空串
}
// foreach遍历
for (auto &item : jsonArray) {
  std::cout << "value: " << item.toString() << std::endl;
}

// 事实上非Object和Array也可以使用迭代器，不过这样的写法没有太大意义
auto& jsonInt = json["intValue"];
for (auto it = jsonInt.begin(); it != jsonInt.end(); ++it) {
  std::cout << "value: " << it.value() << std::endl;
}
```

### 异常

SugerJaon会产生三种异常
1. parse_error  json解析异常
2. type_error   类型异常，类型转换错误或者调用了不属于该类型的函数
3. key_error    键异常，使用[]访问json常量时键不存在

## 问题与计划

### 20230810

1. ~~不支持空数组与空object的解析~~
2. ~~不支持注释的解析~~（解析时直接忽略注释）