#pragma once
#include "zmq.h"
class Server
{
public:
	Server();
	~Server();
	int StartServer();
	int Recv(void *buffer, size_t len);
	int Send(void *buffer, size_t len);
	void *m_ctx;
	void *m_socket;
};

