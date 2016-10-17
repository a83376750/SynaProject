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

#include "rapidjson/rapidjson.h"
#include "rapidjson/writer.h"
class JsonWriter
{
public:
	JsonWriter();
	JsonWriter(char *value);
	JsonWriter(int value);
	JsonWriter(double value);
	JsonWriter(float value);
	JsonWriter(bool value);
	bool WriteInt32(char *key, int value);
	bool WriteObject(char *key, char *value);
	JsonWriter& operator = (JsonWriter &rhf);
	JsonWriter& operator = (char *value);
	JsonWriter& operator [] (char *key);
public:

	rapidjson::Writer<rapidjson::StringBuffer> m_writer;
};

