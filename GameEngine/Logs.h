#pragma once
//#include "Application.h"
#include <string>
#include <vector>

using namespace std;

struct DebugLogs
{
	DebugLogs(string st) : st(st), repts(1) {};

	string st;
	int repts;
};

class Logs
{
public :

	void PrintDebug();
	void DebugLog(string format);
	void CollapseDebug();
	void UnCollapseDebug();

private:

	vector<DebugLogs> logs;
	vector<DebugLogs> logsCopy;
	DebugLogs logsString;

	bool isCollapsed = false;
};