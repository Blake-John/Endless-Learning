# 00 Introduction

## 0.1 What is CMake ?

`CMake` 是一个 **跨平台** 的安装编译工具，可以使用 **简单** 的程序语句来描述 **所有平台的安装（编译过程）** ，可以说是大部分 C++ 开源项目的标配

## 0.2 How do the CMake work ?

![CMake工作.png](CMake工作.png)

![添加项目的操作.png](添加项目的操作.png)

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
		│   ├── CMakeFiles/
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

## 3.1 设置变量优化指令

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

## 3.2 指定 C++版本

我们在编写的时候可以指定 C++ 的编译版本。注意，从 GCC/G++ 6.1 开始，当不指定任何 C++ 版本标准时，默认版本为 c++14

```CMake
	set (CMAKE_CXX_STANDARD 11)
	set (CMAKE_CXX_STANDARD_REQUIRED TRUE)
```

## 3.3 添加库

一个中等大小的项目，一般会有自己所编写的库，这个时候，我们便需要将自己编写的库纳入编译中

### 3.3.1 生成目标库

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

### 3.3.2 链接可执行文件和目标库

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

## 3.4 编译

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
	# 定义缓存变量
	set (<variable_name> <value> CACHE <type> [comment] [FORCE])
	set (USE_CUDA OFF CACHE BOOL "choose to use cuda or not")
	set (MYLIB_PATH /home/mylib CACHE PATH "the path to my libs")
	set (MY_INCLUDE "include" CACHE PATH "the path to include dir")

	# 解除缓存变量
	unset (<variable_name> CACHE)
	unset (USE_CUDA CACHE)
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

![cmake-gui查看缓存条目.png](cmake-gui查看缓存条目.png)

2. 通过调用 `cmake` 的时候使用 `-L` 选项来查看

![](cmake%20-L%20查看缓存条目.png)

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

![cmake-gui设置缓存条目.png](cmake-gui设置缓存条目.png)

## 4.2 常用与语句块

### 4.2.1 运算符

#### 4.2.1.1 一元运算符

###### 1. `EXISTS` 

用于判断文件或者目录是否存在，存在时结果为真，需要提供全路径，也可以是符号链接

`if (EXISTS <path>)` 

```CMake
	if (NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/test)
```

###### 2. `IS_DIRECTORY` 

用于判断指定内容是否为文件夹，是文件夹则为真

`if (IS_DIRECTORY <path>)` 

###### 3. `COMMAND` 

用于判断所给对象是否为 **命令、宏或函数** 等 **可以被调用的对象** ，是则为真

`if (COMMAND <target>)` 

###### 4. `DEFINED` 

用于判断说给变量是否存在，存在为真

`if (DEFINED [ENV] <variable_name>)` 

> 注意：
> 若判断的对象为 **环境变量** ，则需要在前面加上 `ENV` 选项

#### 4.2.1.2 二元运算符

###### 1. 数字逻辑运算符

- `LESS` : <
- `GREATER` : >
- `EQUAL` : =
- `LESS_EQUAL` : <=
- `GREATER_EQUAL` : >=

用于判断左右两边是否符合条件，符合为真为真

`if (<variable_name> EQUAL <value>)`

###### 2. `STREQUAL` 

利用 **[[14.String|字典序]]** 比较两边的字符串是否相等，相等为真

`if (<STR1> STREQUAL <STR2>)`

###### 3. `MATCHES` 

判断左右两边是否匹配，如果左边的值与右边的正则表达式匹配，结果为真

`if (<variable1> MATCH <re>)`

```CMake
	if (CMAKE_SYSTEM_NAME MATCH "Linux")
		message (STATUS "Current Platform : Linux")
	elseif (CMAKE_SYSTEM_NAME MATCH "Windows")
		message (STATUS "Current Platform : Windows")
	endif ()
```

#### 4.2.1.3 逻辑操作符

- `NOT`
- `AND`
- `OR`

### 4.2.2 条件控制

```CMake
	if (<condition>)
		<codes>
	elseif (<condition>)
		<codes>
	else ()
		<codes>
	endif ()
```

> 注意：每次结束判断不能忘记加 `endif ()` 语句

### 4.2.3 遍历循环

#### 1. `foreach` 

```CMake
	foreach (<循环变量> <循环目标>)
		<codes>
	endforeach ()
```

```CMake
	foreach (i 1 2 3)
		message ("value : ${i}")
	endforeach ()

	# value : 1
	# value : 2
	# value : 3
```

#### 2. `RANGE`

与 `Python` 中的 `range` 函数 [[|使用方法]] 相同，但不需要括号，而且在 `Python` 中， `range ()` 左闭右开，在 `CMake` 中， `RANGE` 为闭区间

```CMake
	foreach (i RANGE 2)
		message ("value : ${i}")
	endforeach ()

	# value : 0
	# value : 1
	# value : 2
```

```CMake
	foreach (i RANGE 1 5 2)
		message ("value : ${i}")
	endforeach ()

	# value : 1
	# value : 3
	# value : 5
```

```ad-attention
注意！
在 `if` 和 `foreach` 语句中设置的变量 **仍会在条件体，循环体外生效** ，对于设置的变量 **要养成使用 `unset ()` 解除变量的习惯** ！
```

# 05 构建

## 5.1 可执行文件的构建

`可执行文件` 在 `CMake` 中视为一个 **变量** ，具有 `TARGET` 属性，通过 `add_executable ()` 命令进行构建，所以将库文件或头文件路径链接到可执行文件时的命令为 `target_link_libraries ()` 或 `target_include_directories ()` ：

```CMake
	cmake_minimum_required (VERSION 3.10)
	project (HELLO_WORLD)
	add_executable (main main.cpp)

	target_link_libraries (main mylib)
```

如果需要使用到 **第三方库** ，则需要手动为其添加库和头文件的链接，如 `OpenCV` 库，我们可以通过 `find_package ()` 来找到我们想要的库：

```CMake
	find_package (<package> [mode])
	find_package (OpenCV REQUIRED)
```

其中， `REQUIRED` 选项会在没有找到相应包的时候 **停止整个项目的构建** 

然后，我们可以将 `OpenCV` 包链接到目标文件：

```CMake
	target_include_directories (main PUBLIC ${OpenCV_INCLUDE_DIRS})
	target_link_libraries (main ${OpenCV_LIBS})
```

## 5.2 库文件的构建

### 5.2.1 静态库/动态库

在 Linux 中，以 **`.so`** 为后缀的文件属于 **动态库** ，以 **`.a`** 为后缀的文件属于 **静态库** 

1. 静态库：
	优点：静态库在编译的时候会将库文件 **直接整合进目标程序中** ，所以利用静态库编译成功的可执行文件 **可以独立运行，不需要外部依赖** 
	缺点：利用静态库编译成的文件 **体积一般比较大，因为包含了整个库的内容** ，同时，从 **更新升级** 的难易程度来讲，静态库没有优势， **想要更新其中一个库，就需要将整个项目重新编译** 
2. 动态库：
	优点： **体积小，更新容易** 
	缺点： **运行需要外部依赖，不如静态库更快速** 

### 5.2.2 普通库的构建

在多文件架构中，我们需要将某个功能模块抽象出来时，通常需要 **为某个模块构建一个库** ，最终将这些库链接至可执行文件上。我们使用 `add_library ()` 语句来添加库文件

`add_library (<lib_name> [SHARED|STATIC|MODULE] <source>` 
- [[CMake#^a4c4bc|<lib_name>]] 
- `[SHARED|STATIC|MODULE]` : 指定库的类型为 **动态库** ， **静态库** 或 **[[|模块库]]** ，若没有指定默认静态库
- `<source>` 用于构建库文件的源文件，可以有多个

假设有这样一个文件架构：

```
	project1
    ├── CMakeLists.txt
    ├── MyLib1
	|	├── include
	|	├── src
	|	└── CMakeLists.txt(待创建)
    └── main.cpp
```

根据上面的实践，我们已经知道，在多文件架构中，每一个模块最好使用独立的 `CMakeLists.txt` 进行管理，因此，我们在 `/Mylib1/CMakeLists.txt` 中写：

```CMake
	add_library (mylib1 STATIC ./src/mylib1.cpp)
```

同时，由于该库存在非默认包含路径，需要：

```CMake
	target_include_directories (mylib1 PUBLIC ./include)
```

如果该库使用了第三方库的内容，也需要将第三方库链接到该库

```CMake
	target_include_directories (mylib1 PUBLIC <third_lib_include_path>)
	target_link_libraries (mylib1 <third_lib>)
```

```ad-attention
我们使用 `add_library (mylib SHARED mylib.cpp)` 生成的动态库 `libmylib.so` 在调用时 **无法做到内存上的复用** ，在 **多个程序同时使用该动态库时，仍然会开辟一块内存存储该动态库的内容**

为了实现内存上的复用，我们应该使用 `地址无关代码机制(position-independent code)`

`list (APPEND CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")`

在编译选项后追加 `-fPIC` 选项

```

### 5.2.3 头文件包含有关的属性

1. `PUBLIC` : [[CMake#2. `PUBLIC` 链接|Look]]
2. `PRIVATE` : [[CMake#1. `PRIVATE` 链接|Look]] 
3. `INTERFACE` : 在绑定该当前目标时给指定的内容设置 **接口属性** ，通常用于 **接口库头文件的绑定** ，其他目标在链接当前目标的时候 **只能获得其接口(只能访问其声明)** 

### 5.2.4 接口库的构建

在程序的开发过程中，会遇到 **只有头文件 `.h/.hpp`** 而 **没有源文件 `.cpp`** 的情况，而一般的 `add_library ()` 只能为源文件生成目标库，而不能用头文件生成目标库

我们想要对只含头文件的模块生成目标库，只使用其中的声明而不需要具体的实现方法，此时我们称生成的库为 **接口库** 

假设在刚刚的文件架构基础上上再添加一个用于构建接口库的模块：

```
	project1
    ├── CMakeLists.txt
    ├── MyLib1
	|	├── include
	|	|	└──MyLib1.hpp
	|	├── src
	|	|	└──MyLib1.cpp
	|	└── CMakeLists.txt
	├── MyLib2
	|	├── include
	|	|	└──MyLib2.hpp
	|	└── CMakeLists.txt(待创建)
    └── main.cpp
```

创建接口库的语法与创建普通库类似，只不过少了源文件的添加，在 `/Mylib2/CMakeLists.txt` 中，我们写入：

```CMake
	add_library (mylib2 INTERFACE)

	target_include_directories (mylib2 INTERFACE include)
```

- 我们设置生成的库的属性为 `INTERFACE` 并且不对其添加源文件
- 然后，我们需要将头文件路径绑定到该库上，从而使其能够调用头文件中的声明，此时我们设置头文件的链接属性为 `INTERFACE` 
- 接着，如果当前库需要用到其他库，还需要用接口库的链接形式来链接其他库：
	- `target_link_libraries (mylib2 INTERFACE ${OpenCV_LIBS})`

### 5.2.5 访问库文件的方式

在访问第三方库的时候，第三方库并 **不提供头文件和源文件** ，而是提供 **头文件和库文件** ，在访问本例的 `mylib1` 时，若该库绑定头文件的属性为 `PUBLIC` ，则不需要再将该库的头文件与目标可执行文件绑定

> 注意：
> 在调用第三方库如 `OpenCV` 时，需要 **同时将头文件和库文件与目标可执行文件链接**

### 5.2.6 库链接方式

在链接头文件和库的时候，我们常使用 `target_include_directories ()` 和 `target_link_libraries ()` 而不去使用 `include_directories ()` 和 `link_diretories ()` 

# 06 命令手册

## 1. `cmake_minimum_required ()`

用于指定构建工具 CMake 的最小版本要求

```CMake
	cmake_minimum_required (VERSION <version>)
	cmake_minimum_required (VERSION 3.10)
```

## 2. `project ()`

用于定义工程的名称，版本和支持的语言

```CMake
	project (<project_name> [VERSION <version>] [language])
	project (HELLO_WORLD)
	project (HELLO_WORLD VERSION 1.0)
	project (HELLO_WORLD VERSION 1.0 C++)
```

- `<project_name>` 会存贮在环境变量 `PROJECT_NAME` 中
- `[language]` 默认为 C/C++

## 3. `set ()` and `unset ()`

用于[[CMake#4.1 变量|定义变量和解除变量]] 

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

[[CMake#3.3.1 生成目标库|生成目标库]] ， [[CMake#5.2 库文件的构建|构建库文件]] 

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

[[CMake#5.1 可执行文件的构建|构建可执行文件]] 

```CMake
	add_executable (<exe_name> <source>)
```

## 9. `target_link_libraries ()`

[[CMake#3.3.2 链接可执行文件和目标库|为target添加需要链接的库]] 

```CMake
	target_link_libraries (<target> <lib>)
```

## 10. `target_include_directories ()` 

[[CMake#3.3.1 生成目标库|为target添加头文件路径]] 

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
