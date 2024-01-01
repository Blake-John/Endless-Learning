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

`CMake` 的编译流程与 C/C++ 的编译流程息息相关，因此我们应熟悉 gcc/g++ 的使用

## 2.1 C++ 编译流程

C++ 基本编译流程为 **预处理** ， **编译汇编** ， **链接** ，详情可见：
- [[02.How C++ Work#2.2 The Steps to Build a Executable File|How C++ Work ?]]
- [[Cpp环境配置及编译器使用#1.1 编译|编译]]

## 2.2 CMake工程

CMake工程由 **源文件** ， **CMakeLists.txt** ， **编译信息** 组成。其中，我们需要关注的便是如何根据已有的源文件来编写 `CMakeLists.txt` 文件，并利用其进行编译

### 2.2.1 基本目录结构

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

### 2.2.2 两种方式设置规则

1. 包含源文件的子文件夹 **包含** `CMakeLists.txt` 文件，根目录中的 `CMakeLists.txt` 通过 `add_subdirectory (<target_dir>)` 添加子目录，从而将子目录的构建规则同整个项目结合起来
2. 包含源文件的子文件夹 **不包含** `CMakeLists.txt` 文件，根目录中的 `CMakeLists.txt` 为所有子文件夹设置编译规则

在实际编译中，方法一是最正常的编写方式，而 **方法二十分不推荐** ，因为在一个文件中编写所有规则会使得整个文件及其混乱，难以有条理。但是，对于一些简单的多文件项目也可以使用方法二。

## 2.2.3 编译流程

1. 编写 `CMakeLists.txt` 文件
2. 执行 `cmake <path_to_CMakeLists.txt>` 来生成 `Makefile` 
3. 执行 `make -j<n>` 进行编译

> 注意： `<path_to_CMakeLists.txt>` 为指向工程 **最顶级 `CMakeLists.txt` 的目录** ，一般为工程的根目录

### 2.2.4 两种构建方式

1. 内部构建 (in-source build)，在同级目录下生成编译文件，会显得杂乱无章，绝对不要
2. 外部构建 (out-of-source build)，将编译文件放置于不同于源文件的目录中，专门新建一个目录来存放编译文件，正常的项目开发均是如此

# 03 `CMakeLists.txt` 的编写

在上面的介绍中，我们已经知道，对于一个最基本的 `CMakeLists.txt` 文件，我们必须包括以下命令：
- `CMake` 最小版本指定
- 设置项目名称
- 生成目标可执行文件

接下来，我们将讲讲更适合于一般项目的编写规则

# 04 CMake语法规则

通过上面两个项目的实践，我们已经掌握了 **最基本，最通用，也是最重要的编写规则** ，接下来，我们将详细叙述CMake中具体的语法规则

## 4.1 变量

变量的定义通过 `set (<variable_name> <source>)` 来定义，通过 `${<variable_name>` 来调用，通过 `unset (<variable_name>` 来解除

`CMake` 中的变量分为 **局部变量** 和 **缓存变量** 。

### 4.1.1 局部变量

局部变量是指在 **当前模块** 和 **子模块** 中可以访问的变量

>  `子模块` ：通过 `include` 找到的 `.cmake` 文件或者通过 `add_subdirectory ()` 找到的包含 `CMakeLists.txt` 的目录

```CMake
	set (A "a") # 将 A 的值设置为 "a"
	set (B ${A} "b") # 将 B 的值设置为 "a", "b"

	unset (A) # 解除变量 A 的定义
```

### 4.1.2 缓存变量

缓存变量是指在定义后被添加至 `CMakeCache.txt` 文件中，访问时从该文件中获取，可以在任意位置调用的变量。缓存变量又分为 **内置环境变量** 和 **自定义缓存变量** 。

#### 4.1.2.1 内置环境变量

内置环境变量是 `CMake` 默认提供，默认定义好的变量

> 注意：其定义方式 **与局部变量的定义方式相同** ，但是其作用方式是 **缓存变量的作用方式**

##### 1. 编译选项 

1. `CMAKE_C_FLAGS` 和 `CMAKE_CXX_FLAGS`

`CMAKE_C_FLAGS` 是 C 文件编译选项，而 `CMAKE_CXX_FLAGS` 是 C++ 文件编译选项。一般情况下， **这两项没有默认值** ，但是我们设置的值会 **作为附加参数追加在编译命令之后** 

```CMake
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	# 在 CMAKE_CXX_FLAGS 后追加 -std=c++11 选项
```

> 在上面的代码中，为了保证默认编译选项保持不变，能够正常执行编译命令，我们设置其值的时候调用它本身 `${CMAKE_CXX_FLAGS}` 来赋值，并加上我们想要的选项 `-std=c++11` 。这个可以理解为 `a += 1`

2. `CMAKE_BUILD_TYPE`

`CMAKE_BUILD_TYPE` 用于设置编译类型 **Release** 或 **Debug**
- 调试的时候需要选择 Debug
- 发布时需要选择 Release

```CMake
	set (CMAKE_BUILD_TYPE Debug)
	# 设置编译类型为 Debug

	set (CMAKE_BUILD_TYPE Release)
	# 设置编译类型为 Release
```

3. `CMAKE_CXX_STANDARD` 和 `CMAKE_CXX_STANDARD_REQUIRED`

其中， `CMAKE_CXX_STANDARD` 用于指定 C++ 编译版本， `CMAKE_CXX_STANDARD_REQUIRED` 则用于选择是否使用指定版本

```CMake
	set (CMAKE_CXX_STANDARD 11)
	# 设置 C++ 编译版本为 c++11

	set (CMAKE_CXX_STANDARD_REQUIRED True)
```

##### 2. 与项目相关

1. `PROJECT_NAME` : 默认值为该项目的名称
2. `PROJECT_SOURCE_DIR` : 项目所在 **根目录的路径** (最顶层 `CMakeLists.txt` 所在路径)
3. `PROJECT_BINARY_DIR` : 项目的 **二进制路径**

```CMake
	# 可以这样使用与项目相关的变量
	add_executable (${PROJECT_NAME} main.cpp)
```

> 注意 : `CMAKE_SOURCE_DIR` 与 `PROJECT_SOURCE_DIR` 默认都为项目根目录路径

##### 3. 与路径相关

1. `CMAKE_SOURCE_DIR` 与 `PROJECT_SOURCE_DIR` : 指的是 **项目所在的根目录** 
2. `CMAKE_BINARY_DIR` 与 `PROJECCT_BINARY_DIR` : 指的是 **项目编译发生的目录**
3. `CMAKE_CURRENT_SOURCE_DIR` : 指的是 **当前 `CMakeLists.txt` 所在目录** 
4. `CMAKE_CURRENT_BINARY_DIR` : 指的是 **当前 `CMakeLists.txt` 所在子模块编译发生的目录**

```
	├── CMakeCache.txt
	├── CMakeFiles
	├── cmake_install.cmake
	├── compile_commands.json
	├── detectfunc (detectfunc 模块的编译目录)
	|	├── CMakeFiles
	|	├── cmake_install.cmake
	|	├── libdetectfunc.a
	|	└── Makefile
	├── main
	├── Makefile
	└── mathfunc (mathfunc 模块的编译目录)
		├── CMakeFiles
		├── cmake_install.cmake
		├── libmathfunc.a
		└── Makefile
```

从上面的目录结构中，我们可以看出，对于每一个子模块，都有相应的 **编译目录** ，而不是将所有编译放在同一个文件夹中

##### 4. 与输出相关

1. `EXECUTABLE_OUTPUT_PATH` : 最终生成的可执行文件的存放目录
2. `LIBRARY_OUTPUT_PATH` : 添加的库的输出目录

##### 5. 与环境相关

1. `CMAKE_INCLUDE_PATH` : CMake包含的 **头文件的目录** 
2. `CMAKE_LIBRARY_PATH` : CMake包含的 **库所在目录** 

> 注意：这两个变量都有默认值，如果要添加头文件或库所在的目录，应该在定义时调用本身来赋值后再额外追加新路径，如 
> `set (CMAKE_INCLUDE_PATH "${CMAKE_INCLUDE_PATH} <your_include_path>")` 

```ad-attention
注意：
若是设置 `LIBARARY_OUTPUT_DIR` 更改了输出目录，则应该在 `CMAKE_LIBRARY_PATH` 中追加你添加的库的输出路径
```

##### 6. 库相关

1. `BUILD_SHARED_LIB` : 用于设置库的 **默认编译方式** ，将此项设置为 `ON/TRUE` 则设置默认编译方式为编译动态库

> 注意：
> 库的编译方式由 `add_library ()` 来指定，若是没有指定编译方式，则默认将库编译成 **静态库** ，若将上述选项更改为 `ON/TRUE` ，则会将没有指定编译方式的库编译成动态库

#### 4.1.2.2 自定义缓存变量

##### 1. 选项变量

`option ()` 命令定义了一个 `bool` 类型的变量，该变量的值有两种表示方式 ：

1. `TURE` or `FALSE`
2. `ON` or `OFF`

```CMake
	option (<variable_name> [comment] <value>)
	option (USE_CUDA "choose to use cuda or not" OFF)
```

##### 2. 一般自定义缓存变量

```CMake
	set (<variable_name> <value> CACHE <type> [comment] [FORCE])
	set (USE_CUDA OFF CACHE BOOL "choose to use cuda or not")
	set (MYLIB_PATH /home/mylib CACHE PATH "the path to my libs")
	set (MY_INCLUDE "include" CACHE PATH "the path to include dir")
```

- 使用 `CACHE` 指定改变量为缓存变量
- `type` 指定该变量的类型， **必须有以下其中之一的值** ：
	- `BOOL` : 设置改变量为 `bool` 类型
	- `FILEPATH` : 设置改变量为 `文件路径` 
	- `PAHT` : 设置该变量为 `路径` 
	- `STRING` : 设置该变量为 `string` ，可以用于存放各种值
		- `INTERNAL` : 设置内部缓存条目
- `comment` : 可选项，用于注释该变量
- `FORCE` : 可选项，用于强制覆盖缓存条目

##### 3. 缓存条目

###### 什么是缓存条目？

缓存条目是用于编译的变量，存放于 `CMakeCache.txt` 文件中，在编译过程中如果遇到需要使用缓存条目，则会在该文件中查找。

> 注意：
> 在第一次构建编译信息的时候会生成 `CMakeCache.txt` 文件，并将缓存变量与缓存条目写入其中，之后的每一次构建都不会更改该文件。
> 
> 在使用 `set ()` 命令设置缓存条目的时候，若该缓存条目在 `CMakeCache.txt` 文件中 **不存在** ，则 **自动创建** 并将其值写入；若该缓存条目 **已存在** ，则 **忽略 `set ()`** ，不会覆盖现有的缓存条目。
> 
> 但是，我们仍可以通过 `FORCE` 选项 **强制覆盖现有的缓存条目** 

###### 如何查看缓存条目？

查看缓存条目主要有两种方式：
1. 通过 `cmake-gui` 查看

![[cmake-gui查看缓存条目.png]]

2. 通过调用 `cmake` 的时候使用 `-L` 选项来查看

![[cmake -L 查看缓存条目.png]]

> 注意：
> 这两种方式均要对项目进行构建编译信息后才能查看，原因是我们可能会定义一些外部缓存条目用于编译信息的构建，如 OpenCV 有着大量外部缓存条目

###### 如何定义缓存条目？

缓存条目的定义有三种方式：

1. 在 `CMakeLists.txt` 文档中定义
2. 在调用 `cmake` 命令时使用 `-D` 选项定义
3. 通过 `cmake-gui` 来定义

在实际编译中，我们会通过使用 `-D` 选项或使用 `cmake-gui` 来设置缓存条目，而非在 `CMakeLists.txt` 文档中进行定义，如在从源码构建 OpenCV 项目的时候，我们就需要使用命令 : 

```bash
	cmake -DBUILD_EXAMPLES=OFF -DBUILD_PERF_TESTS=OFF -DBUILD_TESTS=OFF -DBUILD_opencv_python3=OFF -DBUILD_opencv_python_bindings_generator=OFF -DBUILD_opencv_python_tests=OFF -DBUILD_JAVA=OFF -DBUILD_opencv_java_bindings_generator=OFF -DBUILD_opencv_js=OFF -DBUILD_opencv_js_bindings_generator=OFF -DBUILD_opencv_dnn=ON -DBUILD_opencv_ml=ON -DOPENCL_FOUND=OFF -DBUILD_opencv_gapi=OFF -DOPENCV_ENABLE_NONFREE=ON -DENABLE_FAST_MATH=ON -DWITH_GSTREAMER=ON -DCMAKE_BUILD_TYPE=Release ..

```

或者通过GUI：

![[cmake-gui设置缓存条目.png]]

