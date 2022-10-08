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
	DebugLogs(string st, LogsType ty) : st(st), repts(1), type(ty) {};

	string st;
	int repts;
	LogsType type;
};

class Logs
{
public :

	static void PrintDebug();
	static void DebugLog(string format, LogsType type = LogsType::MSGLOG);
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