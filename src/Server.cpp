#include "Server.h"
#include "Log.h"

Server::Server()
{
	m_ctx = zmq_ctx_new();
	m_socket = zmq_socket(m_ctx, ZMQ_ROUTER);
}


Server::~Server()
{
	zmq_close(m_socket);
	zmq_ctx_term(m_ctx);
}

int Server::StartServer()
{
	char address[24] = "tcp://*:8080";
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
	if (nBytes != len)
	{
		auto log = Log::get_b_mt_logger();
		log->info("大小不一致,读取大小:{},实际大小:{}", nBytes, len);
		return -1;
	}
	return 0;
}

int Server::Send(void *buffer, size_t len)
{
	int nBytes = zmq_send(m_socket, buffer, len, 0);
	while (nBytes < len)
	{
		nBytes += zmq_send(m_socket, buffer, len - nBytes, 0);
	}
	if (nBytes != len)
	{
		return -1;
	}
	return 0;
}
