# 01 可执行文件的构建

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

# 02 库文件的构建

## 2.1 静态库/动态库

在 Linux 中，以 **`.so`** 为后缀的文件属于 **动态库** ，以 **`.a`** 为后缀的文件属于 **静态库** 

1. 静态库：
	优点：静态库在编译的时候会将库文件 **直接整合进目标程序中** ，所以利用静态库编译成功的可执行文件 **可以独立运行，不需要外部依赖** 
	缺点：利用静态库编译成的文件 **体积一般比较大，因为包含了整个库的内容** ，同时，从 **更新升级** 的难易程度来讲，静态库没有优势， **想要更新其中一个库，就需要将整个项目重新编译** 
2. 动态库：
	优点： **体积小，更新容易** 
	缺点： **运行需要外部依赖，不如静态库更快速** 

## 2.2 普通库的构建

在多文件架构中，我们需要将某个功能模块抽象出来时，通常需要 **为某个模块构建一个库** ，最终将这些库链接至可执行文件上。我们使用 `add_library ()` 语句来添加库文件

`add_library (<lib_name> [SHARED|STATIC|MODULE] <source>` 
- [<lib_name>](CMake%20Commands.md#^a4c4bc) 
- `[SHARED|STATIC|MODULE]` : 指定库的类型为 **动态库** ， **静态库** 或 **[模块库]()** ，若没有指定默认静态库
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

此外，我们还可以为我们构建的库起一个别名 : 

```CMake
add_library (mylib1 STATIC ./src/mylib1.cpp)
target_include_directories (mylib1 PUBLIC ./include)

# 为库起别名
add_library (hello ALIAS mylib1)
```

此后我们便可以使用 `hello` 作为库的名字来链接，绑定等。

## 2.3 头文件包含有关的属性

1. `PUBLIC` : [Look](04%20Write%20CMakeLists#2.%20`PUBLIC`%20链接)
2. `PRIVATE` : [Look](04%20Write%20CMakeLists#1.%20`PRIVATE`%20链接) 
3. `INTERFACE` : 在绑定该当前目标时给指定的内容设置 **接口属性** ，通常用于 **接口库头文件的绑定** ，其他目标在链接当前目标的时候 **只能获得其接口(只能访问其声明)** 

## 2.4 接口库的构建

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

## 2.5 访问库文件的方式

在访问第三方库的时候，第三方库并 **不提供头文件和源文件** ，而是提供 **头文件和库文件** ，在访问本例的 `mylib1` 时，若该库绑定头文件的属性为 `PUBLIC` ，则不需要再将该库的头文件与目标可执行文件绑定

> 注意：
> 在调用第三方库如 `OpenCV` 时，需要 **同时将头文件和库文件与目标可执行文件链接**

## 2.6 库链接方式

在链接头文件和库的时候，我们常使用 `target_include_directories ()` 和 `target_link_libraries ()` 而不去使用 `include_directories ()` 和 `link_diretories ()` 
