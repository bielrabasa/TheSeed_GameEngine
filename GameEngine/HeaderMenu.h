#include "Application.h"

using namespace std;

class HMenu
{
public:

	static void PrintMenu(Application* app);
	static void ThemeStylePopUp();
	static void ThemeStyleMenuBar();
	static void ThemeStyleWind();

	static void Init();

	static void cleanUp();

	static bool quit;

	static bool openInspector;
	static bool openConsole;
	static bool openConig;
	static bool openHierarchy;
	static bool openAssets;

	static bool popUpAbout;

	static bool isWireframe;
	static bool isBoundingBoxes;

	static bool styleSelectD;
	static bool styleSelectL;
	static bool styleSelectSD;
	static bool styleSelectP;
	static int colorStyle;

private:
	static float colorWind[4];
	static float colorText[4];

	static uint playTexture;
	static uint stopTexture;
	static uint pausedTexture;
	static uint NOpausedTexture;
	static uint speedx1;
	static uint speedx2;
	static uint speedx3;

	static uint pauseButton;
	static uint playButton;
	static uint speedButton;
};