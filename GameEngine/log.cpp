#pragma once
#include "Globals.h"
#include "Logs.h"


void log(const char file[], int line, LogsType type, const char* format, ...)
{
	static char tmp_string[4096];
	static char tmp_string2[4096];
	static char file_string[100];
	static va_list  ap;

	// Construct the string from variable arguments
	va_start(ap, format);
	vsprintf_s(tmp_string, 4096, format, ap);
	va_end(ap);
	sprintf_s(tmp_string2, 4096, "\n%s(%d) : %s", file, line, tmp_string);
	OutputDebugString(tmp_string2);
	
	//Clear string path
	char a = ' ';
	int i = 0;
	int j = 0;
	while (i < 100) {
		a = tmp_string2[j];
		if (a == 0) {	// '\0'
			file_string[i] = 0;
			break;
		}

		if (a == 92) {	// '\'
			i = 0;
			j++;
			continue;
		}
		file_string[i] = a;
		
		i++;
		j++;
	}

	for (i = 0; i < 98; i++) {
		if (file_string[i] == ':') {
			file_string[i + 2] = 0; //	'\0'
		}
	}
	/*
	std::string l = tmp_string2;
	int p = l.find(':')*/
	//Imgui Logger
	Logs::DebugLog(tmp_string, file_string ,type);
}