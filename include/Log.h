#pragma once

#include "spdlog/spdlog.h"

class Log
{
public:
	Log();
	~Log();
	void test();
	static auto get_d_st_logger()
	{
		return spdlog::daily_logger_st("async_file_logger", "../../logs/async_log.txt");
	}
	static auto get_b_mt_logger()
	{
		return spdlog::basic_logger_mt("basic_logger", "../../logs/basic.txt");
	}
};

