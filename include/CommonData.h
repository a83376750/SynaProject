#pragma once
#include <cstdint>

struct HeadData
{
	uint32_t	MsgLen;				//��Ϣ����
	uint16_t	MsgSeq;				//��ˮ��
	uint8_t		MsgType;			//��Ϣ����
	uint8_t		MsgVersion;			//��ǰ�汾��
	uint16_t	MsgCheck;			//�����
	uint8_t		MsgAddition[0];		//������Ϣ
};


