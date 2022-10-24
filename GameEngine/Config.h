#include "Application.h"

using namespace std;

class ConfigWindow
{
public:

	static void PrintConfig(Application* app);

	static int FPSLimit;

private:

	static bool isFullScreen;
	static bool isRe;
	static bool isBor;

	static vector<float> fpsLog;
	static vector<float> timeLog;
};
