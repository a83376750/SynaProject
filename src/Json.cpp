#include "Json.h"
#include <string>

Json::Json()
{

}


Json::~Json()
{
}

Json& Json::operator[](const char *key)
{
	return *this;
}

bool Json::Parse(char *sJson)
{
	//ASSERT(!sJson);
	char *endptr;
	gason::JsonValue jsonValue;
	gason::JsonAllocator allocator;
	int status = jsonParse(sJson, &endptr, &jsonValue, allocator);
	if (status != gason::JSON_OK) {
		fprintf(stderr, "%s at %zd\n", jsonStrError(status), endptr - sJson);
		return false;
	}
	genStat(jsonValue);
	return true;
}