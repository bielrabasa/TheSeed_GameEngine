#pragma once
//#include "Application.h"
#include <string>
#include <vector>

using namespace std;

enum LogsType
{
	WARNING,
	SYSTEM,
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

	void PrintDebug();
	void DebugLog(string format, LogsType type = MSGLOG);
	void CollapseDebug();
	void UnCollapseDebug();

private:

	vector<DebugLogs> logs;
	vector<DebugLogs> logsCopy;
	DebugLogs logsString;

	bool isCollapsed = false;

	bool warnignDebug = true;
	bool systemDebug = true;
	bool msgDebug = true;
};