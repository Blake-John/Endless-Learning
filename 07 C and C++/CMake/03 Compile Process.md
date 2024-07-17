`CMake` 的编译流程与 C/C++ 的编译流程息息相关，因此我们应熟悉 gcc/g++ 的使用

# 01 C++ 编译流程

C++ 基本编译流程为 **预处理** ， **编译汇编** ， **链接** ，详情可见：
- [How C++ Work ?](../C++/01%20Basic/02.How%20C++%20Work.md#2.2%20The%20Steps%20to%20Build%20a%20Executable%20File)
- [编译](../环境/Cpp环境配置及编译器使用#1.1%20编译)

# 02 CMake工程

CMake工程由 **源文件** ， **CMakeLists.txt** ， **编译信息** 组成。其中，我们需要关注的便是如何根据已有的源文件来编写 `CMakeLists.txt` 文件，并利用其进行编译

## 2.1 基本目录结构

1. 简单的目录结构：
最小的CMake工程由单一源文件组成，简单的CMake工程由多个简单的源文件组成，并且这些源文件存放于同一目录下。这时，我们只需要一个 `CMakeLists.txt` 来进行工程的编译，这种工程的目录一般为：

```
project
	|__ build
	|__ main.cpp
	|__ CMakeLists.txt
```

或者是

```
project
	|__ build
	|__ main.cpp
	|__ mylib.cpp
	|__ CMakeLists.txt
```

这个时候，我们只需要将 `main.cpp` 和 `mylib.cpp` 一起生成可执行文件即可，其 `CMakeLists.txt` 如下：

```CMake
cmake_minimum_required (VERSION 3.10)
project (TEST)
add_executable (main main.cpp mylib.cpp)
```

2. 复杂的目录结构：
对于一些比较复杂的项目，可能会包含许多 **头文件** ， **源文件** ，和一些 **依赖库** 。此时，我们就需要更为复杂的 `CMakeLists.txt` 进行编译信息的生成。这种项目的特点便是 **实现不同功能的代码分门别类，分别存放于不同文件夹下** ，如：

```
CMakeI
	├── CMakeLists.txt
	├── common
	│   ├── CMakeLists.txt
	│   ├── kalman
	│   └── math
	├── main.cpp
	├── modules
	│   ├── A1
	│   ├── A2
	│   ├── M1
	│   └── M2
	└── README.md

```

像这种项目就需要我们使用多个 `CMakeLists.txt` 来进行管理。

## 2.2 两种方式设置规则

1. 包含源文件的子文件夹 **包含** `CMakeLists.txt` 文件，根目录中的 `CMakeLists.txt` 通过 `add_subdirectory (<target_dir>)` 添加子目录，从而将子目录的构建规则同整个项目结合起来
2. 包含源文件的子文件夹 **不包含** `CMakeLists.txt` 文件，根目录中的 `CMakeLists.txt` 为所有子文件夹设置编译规则

在实际编译中，方法一是最正常的编写方式，而 **方法二十分不推荐** ，因为在一个文件中编写所有规则会使得整个文件及其混乱，难以有条理。但是，对于一些简单的多文件项目也可以使用方法二。

## 2.3 编译流程

1. 编写 `CMakeLists.txt` 文件
2. 执行 `cmake <path_to_CMakeLists.txt>` 来生成 `Makefile` 
3. 执行 `make -j<n>` 进行编译

> 注意： `<path_to_CMakeLists.txt>` 为指向工程 **最顶级 `CMakeLists.txt` 的目录** ，一般为工程的根目录

## 2.4 两种构建方式

1. 内部构建 (in-source build)，在同级目录下生成编译文件，会显得杂乱无章，绝对不要
2. 外部构建 (out-of-source build)，将编译文件放置于不同于源文件的目录中，专门新建一个目录来存放编译文件，正常的项目开发均是如此
