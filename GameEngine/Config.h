#include "Application.h"
#include <deque>

using namespace std;

class ConfigWindow
{
public:

	static void PrintConfig(Application* app, float dt);

	static int fpsLimit;

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

	static vector<float> fpsDebug;
	static vector<float> fpsDebugAux;
	static vector<float> timeDebug;
	static vector<float> timeDebugAux;
};
