#include <iostream>
#include "Json.h"
#include "gason.h"
using namespace gason;
double sum_and_print(JsonValue o) {
	double sum = 0;
	switch (o.getTag()) {
	case JSON_NUMBER:
		printf("%g\n", o.toNumber());
		sum += o.toNumber();
		break;
	case JSON_STRING:
		printf("\"%s\"\n", o.toString());
		break;
	case JSON_ARRAY:
		for (auto i : o) {
			sum += sum_and_print(i->value);
		}
		break;
	case JSON_OBJECT:
		for (auto i : o) {
			printf("%s = ", i->key);
			sum += sum_and_print(i->value);
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

	//char sJson[] = "{\"praenomen\":\"Gaius\",\"nomen\":\"Julius\",\"cognomen\":\"Caezar\","
	//	"\"born\":-100,\"died\":-44}";
	char sJson[] = "{ \"zubie\": \"cad\",\"members\" : ["

	"{\"firstname\": \"peisheng\", \"lastname\" : \"h\", \"email\" : \"buzhidao\"},"

	"{ \"firstname\": \"peisheng\", \"lastname\" : \"h\", \"email\" : \"buzhidao\" },"

	"{ \"firstname\": \"peisheng\", \"lastname\" : \"h\", \"email\" : \"buzhidao\" }]}";

	Json json;
	json.Parse(sJson);

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
	getchar();
	return 0;
}