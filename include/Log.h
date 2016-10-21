#pragma once

#include "spdlog/spdlog.h"

class Log
{
public:
	Log();
	~Log();
	void test();
	
	static auto get_d_st_logger(char *logName)
	{
		return spdlog::daily_logger_st(logName, "../../logs/async_log");
	}
	static auto get_b_mt_logger(char *logName)
	{
		return spdlog::basic_logger_mt(logName, "../../logs/basic.txt");
	}
};

#define DLOG() spdlog::daily_logger_st("async_file_logger", "../../logs/async_log");
#define BLOG() spdlog::basic_logger_mt("basic_logger", "../../logs/basic.txt");
