#include "Server.h"
#include "Ini.h"
#include "zmq.h"
#include <string>

Server::Server()
{
	m_ctx = zmq_ctx_new();
	m_socket = zmq_socket(m_ctx, ZMQ_ROUTER);
	spdlog::daily_logger_st(serverLog, serverLogPath);
}


Server::~Server()
{
	spdlog::drop(serverLog);
	zmq_close(m_socket);
	zmq_ctx_term(m_ctx);
}

int Server::StartServer()
{
	Ini ini;
	ini.SetPath(INI_PATH);
	
	char address[24];
	ini.ReadString("CONFIG", "address", address);
	auto sptrLog = spdlog::get(serverLog);
	sptrLog->info("服务器绑定地址:{}", address);
	int rc = zmq_bind(m_socket, address);
	return rc;
}

int Server::Recv(void *buffer, size_t len)
{
	int nBytes = zmq_recv(m_socket, buffer, len, 0);
	while (nBytes < len)
	{
		nBytes += zmq_recv(m_socket, buffer, len - nBytes, 0);
	}

	auto sptrLog = spdlog::get(serverLog);

	if (nBytes != len)
	{
		sptrLog->info("大小不一致,读取大小:{},实际大小:{}", nBytes, len);
		return -1;
	}
	else
	{
		unsigned char *sBuffer = new unsigned char[len];
		sprintf_s((char*)sBuffer, len, "%02x", buffer);
		sptrLog->info("读取的buffer:{}", sBuffer);
		delete[] sBuffer;
		return 0;
	}
}

int Server::Send(void *buffer, size_t len)
{
	int nBytes = zmq_send(m_socket, buffer, len, 0);
	while (nBytes < len)
	{
		nBytes += zmq_send(m_socket, buffer, len - nBytes, 0);
	}

	auto sptrLog = spdlog::get(serverLog);

	if (nBytes != len)
	{
		sptrLog->info("大小不一致,写入大小:{},实际大小:{}", nBytes, len);
		return -1;
	}
	else
	{
		unsigned char *str = (unsigned char*)buffer;
		char cStr[6];
		std::string outputInfo;
		for (int i = 0; i < len; ++i)
		{
			if (i % 10 == 0)
				outputInfo.append("\n");
			sprintf_s(cStr, "%02x ", str[i]);
			outputInfo.append(cStr);

		}
		sptrLog->info("写入的buffer:{}\nbuffer 大小:{}", outputInfo, len);
		return 0;
	}
}
