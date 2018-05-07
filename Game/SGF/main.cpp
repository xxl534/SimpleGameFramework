#include "sgfPCH.h"

int main()
{
	int i = sizeof(sgf::Win32App);
	sgf::Win32App app("Game");
	app.Initialize(0, NULL);
	app.Run();
	app.Destroy();
	return 0;
}