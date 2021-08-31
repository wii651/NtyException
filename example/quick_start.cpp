/***************************************************************
 * 
 * @file:    quick_start.cpp
 * @author:  wilson
 * @version: 1.0
 * @date:    2021-08-31 10:37:42
 * @license: MIT
 * @brief:   
 * 编译:
 * g++ quick_start.cpp NtyException.cpp nty_inproc_mq.c nty_logger.c -pthread
 * 编译时增加 -D WII_DEBUG 选项可以在log中增加堆栈信息
 * 编译时增加 -D NOLOGMSG 选项可以取消日志器状态在stdout中的输出
 * 
 ***************************************************************/

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