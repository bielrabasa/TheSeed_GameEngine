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

	static bool vSync;
	static bool lights;
	static bool depths;
	static bool isCullFaces;
	static bool colorM;
	static bool text2D;
	static float bright;
	static float bright_aux;

	static vector<float> fpsLog;
	static vector<float> timeLog;

};
