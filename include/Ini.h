#pragma once

#include <string>
#include <iostream>
#include <fstream>

#ifdef WIN32
/*
WritePrivateProfileString,
GetPrivateProfileString,
GetPrivateProfileInt
*/
#include <windows.h>
#endif

#define INI_PATH "../../server.ini"
class Ini
{
public:
	Ini();
	~Ini();
	//д����,��ʱû����
	bool WriteString(const char *sAppName, const char *sKey, const char *sValue);

	unsigned long ReadString(const char * sAppName, const char * sKey, char *sOutput, const char * sDefault = "");
	long ReadInt(const char * sAppName, const char * sKey, long nDefault = 0);
	void CheckPath();
	void SetPath(const char *sPath);
private:
	std::string m_sPath;
		
public:	
#ifndef WIN32
	long PackagingFunction(const char *lpAppName, const char *lpKeyName, const char *lpDefault,
		char *lpReturnedString, unsigned long nSize, const char *lpFileName);
#endif
};

