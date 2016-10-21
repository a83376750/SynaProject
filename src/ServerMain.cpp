#include <iostream>
#include "Json.h"
#include "gason.h"
#include "Server.h"
#include <thread>

void AllRecv(Server &sr);
void AllSend(Server &sr);

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

	Server sr;
	int re = sr.StartServer();
	assert(re == 0);
	std::thread tdSend(AllRecv, sr);
	//std::thread tdRecv(AllSend, sr);
	AllSend(sr);
	return 0;
}

void AllRecv(Server &sr)
{
	char str[1024];
	while (1)
	{
		sr.Recv(str, 1024);
		std::cout << str << std::endl;
	}
}

void AllSend(Server &sr)
{
	char str[1024];

	while (1)
	{
		std::cin >> str;
		sr.Send(str, strlen(str));
	}
}


using namespace gason;

void testJsonReaderAndWriter()
{
	//char sJson[] = "{\"praenomen\":\"Gaius\",\"nomen\":\"Julius\",\"cognomen\":\"Caezar\","
	//	"\"born\":-100,\"died\":-44}";
	//char sJson[] = "{ \"zubie\": \"cad\", \"abc\": true, \"members\" : ["

	//"{\"firstname\": false, \"lastname\" : \"h\", \"email\" : \"buzhidao\"},"

	//"{ \"firstname\": \"eisheng\", \"lastname\" : \"i\", \"email\" : \"uzhidao\" },"

	//"{ \"firstname\": \"isheng\", \"lastname\" : \"j\", \"email\" : \"zhidao\" }]}";

	//Json json;
	//json.Parse(sJson);
	//string zubie = json["zubie"].AsString();
	//printf(zubie.c_str());
	//printf(json["members"].AsString(2, "lastname"));
	//bool abc = json["members"].Asbool(1,"firstname");


	//char *endptr;
	//gason::JsonValue jsonValue;
	//gason::JsonAllocator allocator;
	//int status = jsonParse(sJson, &endptr, &jsonValue, allocator);
	//if (status != gason::JSON_OK) {
	//	fprintf(stderr, "%s at %zd\n", jsonStrError(status), endptr - sJson);
	//	return false;
	//}
	//sum_and_print(jsonValue);

	//printf("%s%d\n", "Num:", json.AsInt("born"));
	//printf("%s%d\n", "Num:", json.AsInt("died"));
	//printf("%s%s\n", "string:", json.AsString("praenomen"));
	//printf("%s%s\n", "string:", json.AsString("nomen"));
	//printf("%s%s\n", "string:", json.AsString("cognomen"));

	JsonWriter writer;
	writer.WriteStartObject();
	writer["hello"] = "world";
	writer["dll"] = nullptr;
	writer.WriteEndObject();
	string json = writer.ToChar();
	cout << json.c_str() << endl;
	char stackJson[100];
	strcpy_s(stackJson, json.c_str());
	JsonReader reader;
	reader.Parse(stackJson);
	cout << reader["hello"].AsString() << endl;
}

double sum_and_print(JsonValue o) {
	double sum = 0;
	switch (o.getTag()) {
	case JSON_NUMBER:
		printf("Number");
		printf("%g", o.toNumber());
		sum += o.toNumber();
		break;
	case JSON_STRING:
		printf("string");
		printf("\"%s\"", o.toString());
		break;
	case JSON_ARRAY:
		for (auto i : o) {
			printf("Array:{");
			sum += sum_and_print(i->value);
		}
		printf("Array}\n");
		break;
	case JSON_OBJECT:
		for (auto i : o) {
			printf("obj:{");
			printf("%s = ", i->key);
			sum += sum_and_print(i->value);
			printf("obj}\n");
		}
		break;
	case JSON_TRUE:
		fprintf(stdout, "true");
		break;
	case JSON_FALSE:
		fprintf(stdout, "false");
		break;
	case JSON_NULL:
		printf("null\n");
		break;
	}
	return sum;
}
