#include "Application.h"

using namespace std;

class HMenu
{
public:

	static void PrintMenu(Application* app);
	static void ThemeStylePopUp();
	static void ThemeStyleMenuBar();
	static void ThemeStyleWind();

	static bool quit;

	static bool openInspector;
	static bool openConsole;
	static bool openConig;
	static bool openHierarchy;

	static bool popUpAbout;

	static bool isWireframe;

	static bool styleSelectD;
	static bool styleSelectL;
	static bool styleSelectSD;
	static bool styleSelectP;
	static int colorStyle;

private:
	static float colorWind[4];
	static float colorText[4];

};