#pragma once
#include <iostream>

#define DEBUG 1

// 0 - display all logs
// 1 - display normal and critical logs
// 2 - display critical logs only
#define LOG_PRIORITY 0

// standard log
#if DEBUG == 1 && LOG_PRIORITY <= 1
#define LOG(x) std::cout << x << std::endl;
#define LOG2(msg, val) std::cout << msg << " " << val << std::endl;
#else 
#define LOG(x)
#define LOG2(msg, val) 
#endif

// low priority log
#if DEBUG == 1 && LOG_PRIORITY <= 0
#define LOG_L(x) std::cout << x << std::endl;
#define LOG2_L(msg, val) std::cout << msg << " " << val << std::endl;
#else 
#define LOG_L(x)
#define LOG2_L(msg, val)
#endif

// high priority log
#if DEBUG == 1 && LOG_PRIORITY <= 2
#define LOG_H(x) std::cout << x << std::endl;
#define LOG2_H(msg, val) std::cout << msg << " " << val << std::endl;
#else 
#define LOG_H(x)
#define LOG2_H(msg, val)
#endif