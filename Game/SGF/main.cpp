#include "sgfPCH.h"

int main()
{
	sgf::Win32App app("Game");
	app.Initialize(0, NULL);
	sgf::Material mtrl("shader_buildin/diffuse.xml");
	app.Run();
	app.Destroy();
	return 0;
}