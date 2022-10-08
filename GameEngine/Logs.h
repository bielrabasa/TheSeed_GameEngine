#pragma once

//#include "Application.h"
#include <string>
#include <vector>

using namespace std;

enum class LogsType
{
	WARNINGLOG,
	SYSTEMLOG,
	MSGLOG,
};

struct DebugLogs
{
	DebugLogs(string st, string f, LogsType ty)// : st(st), repts(1), type(ty), file(f) {};
	{
		st = this->st;
		ty = this->type;
		f = this->file;
		repts = 1;
	}

	string st;
	string file;
	int repts;
	LogsType type;
};

class Logs
{
public :

	static void PrintDebug();
	static void DebugLog(string format, string file, LogsType type = LogsType::MSGLOG);
	static void CollapseDebug();
	static void UnCollapseDebug();

private:

	static vector<DebugLogs> logs;
	static vector<DebugLogs> logsCopy;
	static DebugLogs logsString;

	static float colorEdit[3];

	static bool isCollapsed;
	static bool showPath;

	static bool warnignDebug;
	static bool systemDebug;
	static bool msgDebug;
};