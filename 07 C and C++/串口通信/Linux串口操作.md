# 01 实现思路

1. 打开串口，并将串口的模式设置为 **可读可写** ， **不视为终端** ， **非阻塞模式** 
2. 设置串口参数，包括 : 
	- 波特率
	- 数据位
	- 停止位
	- 校验位
	- 流控
	- 输入输出处理
	- 超时函数
	- 最小等待字符
3. 将参数设置应用到串口上
4. 读/写数据
5. 关闭串口

# 02 实现代码

用于读取数据的代码如下 : 

```C++
#include <cerrno>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

#define log(x) std::cout << x << std::endl;

int main() {
    // 打开串口
    int fd = open("/dev/ttyUSB0", O_RDWR | O_NONBLOCK);
    if (fd == -1) {
        std::cerr << "打开串口失败" << std::endl;
        return 1;
    }

    // 设置串口属性
    struct termios termios_settings;
    // memset(&termios_settings, 0, sizeof(termios_settings));
    termios_settings.c_iflag = IGNPAR;                          //* 忽略 partiy 错误
    termios_settings.c_oflag = 0;                               //* 无输出处理
    termios_settings.c_cflag = CS8 | CREAD | HUPCL | CLOCAL;    //* 设置8位数据，读取模式，忽略调制解调信号， 取消本地回显
    termios_settings.c_lflag = 0;                               //* 无输入处理
    termios_settings.c_cflag &= ~CSTOPB;                        //* 设置一位停止位
    termios_settings.c_cflag &= ~PARENB;                        //* 设置无奇偶校验
    termios_settings.c_cc[VINTR] = 0;                           //* 终端处理为空
    termios_settings.c_cc[VQUIT] = 0;                           //* 退出处理为空
    termios_settings.c_cc[VERASE] = 0;                          //* 删除字符处理函数为空
    termios_settings.c_cc[VKILL] = 0;                           //* 终止字符处理函数为空
    termios_settings.c_cc[VEOF] = 0;                            //* 退出字符处理函数为空
    termios_settings.c_cc[VTIME] = 0;                           //* 超时处理函数为空
    termios_settings.c_cc[VMIN] = 1;                            //* 最小等待字符数设置为1

    if (0 != tcsetattr(fd, TCSANOW, &termios_settings)) {
        std::cerr << "设置串口属性失败" << std::endl;
        return 1;
    }

    // 设置非阻塞模式
    // if (0 != fcntl(fd, F_SETFL, O_NONBLOCK)) {
    //     std::cerr << "设置非阻塞模式失败" << std::endl;
    //     return 1;
    // }

    // 接收数据
    int bytes_received = 0;
    while (true) {
        char buffer[50] = " ";
        ssize_t key = read (fd, buffer, sizeof (buffer));
        if (key == -1)
        {
            if (errno == EAGAIN) //* 如果错误为 阻塞 ，即没有数据，则跳过
            {
                usleep (100);
                continue;
            }
            else
            {
                log ("ERROR !");
                log (errno);
                return 1;
            }
        }
        else
        {
            log (buffer);
        }
    }

    // 关闭串口
    close(fd);

    return 0;
}
```

用于写入数据的代码如下 : 

```C++
// #include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
// #include <errno.h>
#include <iostream>
// #include <cstring>

#define log(x) std::cout << x << std::endl;

int main ()
{
    int fd; // File Descriptor

    log ("-----------------------Start Serial Port Write------------------------");

    fd = open ("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);

    if (fd == -1)
    {
        log ("Open File Failed !");
    }
    else
    {
        log ("Open ttyUSB0 Successfully !");
    }

    termios SerialPortSettings;

    tcgetattr (fd, &SerialPortSettings);

    // 设置 波特率
    cfsetispeed (&SerialPortSettings, B9600);
    cfsetospeed (&SerialPortSettings, B9600);

    // 设置校验位
    SerialPortSettings.c_cflag &= ~PARENB;

    // 设置停止位 = 1
    SerialPortSettings.c_cflag &= ~CSTOPB;

    // 设置数据位 = 8
		SerialPortSettings.c_cflag &= ~CSIZE;
    SerialPortSettings.c_cflag |= CS8;

		// 启动字符接收，忽略调制解调器信号
    SerialPortSettings.c_cflag |= CREAD | CLOCAL;

    // 设置流控
		SerialPortSettings.c_cflag &= ~CRTSCTS; // 关闭硬件流控
		// 关闭软件流控
    SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);

    // 设置操作模式
    SerialPortSettings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG); // 关闭输入处理，关闭本地回显，关闭信号

		// 关闭输出处理
    SerialPortSettings.c_oflag &= ~OPOST;

    if (tcsetattr (fd, TCSANOW, &SerialPortSettings) != 0)
    {
        log ("Setting Attributes ERROR !");
    }
    else
    {
        log ("Setting Attributes Successfully !");
        log ("BaudRate = 9600\nStopBits = 1\nParity = None");
    }
    struct data
    {
        char head;
        char data[100];
        char end;
    };
    
    int write_byte = 0;
		char buf[50];

    data Data;
    Data.head = '@';
    Data.end = '\n';

    while (1)
    {
				if (read (fd, buf, 50) != -1)
				{
					log (buf);
				}
        std::cin >> Data.data;
        write_byte = write (fd, &Data, sizeof (Data));
        log (Data.data << " is written to ttyUSB0");
        log ("The size of the data : " << write_byte);
        log ("-------------------------------------------");

    }

    close (fd);
}

```

# 03 模块详解

## 3.1 `<fcntl.h>` 

`<fcntl.h>` (`file control`)是 C 语言中的一个头文件，它提供了一些用于 **文件控制** 的 **常量** 和 **函数原型** 。具体来说，该头文件主要用于以下几个方面：

1. **文件打开和关闭**：该头文件定义了 `open()` 和 `close()` 函数，用于 **打开和关闭文件**。open() 函数接受文件路径和标志位作为参数，并返回一个文件描述符，以后的读写操作都通过该文件描述符进行。close() 函数用于关闭已打开的文件。
	
2. **文件权限设置**：通过 `open()` 函数的参数可以 **指定文件的访问权限**。fcntl.h 中定义了一些常量，如 `O_RDONLY（只读）、O_WRONLY（只写）、O_RDWR（可读写）` 等，可以与 open() 函数的标志位进行组合，来设置文件的权限。
	
3. **文件操作标志位**：fcntl.h 中定义了一些标志位，用于 **控制文件的行为**。比如 `O_CREAT（create 若文件不存在则创建）、O_EXCL（exception log 若文件存在则报错）、O_APPEND（append 追加写入）` 等。
	
4. **文件控制函数**：该头文件还包含了一些文件控制的函数原型，如 `fcntl()` 、`fcntl64()`  等，这些函数用于对已打开的文件进行各种控制操作，如修改文件状态标志、获取文件状态等。

总的来说，`fcntl.h` 提供了一系列用于文件控制的常量和函数，使得我们可以在 C 语言程序中对文件进行打开、关闭、读写以及其他一些控制操作。这使得我们能够更好地管理和操作文件，提高程序的灵活性和可扩展性。

### 3.1.1 `open ()` 

> 用于打开一个文件，并返回一个文件描述符（file descriptor），以便后续对文件的读写操作。

**Declaration :** 
- `int open(const char *__file, int __oflag, ...)` 

**Parameters :** 
1. `const char *__file` : 要打开的文件路径名。
	
2. `int __oflag` : 打开文件的 **标志位**，用于指定文件的 **打开方式和行为**。
	- `O_RDONLY`: read only 仅以 **只读** 方式打开文件。
	- `O_WRONLY`: write only 仅以 **只写** 方式打开文件。
	- `O_RDWR`: read and write 以 **可读写** 方式打开文件。
	- `O_CREAT`: create 若文件 **不存在则创建文件**。如果文件 **已存在，则不会修改文件的内容，但允许进行读写操作**。需要注意的是，此时必须指定第三个参数 `mode`，设置新建文件的权限。
	- `O_EXCL`: exception log **如果文件已存在，不打开文件**。若同时指定了 `O_CREAT` 标志位，且文件已经存在，则返回错误。这个标志常常与 `O_CREAT` 一起使用，确保创建的文件不存在。
	- `O_TRUNC`: 若文件已存在，则 **将文件的大小截为0**。如果文件不存在，则忽略此标志位。
	- `O_APPEND`: 打开文件时，将文件指针定位到文件的末尾。每次写入数据时，都会 **追加写入** 到文件末尾处。
		
	- `O_NONBLOCK` ：以 **非阻塞模式** 打开文件，如果文件不可用，不会阻塞等待，而是会 **返回一个代表阻塞的错误** 
	- `O_SYNC` ：以 **同步模式** 打开文件，对文件进行磁盘写入操作后，确保数据已写入磁盘。
	- `O_ASYNC` ：以 **异步模式** 打开文件，对文件的读写操作不等待磁盘操作完成。
	- `O_DIRECT` ：以 **直接模式** 打开文件，**绕过缓冲区，直接对磁盘进行读写**。
	- `O_DIRECTORY` ：**打开一个目录**，而不是打开一个文件。
	- `O_NOFOLLOW` ：如果路径是符号链接，不follow其链接到目标。
	- `O_NOATIME` ：**不要更新文件的访问时间**。
	- `O_CREATE_MISSING_DIRS` ：**如果目录不存在，创建它**。
		
	- `O_NOCTTY` ：表示 **不要将此文件视为终端设备**。这通常在创建伪终端对时使用，如在某些Linux系统上 **创建与硬件设备的伪终端**。
	- `O_NDELAY` ：表示 **不使用NORMAL DELAY模式**。在某些情况下，这可以提高异步I/O操作的性能。

**Return :** 
- `open()` 函数返回一个 **非负数的 「文件描述符」**，表示打开的文件。如果 **打开文件失败，则返回-1**，并设置 `errno` 错误码来指示具体的错误原因。

> [!note] 
> **「文件描述符」** 是系统用来 **表示文件或目录的的唯一整数**。文件描述符可以用来进行文件读写操作，如使用 `read()` 和 `write()` 函数读写文件。文件描述符还可以用于 **检查文件的状态**，如检查文件是否已关闭、是否可读、是否可写等。

### 3.1.2 `write ()` 

> 用于写入指定字节的数据到某个文件

**Declaration :** 
- `ssize_t write(int __fd, const void *__buf, size_t __n)` 

**Parameters :** 
- `const void *__buf` : 要写入的数据的指针
- `size_t __n` : 要写入的数据的大小

**Return :** 
- `ssize_t` : 返回写入的数据的大小，如果写入错误，则返回 `-1` 

### 3.1.3 `read ()` 

> 用于读取串口缓存区的指定大小的数据

**Declaration :** 
- `ssize_t read(int __fd, void *__buf, size_t __nbytes)` 

**Parameters :** 
- `void *__buf` : 用于接收数据的变量的指针
- `size_t __nbytes` : 读取的数据大小

**Return :** 
- `ssize_t` : Return the number read, -1 for errors or 0 for EOF.

> [!note] 
> 当 `read ()` 返回 `-1` 的时候，我们就需要检查错误信息。当出现一个错误的时候，函数会将错误 **存储到 `errno` 中** ，我们可以通过输出该变量来查看错误信息。

## 3.2 `<termios.h>` 

`<termios.h>` 是一个 C 语言头文件，它 **包含了与终端 I/O 相关的函数和数据类型** 的定义。`termios`是一个用于处理通信协议的C++库，它提供了低级别的 **通信控制**。通过使用 `<termios.h>` 头文件，我们可以 **对终端进行输入和输出的控制**。

> [!attention] 
> 注意：
> `<termios.h>` 是 **Linux/Unix** 系统下的一个中断控制库， **在Windows中没有这个库！！！** 

以下是 `<termios.h>` 中一些常用的函数和数据类型：

1. `tcgetattr()` 和 `tcsetattr()`: 这两个函数用于 **获取** 和 **设置** 终端的 **属性**。
	- `tcgetattr()` 函数可以获取当前终端的属性，并将其 **保存在一个结构体中**；
	- `tcsetattr()` 函数则用于 **设置终端的属性**，通过 **传递一个结构体参数** 来指定所需的属性。
    
2. `struct termios`: 这是一个用于 **存储终端属性的结构体**。它包含了很多字段，用于描述终端的各种特性，如输入模式、输出模式、控制字符等。
    
3. `cfsetispeed()` 和 `cfsetospeed()`: 这两个函数用于 **设置终端的输入和输出波特率**。它们可以将指定的波特率值设置到终端属性的相应字段中。
    
4. `cfmakeraw()`: 这个函数可以 **将终端属性设置为原始模式**，即 **禁用终端的特殊处理和输入行编辑**。在原始模式下，**所有输入字符都会立即可用**，没有缓冲区或特殊字符的处理。
    
5. `tcflush()`: 这个函数用于 **刷新终端的输入或输出缓冲区**。可以通过指定参数 `TCIFLUSH` 来 **刷新输入缓冲区**，或者通过指定参数 `TCOFLUSH` 来 **刷新输出缓冲区**，还可以使用参数 `TCIOFLUSH` 来 **同时刷新输入和输出缓冲区**。
    

通过使用 `<termios.h>` 头文件提供的函数和数据类型，我们可以对终端进行更高级别的控制，如设置终端属性、控制终端输入输出的方式等。这对于需要实现特定终端行为的程序（如终端模拟器、串口通信等）非常有用。

### 3.2.1 `struct termios` 

`termios`结构体是一个用于 **存储终端属性** 的结构体，包含了与串行通信相关的各种设置和参数，描述终端的各种特性，如 **输入模式、输出模式、控制字符** 等。在这个结构体中，我们可以看到以下几个部分：

1. `c_iflag`：这个字段表示 **输入模式标志位**，用于控制终端 **如何处理输入字符**。例如，设置 `IGNBRK` 标志位可以忽略 BREAK 字符，设置 `IXON` 标志位可以启用 XON/XOFF 流控制等。
	
2. `c_oflag`：这个字段表示 **输出模式标志位**，用于控制终端 **如何处理输出字符**，如是否启用本地echo、是否启用超时等。例如，设置 `OPOST` 标志位可以启用输出映射和换行转换，设置 `ONLCR` 标志位可以将新行字符转换为回车加新行字符等。
	
3. `c_cflag`：这个字段表示 **控制模式标志位**，用于 **控制终端的硬件参数**。例如，**设置波特率、数据位数、停止位数、奇偶校验位**等。
	
4. `c_lflag`：这个字段表示 **本地模式标志位**，用于 **控制终端的行为**。例如，设置 `ICANON` 标志位可以启用规范模式，启用行编辑和 EOF 字符等。
	
5. `c_cc`：这个字段表示 **控制字符数组**，包含了一些 **特殊字符的定义**。例如，`c_cc[VINTR]` 表示中断字符，`c_cc[VEOF]` 表示输入结束字符等。

在这个结构体中，我们可以设置和获取与串行通信相关的各种参数，如波特率、数据位、停止位和奇偶校验等。通过修改`c_cflag`掩码，我们可以控制串行端口的这些参数。

#### 1. `c_iflag` 

**输入模式**，控制数据在 **传递给程序之前** 的处理方式，以下是可用的而宏定义 : 
- `BRKINT` : 当在输入行中检测到一个终止状态时，产生一个中断
- `TGNBRK` : 忽略输入行中的终止状态
- `TCRNL` : 将接收到的回车符转换为 `\'n'` 
- `TGNCR` : 忽略 `\'n'` 
- `INLCR` : 将接收到的 `\'n'` 转化为回车符
- `IGNPAR` : ignore parity excepetion char 接收时忽略奇偶校验错误的字符
- `INPCK` : in char parity check 对接收到的字符执行奇偶校验
- `PARMARK` : parity exception mark 对奇偶校验错误做出标记
- `ISTRIO` : 将所有接收的字符裁剪为 `7 bits` 
- **`IXOFF` : 对输入启用软件流控，启用接收暂停功能** 
- **`IXON` : 对输出启用软件流控，启用发送暂停功能**
- **`IXANY` : 在接收到START字符后重新启动输出队列，关闭则意味着由程序进行控制数据的传输**
- **`ECHO` : 启用输入字符的本地回显功能** 
- **`ECHONL` : 回显换行符** 
- **`ECHOE` : 擦除字符时回显退格符** 
- **`ICANON` : 启用标准输入处理** 
- **`ISIG` : 启用信号** 

其中， `T` 代表发送， `I` 代表接收， `CR` 代表回车符， `NL` 为 new line，代表换行符， `G` 代表 ignore

#### 2. `c_oflag` 

**输出模式**，控制输出字符的处理方式，即由程序发出的字符在传递到串行口或屏幕之前该如何处理 :
- **`OPOST` : 用于控制在输出数据时是否进行输出处理** 
- `ONLCR` : 将输出中的 `\'n'` 转换为回车符
- `OCRNL`
- `ONOCR` : 第0行不输出回车符
- `ONLRET` : 不输出回车符

#### 3. `c_cflag` 

**控制模式**，用于控制终端硬件的特性 : 
- **`CLOCAL` : 忽略所有调制解调器的状态行** 
- **`CREAD` : 启用字符接收器，允许从终端设备中读取数据** 
- **`CSIZE` : 设置收发字符的大小，`~CSIZE` 可以将该位清零，然后再重新设置字符大小**
- **`CS{5,6,7,8}` : 设置发送或接收字符时字符的大小为 `5/6/7/8 bits`** 
- **`CSTOPB` : 每个字符使用两位停止位** 
- **`PARENB` : 启用奇偶校验的功能** 
- **`CRTSCTS` : 启用硬件流控** 

### 3.2.2 `tcgetattr ()` `tcsetattr ()`

#### 1. `extern int tcgetattr(int __fd, struct termios *__termios_p)`

用于通过 `fd` 来初始化一个终端对应的 `termios` 结构，即将文件参数加载入该结构中，我们可以通过这种方法获取默认的配置，然后在结构体中对我们需要的进行修改，可以减少不必要的配置。

#### 2. `extern int tcsetattr(int __fd, int __optional_actions, const struct termios *__termios_p)`

我们可以使用该函数将结构体中的属性设置为文件的配置。

**Parameters :** 
- `__optional_actions` : 该参数控制修改方式
	- `TCSANOW` : now 立即对文件进行修改
	- `TCSADRAIN` : 等当前的输出完成后再对值进行修改
	- `TCSAFLUSH` : 等当前的输出完成后再修改，但是丢弃未从 read 调用返回的当前可用的任何输入

**Return :** 
- `0` : 表示成功设置终端
- `-1` : 表示设置失败

### 3.2.3 `cfsetispeed ()` `cfsetospeed ()` 

`cfsetispeed` 和 `cfsetospeed` 是 termios 库中用于设置串口输入和输出波特率的函数。这两个函数通常与串口通信相关，用于确保发送方和接收方以相同的速率进行通信，以避免数据传输错误。

#### 1. `cfsetispeed(struct termios *termios_p, speed_t speed)` 

- 这个函数用于设置串口的 **输入波特率**。它接受两个参数，第一个参数是指向 `struct termios` 结构体的指针，第二个参数是一个表示波特率的整数值或宏定义。
- 例如，`cfsetispeed(&SerialPortSettings, B9600);` 将输入波特率设置为 9600 比特每秒。

#### 2. `cfsetospeed(struct termios *termios_p, speed_t speed)` 

- 这个函数用于设置串口的输出波特率。它接受两个参数，第一个参数是指向 `struct termios` 结构体的指针，第二个参数是一个表示波特率的整数值或宏定义。
- 例如，`cfsetospeed(&SerialPortSettings, B9600);` 将输出波特率设置为 9600 比特每秒。

在这两个函数中，`speed_t` 类型通常是一个整数类型，可以使用 **预定义的宏定义** 来表示标准的波特率，比如 `B9600`、`B115200` 等。这样可以使代码更易读，并且具有更好的可移植性。

> 常用的波特率宏定义为如下：
> `#define B0 0000000 /* hang up */`
> `#define B50 0000001`
> `#define B75 0000002`
> `#define B110 0000003`
> `#define B134 0000004`
> `#define B150 0000005`
> `#define B200 0000006`
> `#define B300 0000007`
> `#define B600 0000010`
> `#define B1200 0000011`
> `#define B1800 0000012`
> `#define B2400 0000013`
> `#define B4800 0000014`
> `#define B9600 0000015`
> `#define B19200 0000016`
> `#define B38400 0000017`

这两个函数配合结构体 `struct termios` 使用，通过操作该结构体中的字段来实现对串口的输入和输出波特率进行设置。这样就能确保发送方和接收方在相同的速率下进行通信，从而避免数据传输错误。

### 3.2.4 设置奇偶校验 `PARENB` 

`PARENB (Parity ENABLE)` 是用于 **设置奇偶校验** 的宏定义，用于表示 **「奇偶校验位使能」**，本质上是一个位掩码 `0000400` 。

**当 `PARENB` 位被设置为 `1` 时，奇偶校验功能会被启用**，发送方会在每个字符的末尾添加一个奇偶校验位，用于检测传输过程中的错误。接收方会根据奇偶校验位来验证数据的准确性，并在发现错误时进行纠正。

**而当 `PARENB` 位被设置为 `0` 时，奇偶校验功能会被禁用**，数据将以无校验的方式直接传输，不添加额外的校验位。

> [!attention] 
> 对于 `PARENB` 位来说，其掩码状态为： **其余位皆为 `0` ，而「奇偶校验使能位」(`PARENB` 位) 为 `1`** 。因此，开启和关闭奇偶校验的运算方法并不相同。
> 
> 对于文件控制的所有宏定义来说， **该宏定义代表着开启/使能某一功能，即该宏定义代表的位不为 `0`** ，我们在需要关闭某一功能时，应对其取反，使得该位为 `0` ，操作都类似奇偶校验的开启与关闭。

#### 1. 开启奇偶校验

对于 `PARENB` ，要开启奇偶校验，要将 **奇偶校验使能位** 设置为 `1` ，则需要使用 **`|` 按位或** 运算，使 **其余位保持不变** ，而该位被设置为 `1` 

```C++
termios SerialPortStruct;
tcgetattr (fd, &SerialPortStruct); // 将原本tty文件的设置存储到 SerialPortStruct 中

SerialPortStruct.c_cflag |= PARENB; // 开启奇偶校验
```

> 假设 `PARENB` 为 `00010000` ，其他参数现在为 `10100111` ，通过按位或运算
> 	`00010000` 
>    |   `10100111` 
> ->    `10110111` 
> 则只有奇偶校验使能位改变，然后再将该值赋值给原本的变量。

#### 2. 关闭奇偶校验

对于 `PARENB` ，将 **奇偶校验使能位** 设置为 `0` ，需要运用 **`~` 取反以及 `&` 按位与** 运算。

```C++
termios SerialPortStruct;
tcgetattr (fd, &SerialPortStruct); // 将原本tty文件的设置存储到 SerialPortStruct 中

SerialPortStruct.c_cflag &= ~PARENB; // 开启奇偶校验
```

> 假设 `PARENB` 为 `00010000` ，其他参数为 `10110101` ，通过取反与按位与运算
>     ~`00010000`
>    ->   `11101111` 
>    &    `10110101` 
>    ->   `10100101` 
> 则只有该位被改变。

### 3.2.5 设置停止位长度

`CSTOPB` 代表将停止为长度 **设置为 `2`** ，因此
- 如果我们要将停止位长度设置为2，需要 `SerialPortStruct.c_cflags |= CSTOPB` 
- 如果只要一位长度的停止位，需要 `SerialPortStruct.c_cflag &= ~CSTOPB` 

### 3.2.6 设置字符长度

- 清空字符大小位 : `SerialPortStruct.c_cflag &= ~CSIZE`
- 设置字符大小 : `SerialPortStruct.c_cflag |= CS8` 

### 3.2.7 启用字符接收功能，并忽略调制解调器的控制信号

`SerialPortStruct.c_cflag |= CREAD | CLOCAL` 

### 3.2.8 设置流控

- 关闭硬件流控 : `SerialPortStruct.c_cflag &= ~CRTSCTS` 
- 关闭输入输出暂停，关闭自动输出 : `SerialPortStruct.c_cflag &= ~(IXON | IXOFF | IXANY)`

### 3.2.9 设置输入处理

关闭输入字符本地回显，关闭信号，关闭标准输入处理 : 

`SerialPortStruct.c_iflag = ~(ECHO | ECHOE | ICANON | ISIG)` 

### 3.2.10 设置输出处理

关闭输出处理 : `SerialPortStruct.c_oflag &= ~OPOST` 
