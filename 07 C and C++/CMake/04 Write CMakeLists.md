在上面的介绍中，我们已经知道，对于一个最基本的 `CMakeLists.txt` 文件，我们必须包括以下命令：
- `CMake` 最小版本指定
- 设置项目名称
- 生成目标可执行文件

接下来，我们将讲讲更适合于一般项目的编写规则

# 01 设置变量优化指令

若习惯将目标可执行文件的名称设置为项目的名称，则可以：

```CMake
add_executable (${PROJECT_NAME} main.cpp)
```

若由多个源文件生成一个可执行文件，则可以：

```CMake
set (SRC_LIST a.cpp b.cpp c.cpp)
add_executable (${PROJECT_NAME} ${SRC_LIST})
```

若源文件分多个文件存放，则可以通过 `aux_source_directory ()` 来获取一个目录下的所有文件，并存储于变量中

```CMake
aux_source_directory (<dir> <variable_name>)

aux_source_directory (/mylib SRC_LIST)
add_executable (${PROJECT_NAME} main.cpp ${SRC_LIST})
```

# 02 指定 C++版本

我们在编写的时候可以指定 C++ 的编译版本。注意，从 GCC/G++ 6.1 开始，当不指定任何 C++ 版本标准时，默认版本为 c++14

```CMake
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED TRUE)
```

# 03 添加库

一个中等大小的项目，一般会有自己所编写的库，这个时候，我们便需要将自己编写的库纳入编译中

## 3.1 生成目标库

要想向项目中添加一个自建库，首先要将自己的源码编译成库文件。生成一个库可以在根目录下的 `CMakeLists.txt` 中构建该库，但是，我们更倾向于在子模块中重新编写 `CMakeLists.txt` 文件，使整个项目更加有条理

生成库的命令为 `add_library (<lib_name> [SHARED|STATIC|MOUDLE] <source>)`，其中：
- `<lib_name>` : 为指定的库名，这与使用 g++ 命令行生成库不同，g++ 需要将整个库名写完整，如 `g++ mathfunc.cpp -Iinclude -c -o libmathfunc.a` ，而CMake中只需要写我们调用时的库名 `mathfunc`  ^a4c4bc
- `[SHARED|STATIC|MOUDLE]` 为生成的库的属性，默认为 `STATIC` 
- `<source>` 是用于生成库的目标源文件

假设我们有这样一个项目：

```CMake
HELLO_WORLD
	|__ CMakeLists.txt
	|__ MathFunctions
	|	|__ CMakeLists.txt
	|	|__ include
	|		|__ mathfunc.h
	|	|__src
	|		|__ mathfunc.cpp
	|__ main.cpp
```

则在 `HELLO_WORLD/MathFunctions/CMakeLists.txt` 中应该写入：

```CMake
add_library (mathfunc ./src/mathfunc.cpp)
target_include_directories (mathfunc PUBLIC ./include)
```

- `add_library` 设置以 `mathfunc.cpp` 文件生成名为 `mathfunc` 的 **静态库** 
- `target_include_directory (<target> <PUBLIC|PRIVATE|INTERFACE> <source>)`  用于 **将头文件所在的路径与该项目绑定** 
	- `target` 表示需要被链接的目标文件
	- `PUBLIC|PRIVATE|INTERFACE` 为链接的方式
		- `PUBLIC` 表示共享该包含目录
		- `PRIVATE` 表示该包含目录为私有的
		- `INTERFACE` 表示该库文件为接口库，没有具体的实现文件
	- `source` 是用于生成库文件的源文件

当我们在子模块中的 `CMakeLists.txt` 中编写好库的生成规则时，还需要将子模块添加到整个项目中，这样构建项目的时候才能根据子模块中的 `CMakeLists.txt` 文件对子模块进行构建。我们应该在 `HELLO_WORLD/CMakeLists.txt` 中写到：

```CMake
add_subdirectory (MathFunctions)
```

这样，子模块 `MathFunctions` 就会在构建整个项目的时候被找到并进行构建

## 3.2 链接可执行文件和目标库

可执行文件想要使用库文件，需要将 **库文件** 和 **对应的头文件** 与该可执行文件链接起来，这个时候需要用到 `target_include_directories ()` 和 `target_link_libraries ()` 。链接库文件需要 **依据库文件链接头文件的方式** 分为两种情况： `PUBLIC` or `PRIVATE` 

#### 1. `PRIVATE` 链接

当库文件链接头文件时选择的是 `PRIVATE` 属性，表示该链接是 **私有于该目标的属性** ，其他目标在链接当前目标的时候， **无法访问该属性** ，这时我们需要包含这些头文件，才能在主函数中调用该库：

```CMake
# HELLO_WORLD/MathFunctions/CMakeLists.txt
add_library (mathfunc ./src/mathfunc.cpp)
target_include_directories (mathfunc PRIVATE ./include)

# HELLO_WORLD/CMakeLists.txt
cmake_minimum_required (VERSION 3.10)
project (HELLO_WORLD)

add_subdirectory (MathFunctions)

add_executable (main main.cpp)
target_include_directories (main PRIVATE ./MathFunctions/include)
target_link_libraries (main mathfunc)
```

#### 2. `PUBLIC` 链接

当库文件链接头文件时选择的是 `PUBLIC` 属性，表示该链接是 **该目标的公有属性** ，其他目标在链接当前目标的时候，当前目标会共享该属性，即其他目标 **能够直接访问该目标所绑定的头文件** ：

```CMake
# HELLO_WORLD/MathFunctions/CMakeLists.txt
add_library (mathfunc ./src/mathfunc.cpp)
target_include_directories (mathfunc PUBLIC ./include)

# HELLO_WORLD/CMakeLists.txt
cmake_minimum_required (VERSION 3.10)
project (HELLO_WORLD)

add_subdirectory (MathFunctions)

add_executable (main main.cpp)
target_link_library (main mathfunc)
```

# 04 编译

在一般编译中，我们选择在项目的根目录下新建 `build` 文件夹用于存放编译信息和编译产物，项目 `HELLO_WORLD` 的 `build` 目录为：

```
build
	├── CMakeCache.txt
	├── CMakeFiles/
	├── cmake_install.cmake
	├── main*
	├── Makefile
	└── MathFunctions/
		├── CMakeFiles
		├── cmake_install.cmake
		├── libmathfunc.a
		└── Makefile
```

- `CMakeCache.txt` 为存放缓存变量，编译信息的文件 
- `Makefile` 为根据顶级 `CMakeLists.txt` 文件生成的含有构建规则的文件， `make` 将根据该文件中的规则对项目进行构建
- `main*` 为生成的可执行文件
- `CMakeFiles/` 为存放中间编译文件的目录
- `cmake_install.cmake` 是用于设置 **目标安装** 的配置文件
- `MathFunctions/` 为子模块(子目录)的编译文件
	- `libmathfunc.a` 为根据该模块中的源文件生成的 **静态库** 

# 05 编译命令
## 5.1 默认编译

我们一般选择使用外部构建的方式来编译项目。

```bash
cd build
cmake ..
make
```

## 5.2 设置编译工具

CMake 可以生成许多用于不同编译工具的编译文件，如 `mingw` , `make` , `ninjia` `msvc` 等等，我们可以通过 `-G` 选项来设置编译工具 : 

```bash
cd build
cmake -G "Unix Makefiles" ..
cmake -G "Ninjia" ..
cmake -G "MinGW Makefiles" ..
make
```

而在 Windows 系统下， `cmake ..` 默认生成适用 Visual Studio 编译器的编译文件。

## 5.3 设置编译选项

我们可以通过 `-D` 选项来设置编译选项，常见的如 : 

```bash
cd build
cmake -D CMAKE_BUILD_TYPE=Release
```

## 5.4 添加宏定义

我们可以通过向CMake项目中添加某些特定的宏定义来实现条件编译。

```bash
cd build
cmake -DWITH_A -DBUILD_TEST=0001 ..
```

除了向 CMake 项目中添加宏定义，我们也可以在 `CMakeLists.txt` 文件中通过 `add_compile_definitions ()` 来向 C++ 源文件添加宏定义，见 [add_compile_definitions](CMake%20Commands.md##14.%20`add_compile_definitions%20()`) 

> [!attention] 
> 这里的宏定义并**不是指同一个宏定义**！
> 
> - 前者是 CMake 项目中的宏定义，实际上也就是 CMake 项目中的变量，用于控制 CMake 项目中 Makefiles 的编写
> - 后者指的是 C++ 源文件中的宏定义，是要添加到 `.cpp` 文件中的 macro 

