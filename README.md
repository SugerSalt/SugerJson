# SugerJson
一个轻量级的Json解析库

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
2. useJson实现了Json的创建和是哦嗯样例。

## 问题与计划

### 20230810

1. 不支持空数组与空object的解析
2. 不支持注释的解析