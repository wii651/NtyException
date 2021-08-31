/***************************************************************
 * 
 * @file:    NtyException.cpp
 * @author:  wilson
 * @version: 1.0
 * @date:    2021-08-26 11:54:07
 * @license: MIT
 * @brief:   异常类
 * 
 ***************************************************************/
#include "NtyException.h"

NtyException::NtyException(const std::string& msg, const std::string& stack) {
	m_msg = msg;
	m_stackInfo = stack;
}

NtyException::~NtyException() throw() {}

bool NtyException::InitLogger(int logWay) {
	int ret = ntylogger_init(logWay);
	return ret == 0? true: false;
}
void NtyException::DestroyLogger() {
	ntylogger_destroy();
}

const char* NtyException::what() const throw() {
	return this->m_msg.c_str();
}

const char* NtyException::stack() const throw() {
	return this->m_stackInfo.c_str();
}

void NtyException::log(const std::string& moduleName, const std::string& procName) const {
#if WII_DEBUG
	ntylog2(moduleName.c_str(), procName.c_str(), std::string(m_msg + "\n[stack_info]:\n" + m_stackInfo + "\n").c_str());
#else
	ntylog2(moduleName.c_str(), procName.c_str(), std::string(m_msg + "\n").c_str());
#endif
}
