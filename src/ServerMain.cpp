#include <iostream>



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
	return 0;
}