# 1. `cmake_minimum_required ()`

用于指定构建工具 CMake 的最小版本要求

```CMake
cmake_minimum_required (VERSION <version>)
cmake_minimum_required (VERSION 3.10)
```

# 2. `project ()`

用于定义工程的名称，版本和支持的语言

```CMake
project (<project_name> [VERSION <version>] [language])
project (HELLO_WORLD)
project (HELLO_WORLD VERSION 1.0)
project (HELLO_WORLD VERSION 1.0 C++)
```

- `<project_name>` 会存贮在环境变量 `PROJECT_NAME` 中
- `[language]` 默认为 C/C++

# 3. `set ()` and `unset ()`

用于[定义变量和解除变量](05%20CMake%20Program#01%20变量) 

```CMake
set (<variable_name> <value>)
unset (<variable_name>)

set (<variable_name> <value> CACHE <type> [discription] [FORCE])
unset (<variable_name> CACHE)
```

## 4. `include_directories ()` 

向工程添加多个特定的头文件路径

```CMake
include_directories (<path>)
```

## 5. `link_directories ()` 

向工程添加多个特定的库文件路径

```CMake
link_directories (<path>)
```

## 6. `add_library ()` 

[构建库文件](06%20Build#02%20库文件的构建) 

```CMake
add_library (<lib_name> [SHARED|STATIC|MOUDLE] <source>)
```

## 7. `add_compile_options ()` 

添加编译参数

```CMake
add_compile_options (<option>)
add_compile_options (-Wall -std=c++11 -O2)
```

## 8. `add_executable ()` 

[构建可执行文件](06%20Build#01%20可执行文件的构建) 

```CMake
add_executable (<exe_name> <source>)
```

## 9. `target_link_libraries ()`

[为target添加需要链接的库](04%20Write%20CMakeLists#3.2%20链接可执行文件和目标库) 

```CMake
target_link_libraries (<target> <lib>)
```

## 10. `target_include_directories ()` 

[为target添加头文件路径](04%20Write%20CMakeLists#3.1%20生成目标库) 

```CMake
target_include_directories (<target> <PUBLIC|PRIVATE|INTERFACE> <path>)
```

## 11. `add_subdirectory ()`

向CMake项目中添加子模块

```CMake
add_subdirectory (<path>)
```

> 注意：
> 子模块中必须包含 `CMakeLists.txt` 文件

## 12. `aux_source_directory ()` 

发现一个目录下所有源代码文件并将其存储在一个变量中

```CMake
aux_source_directory (<path> <variable_name>)

aux_source_directory (. SRC)
add_executable (main ${SRC})
```

## 13. `message ()` 

在配置 `CMake` 项目时向终端输出信息。

```CMake
cmake_minimum_required (VERSION 3.10)
project (hello)

add_executable (main main.cpp)

message ("Configure the project successfully !")
```

## 14. `add_compile_definitions ()` 

在编译 `CMake` 项目时向工程中添加 **宏定义** ，可用于条件编译开启或关闭某一功能。

```CMake
add_compile_definitions (<your_definition>[=<value>])

add_compile_definitions (WITH_A)
# 向项目添加 #define WITH_A 的宏定义

add_compile_definitions (BUILD_TEST=0001)
# 向项目添加 #define BUILD_TEST 0001 的宏定义
```

