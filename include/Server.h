#pragma once
#include <atomic>
#include "spdlog/spdlog.h"
constexpr const char *serverLog = "serverLog";
constexpr const char *serverLogPath = "../../logs/serverLog";
class Server
{
public:
	Server();
	~Server();
	int StartServer();
	int Recv(void *buffer, size_t len);
	int Send(void *buffer, size_t len);
public:
	void *m_ctx;
	void *m_socket;
};

