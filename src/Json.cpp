#include "Json.h"
#include <string>
#include <assert.h>

Json::Json()
{

}


Json::~Json()
{
}

Json& Json::operator[](const char *key)
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

bool Json::Parse(char *sJson)
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

double Json::AsNumber(unsigned int index, char *key)
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

int Json::AsInt(unsigned int index, char *key)
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

char* Json::AsString(unsigned int index, char *key)
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



bool Json::Asbool(unsigned int index, char *key)
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

void Json::SaveMapInfo(gason::JsonValue &jsonValue)
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

}

JsonWriter& JsonWriter::operator=(char *value)
{
	//gason::JsonNode *node = new gason::JsonNode;
	//node->value = gason::JsonValue(gason::JSON_STRING, value);
	//node->next = nullptr;
	//m_CurValue.toNode()->next
	return *this;
}



JsonWriter& JsonWriter::operator=(JsonWriter &rhf)
{
	//gason::JsonNode *node = this->m_tail.toNode();
	//while(strcmp(node->key, rhf.m_tail.toNode()->key))
	//{
	//	if(node->next == NULL)
	//		break;
	//	node = node->next;
	//}
	//if (node->next != NULL)
	//{
	//	gason::JsonNode *tmp = node->next;
	//	node->next = rhf.m_tail.toNode();
	//	node->next->next = tmp;
	//}
	//else
	//	node->next = rhf.m_tail.toNode();
	return *this;
}

JsonWriter& JsonWriter::operator[](char *key)
{
	return *this;
}