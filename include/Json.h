#pragma once
#include "gason.h"
#include <map>
#include <vector>
using namespace std;
class JsonReader
{
public:
	JsonReader();
	~JsonReader();
	bool Parse(char *sJson);
	JsonReader& operator [] (const char *key);
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
	void WriteInt32(char *key, int value);
	void WriteInt64(char *key, int64_t value);
	void WriteUInt32(char *key, uint32_t value);
	void WriteUInt64(char *key, uint64_t value);
	void WriteDouble(char *key, double value);
	void WriteString(char *key, const char *value);
	void WriteNull(char *key);

	JsonWriter& operator = (int value);
	JsonWriter& operator = (int64_t value);
	JsonWriter& operator = (uint32_t value);
	JsonWriter& operator = (uint64_t value);
	JsonWriter& operator = (double value);
	JsonWriter& operator = (const char *value);

	void WriteStartObject(char *key = nullptr);
	void WriteStartArray(char *key = nullptr);

	void WriteEndObject();
	void WriteEndArray();

	const char* ToChar();
	JsonWriter& operator [] (char *key);
public:
	rapidjson::Writer<rapidjson::StringBuffer> m_writer;
	rapidjson::StringBuffer m_strBuffer;
};

