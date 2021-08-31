/***************************************************************
 * 
 * @file:    NtyException.h
 * @author:  wilson
 * @version: 1.0
 * @date:    2021-08-24 21:20:05
 * @license: MIT
 * @brief:   异常类
 * 
 ***************************************************************/

#ifndef _NTY_EXCEPTION_H_ 
#define _NTY_EXCEPTION_H_

#include <string>
#include <exception>
#include <execinfo.h>
#include "nty_logger.h"

class NtyException
	: public std::exception
{
private:

	std::string m_msg;
	std::string m_stackInfo;
public:
	NtyException(const std::string& msg, const std::string& stack);
	virtual ~NtyException() throw();

	/**
	 * @brief 初始化日志器, 选择是同步方式记录还是开启日志专用线程异步记录
	 * 注意初始化完成后, 执行NtyException::DestroyLogger()之前, 无法再次初始化
	 * 
	 * @param logWay[in] 该传参为SYNC_LOG(0)时, 表示同线程下同步日志记录方式;
	 * 该传参为ASYNC_LOG(1)时, 表示开启单独的线程日志异步记录方式
	 * @return true -- 执行成功
	 * @return false -- 执行失败
	 */
	static bool InitLogger(int logWay);

	/**
	 * @brief 销毁日志器
	 */
	static void DestroyLogger();

	/**
	 * @brief 返回日志信息
	 * 
	 * @return const char* -- 日志信息c_str
	 */
	const char* what() const throw();

	/**
	 * @brief 返回堆栈信息
	 * 
	 * @return const char* -- 堆栈信息c_str
	 */
	const char* stack() const throw();

	/**
	 * @brief 记录信息到日志
	 * 
	 * @param moduleName[in] 日志模块名称
	 * @param procName[in] 日志进程名称
	 */
	void log(const std::string& moduleName, const std::string& procName) const;
};

#define CSTR(x)     _CSTR(x)
#define _CSTR(x)        #x

//[ 信息打印宏 ]
#define INFO(x)		(std::string("[") + __DATE__ + std::string(" ") + __TIME__ + std::string("]--[") + __FILE__ + std::string(":") + CSTR(__LINE__)  + std::string(":") + __FUNCTION__ + std::string("()]:\n\t") + std::string(x))

/**
 * @brief 创建NtyException类, 记录此刻的相关信息, 并将传参作为日志信息记录
 * 
 * @param str[in] std::string类型或c_str类型均可
 */
#define Ex(str) ({											\
	std::string stack;										\
	void* buf[200];											\
	int nptrs = backtrace(buf, 200);						\
	char** strings = backtrace_symbols(buf, nptrs);			\
	if (strings) {											\
		for (int i = 0; i < nptrs; i++) {					\
			if (i != 0)	{ stack.push_back('\n'); }			\
			stack.push_back('\t');							\
			stack.append(strings[i]);						\
		}													\
		free(strings);										\
	}														\
	NtyException(INFO(str), stack);							\
})

#endif	// _NTY_EXCEPTION_H_