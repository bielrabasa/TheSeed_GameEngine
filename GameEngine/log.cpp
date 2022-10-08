#pragma once
#include "Globals.h"
#include "Logs.h"

void log(const char file[], int line, LogsType type, const char* format, ...)
{
	static char tmp_string[4096];
	static char tmp_string2[4096];
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
	while (j < 4096) {
		a = tmp_string2[j];
		if (a == 0) {	// '\0'
			tmp_string[i] = 0;
			break;
		}

		if (a == 92) {	// '\'
			i = 0;
			j++;
			continue;
		}
		tmp_string[i] = a;
		
		i++;
		j++;
	}

	//Imgui Logger
	Logs::DebugLog(tmp_string, type);
}