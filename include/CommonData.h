#pragma once
#include <cstdint>

struct HeadData
{
	uint32_t	MsgLen;				//消息长度
	uint16_t	MsgSeq;				//流水号
	uint8_t		MsgType;			//消息类型
	uint8_t		MsgVersion;			//当前版本号
	uint16_t	MsgCheck;			//检验和
	uint8_t		MsgAddition[0];		//附加信息
};


