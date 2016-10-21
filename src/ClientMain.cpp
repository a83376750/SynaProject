#include <iostream>
#include "zmq.h"
#include <thread>
#define ZMQADDRESS "tcp://localhost:8080"
bool TestClient();
void SendBuffer(void *socket);

int main(int argc, char *argv[])
{
	if (argc <= 0)
	{
		printf("²ÎÊýÎª0\n");
	}
	else
	{
		for (int i = 0; i < argc; ++i)
		{
			printf("%s\n", argv[i]);
		}
	}

	if (TestClient())
		return 0;
	else
		return -1;
}

bool TestClient()
{
	void *ctx = zmq_ctx_new();
	void *socket = zmq_socket(ctx, ZMQ_DEALER);
	int rc = zmq_connect(socket, ZMQADDRESS);
	if (rc != 0)
	{
		printf("socket connect error\n");
		return false;
	}

	std::thread td(SendBuffer, socket);
	td.join();
	char str[1024];
	while (1)
	{
		zmq_recv(socket, str, strlen(str), 0);
	}
	return true;
}

void SendBuffer(void *socket)
{
	char str[1024];
	while (1)
	{
		std::cin >> str;
		int len = strlen(str);
		int nSize = zmq_send(socket, str, len, 0);
		printf("%d\n", nSize);
	}
}