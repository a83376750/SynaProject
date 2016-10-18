#include "Json.h"
#include <string>
#include <assert.h>

JsonReader::JsonReader()
{

}


JsonReader::~JsonReader()
{
}

JsonReader& JsonReader::operator[](const char *key)
{
	m_vecGetValue.clear();

	auto ObjIter = m_MapObject.find(key);

	if (ObjIter != m_MapObject.end())
	{
		m_vecGetValue.push_back(ObjIter->second);
	}
	auto arrIter = m_MapArray.find(key);
	if (arrIter != m_MapArray.end())
	{
		for (auto &iter : arrIter->second)
		{
			m_vecGetValue.push_back(iter);
		}
	}
	return *this;
}

bool JsonReader::Parse(char *sJson)
{
	char *endptr;
	int status = jsonParse(sJson, &endptr, &m_JsonValue, m_Allocator);
	if (status != gason::JSON_OK) {
		fprintf(stderr, "%s at %zd\n", jsonStrError(status), endptr - sJson);
		return false;
	}
	SaveMapInfo(m_JsonValue);
	return true;
}

double JsonReader::AsNumber(unsigned int index, char *key)
{
	assert(m_vecGetValue.size() > index);
	auto value = m_vecGetValue.begin() + index;
	if (value != m_vecGetValue.end())
	{
		if (value->getTag() == gason::JSON_OBJECT)
		{
			for (auto i : *value) {
				if (!strcmp(i->key, key))
				{
					return i->value.toNumber();
				}
			}
		}
		return value->toNumber();
	}
	return NULL;		//这里最好就是抛异常
}

int JsonReader::AsInt(unsigned int index, char *key)
{
	assert(m_vecGetValue.size() > index);
	auto value = m_vecGetValue.begin() + index;
	if (value != m_vecGetValue.end())
	{
		if (value->getTag() == gason::JSON_OBJECT)
		{
			for (auto i : *value) {
				if (!strcmp(i->key, key))
				{
					return static_cast<int>(i->value.toNumber());
				}
			}
		}
		return static_cast<int>(value->toNumber());
	}
	return NULL;		//这里最好就是抛异常	
}

char* JsonReader::AsString(unsigned int index, char *key)
{
	assert(m_vecGetValue.size() > index);
	auto value = m_vecGetValue.begin() + index;
	if (value != m_vecGetValue.end())
	{
		if (value->getTag() == gason::JSON_OBJECT)
		{
			for (auto i : *value) {
				if (!strcmp(i->key, key))
				{
					return i->value.toString();
				}
			}
		}
		else
			return value->toString();
	}
	return NULL;		//这里最好就是抛异常
}



bool JsonReader::Asbool(unsigned int index, char *key)
{
	assert(m_vecGetValue.size() > index);
	auto value = m_vecGetValue.begin() + index;
	if (value != m_vecGetValue.end())
	{
		if (value->getTag() == gason::JSON_OBJECT)
		{
			for (auto i : *value) {
				if (!strcmp(i->key, key))
				{
					if (i->value.getTag() == gason::JSON_TRUE)
					{
						return true;
					}
					else if (i->value.getTag() == gason::JSON_FALSE)
					{
						return false;
					}
					else
					{
						assert(0);
					}
				}
			}
		}
		if (value->getTag() == gason::JSON_TRUE)
		{
			return true;
		}
		else if (value->getTag() == gason::JSON_FALSE)
		{
			return false;
		}
		else
		{
			assert(0);
		}
	}
	return false;		//这里最好就是抛异常
}

void JsonReader::SaveMapInfo(gason::JsonValue &jsonValue)
{

	gason::JsonTag tag = jsonValue.getTag();
	static string sName;
	switch (tag)
	{

	case gason::JSON_ARRAY:
	{
		vector<gason::JsonValue> vec;
		for (auto i : jsonValue) {
			vec.push_back(i->value);
		}
		m_MapArray[sName] = vec;
		break;
	}
	case gason::JSON_OBJECT:
	{
		for (auto i : jsonValue)
		{
			sName = i->key;
			SaveMapInfo(i->value);
		}
		break;
	}
	case gason::JSON_NUMBER:
	case gason::JSON_STRING:
	case gason::JSON_TRUE:
	case gason::JSON_FALSE:
	case gason::JSON_NULL:
	{
		m_MapObject[sName] = jsonValue;
		break;
	}
	default:
		break;
	}
}

JsonWriter::JsonWriter()
{
	m_writer.Reset(m_strBuffer);
}

void JsonWriter::WriteInt32(char *key, int value)
{
	m_writer.Key(key);
	m_writer.Int(value);
}

void JsonWriter::WriteInt64(char *key, int64_t value)
{
	m_writer.Key(key);
	m_writer.Int64(value);
}

void JsonWriter::WriteUInt32(char *key, uint32_t value)
{
	m_writer.Key(key);
	m_writer.Uint(value);
}

void JsonWriter::WriteUInt64(char *key, uint64_t value)
{
	m_writer.Key(key);
	m_writer.Uint64(value);
}

void JsonWriter::WriteDouble(char *key, double value)
{
	m_writer.Key(key);
	m_writer.Double(value);
}

void JsonWriter::WriteString(char *key, const char *value)
{
	m_writer.Key(key);
	m_writer.String(value);
}

void JsonWriter::WriteNull(char *key)
{
	m_writer.Key(key);
	m_writer.Null();
}

JsonWriter& JsonWriter::operator=(int value)
{
	m_writer.Int(value);
	return *this;
}

JsonWriter& JsonWriter::operator=(int64_t value)
{
	m_writer.Int64(value);
	return *this;
}

JsonWriter& JsonWriter::operator=(uint32_t value)
{
	m_writer.Uint(value);
	return *this;
}


JsonWriter& JsonWriter::operator=(const char *value)
{
	if (value == nullptr)
	{
		m_writer.Null();
	}
	else
	{
		m_writer.String(value);
	}
	return *this;
}


JsonWriter& JsonWriter::operator=(uint64_t value)
{
	m_writer.Uint64(value);
	return *this;
}

JsonWriter& JsonWriter::operator=(double value)
{
	m_writer.Double(value);
	return *this;
}

void JsonWriter::WriteStartObject(char *key)
{
	m_writer.StartObject();
	if(key != nullptr)
		m_writer.Key(key);
}

void JsonWriter::WriteStartArray(char *key)
{
	m_writer.StartArray();
	if (key != nullptr)
		m_writer.Key(key);
}


void JsonWriter::WriteEndObject()
{
	m_writer.EndObject();
}

void JsonWriter::WriteEndArray()
{
	m_writer.EndArray();
}

const char* JsonWriter::ToChar()
{
	if (m_writer.IsComplete())
		return m_strBuffer.GetString();
	else
		return nullptr;
}

JsonWriter& JsonWriter::operator[](char *key)
{
	m_writer.Key(key);
	return *this;
}