#include "Application.h"

using namespace std;

class ConfigWindow
{
public:

	static void PrintConfig();

	static int FPSLimit;

private:

	static vector<float> fpsLog;
	static vector<float> timeLog;
};
