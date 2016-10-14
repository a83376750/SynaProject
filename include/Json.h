#pragma once
#include "gason.h"
#include <map>
#include <vector>
using namespace std;
class Json
{
public:
	Json();
	~Json();
	bool Parse(char *sJson);
	Json& operator [] (const char *key);
private:
	map<string, gason::JsonValue> m_MapObjAry;
};

