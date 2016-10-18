#include "Log.h"

//mt 不加锁  st加锁
Log::Log()
{

}


Log::~Log()
{
}

void Log::test()
{
	//基础日志 不加锁
	auto my_logger = spdlog::basic_logger_mt("basic_logger", "../../logs/basic.txt");
	my_logger->info("Some log message");


	auto file_logger = spdlog::rotating_logger_mt("file_logger", "../../logs/myfilename.txt", 1024 * 1024 * 5, 3);
	file_logger->info("Hello spdlog {} {} {}", 1, 2, "three");
	//更改日志输出格式 - 这是全局的
	spdlog::set_pattern("*** [%H:%M:%S %z] [thread %t] %v ***");

	//多线程日志加锁
	auto async_file = spdlog::daily_logger_st("async_file_logger", "../../logs/async_log.txt");
	for (int i = 0; i < 100; ++i)
		async_file->info("Async message #{}", i);

	//控制台输出
	auto console = spdlog::stdout_color_mt("console");
	console->info("Welcome to spdlog!");
	console->error("Some error message with arg{}..", 1);

	// Formatting examples
	console->warn("Easy padding in numbers like {:08d}", 12);
	console->critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
	console->info("Support for floats {:03.2f}", 1.23456);
	console->info("Positional args are {1} {0}..", "too", "supported");
	console->info("{:<30}", "left aligned");

	spdlog::get("console")->info("loggers can be retrieved from a global registry using the spdlog::get(logger_name) function");

}
