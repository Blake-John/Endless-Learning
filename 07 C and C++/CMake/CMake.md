# 00 Introduction

## 0.1 What is CMake ?

`CMake` 是一个 **跨平台** 的安装编译工具，可以使用 **简单** 的程序语句来描述 **所有平台的安装（编译过程）** ，可以说是大部分 C++ 开源项目的标配

## 0.2 How do the CMake work ?

![[CMake工作.png]]

![[添加项目的操作.png]]

## 0.3 语法特性

1. 基本语法格式：
	- 参数使用 `()` 括起
	- 参数之间用 `空格` 或 `;` 分开

```CMake
	<command> (<parameter1> <parameter2> ...)
```

2. 特色：
	- **指令** 是**大小写无关的** 
	- **参数** 和 **变量** 是 **大小写相关的** 

```CMake
	set (HELLO hello.cpp)
	set (hello main.cpp)
	# HELLO 和 hello 的内容不一

	add_executable (main main.cpp)
	ADD_EXECUTABLE (main main.cpp)
	# 指令一样
```

3. 特殊：
	- **变量** 需要使用 `${<variable>}` 的方式来取值
	- 而在 `IF` 语句中则 **直接使用变量名** 

# 01 Quick Start

## 1.1 最小编译工程

假设我们现在有这样一个只含有一个源文件的项目

```
	program
		├── main.cpp
		└── main_g++
```

### 1.1.1 CMake文件

我们需要在项目的 **根目录** 下创建一个 `CMakeLists.txt` 文件来编写 **如何生成编译信息** ，使用 `CMake` 最重要的便是编写 `CMakeLists.txt` ， `CMake` 根据该文件来生成编译信息

对于这个项目，我们需要在 `CMakeLists.txt` 文件中写入：

```CMake
	cmake_minimum_required (VERSION 3.10)
	project (HELLO_CMAKE)
	add_executable (main main.cpp)
```

### 1.1.2 编译命令

编辑完 `CMakeLists.txt` ，我们便需要对该项目进行编译信息的生成，对项目进行编译，我们可以在命令行中输入以下指令：

```bash
	mkdir build
	cd build
	cmake ..
	make -j10
```

### 1.1.3 编译结果

在经过上述的操作后，我们会获得一个 **可执行文件** ，该可执行文件位于 `build` 目录下，调用该文件就可以运行我们编写的 C++ 代码

```
	program
		├── build
		│   ├── CMakeCache.txt
		│   ├── CMakeFiles
		│   ├── cmake_install.cmake
		│   ├── main (目标可执行文件，是由我们代码生成的可执行文件)
		│   └── Makefile (生成的用于 make 编译项目的 Makefile)
		├── CMakeLists.txt (我们编写的 CMakeLists.txt 文件)
		├── main.cpp
		└── main_g++
```

## 1.2 讲解

### 1.2.1 CMake文件

1. `cmake_minimum_required (VERSION <version>)` 命令用于指定 `CMake` 的最低版本
2. `project (<project_name>)` 用于设置该项目的名称
3. `add_executable (<target> <source>)` 用于将源代码文件编译成可执行文件

### 1.2.2 编译命令

1. `mkdir build` 用于创建一个 `build` 目录，我们将在这个目录下完成我们的编译，所以我们需要将工作路径切换到该目录 `cd build`
2. `cmake ..` 调用 `CMake` 读取目标目录下的 `CMakeLists.txt` 文件并生成编译信息，生成编译文件 `Makefile` 
3. `make -j10` 调用 `make` 根据 `Makefile` 文件中的编译信息对项目进行编译， `-j10` 是指定编译核心数，电脑有多少线程就可以设置多少核心，以 **加快编译速度** 

# 02 一个项目的编译过程