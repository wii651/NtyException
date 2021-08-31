# NtyException
* 简单易用

* 内嵌日志记录器, 支持同步/异步两种日志记录方式

## quick start

```c++
#include "NtyException.h"
#include <iostream>

using namespace std;

int main() {
	//[ 在第一次日志记录前初始化 ]
	//[ ASYNC_LOG表示单独线程异步记录, SYNC_LOG表示当前线程同步记录 ]
	NtyException::InitLogger(ASYNC_LOG);	

	try {
		if (true) {
			throw Ex("Some log info");
		}
	} catch (NtyException& e) {
		cout << e.what() << endl;
		cout << e.stack() << endl;
		e.log("mod", "proc");	//[ 日志记录 ]
	}

	//[ 复位日志器 ]
	NtyException::DestroyLogger();
}
```

## 日志记录

执行`NtyException::log()`方法时, 会执行以下动作

1. 在执行路径下尝试创建`logs/module/[year]/[month]/proc-[day].log`文件

2. 打开文件并写入以下内容

   > [Aug 31 2021 10:46:36]--[quick_start.cpp:28:main()]:
   >
   > ​	Some log info
   >
   > [stack_info]:
   >
   > ​	./a.out(+0x1e43) [0x562597edbe43]
   >
   > ​	/lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xe7) [0x7fad88fbdbf7]
   >
   > ​	./a.out(+0x1d0a) [0x562597edbd0a]

## 编译
以编译quick_start.cpp为例
```c++
g++ quick_start.cpp NtyException.cpp nty_inproc_mq.c nty_logger.c -pthread
```
编译时增加`-D WII_DEBUG`选项可以在log中增加堆栈信息

编译时增加`-D NOLOGMSG`选项可以取消日志器状态在stdout中的输出

