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
	double	AsNumber(unsigned int index = 0, char *key = "");
	int		AsInt(unsigned int index = 0, char *key = "");
	char*	AsString(unsigned int index = 0, char *key = "");
	bool	Asbool(unsigned int index = 0, char *key = "");
private:
	map<string, gason::JsonValue> m_MapObject;					//保存所有object对象
	map<string, vector<gason::JsonValue> > m_MapArray;			//保存所有Array对象
	void SaveMapInfo(gason::JsonValue &jsonValue);
	gason::JsonValue m_JsonValue;
	gason::JsonAllocator m_Allocator;
	
	
	vector<gason::JsonValue> m_vecGetValue;	//这是查找后的JsonValue
};

