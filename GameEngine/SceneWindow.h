#include "Application.h"

using namespace std;

class SceneWindows
{
public:
	static void PrintScene(Application* app);

	static ImVec2 NormMousePos(float x, float y, float w, float h, ImVec2 point);

	static bool isHovered;

private:
	
	static ImVec2 sizeWindScn;

};