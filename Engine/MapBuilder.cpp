#include "MapBuilder.h"
#include "MainWindow.h"

void Mapbuilder::MapBuilderUI_Keys(MainWindow& wnd)
{

	if (wnd.kbd.KeyIsPressed('C'))
	{
		Colourpallet = true;
		// if true load colour into temp block colour
	}
	else
	{
		Colourpallet = false;
		// clear block colour
	}
	if (wnd.kbd.KeyIsPressed('B'))
	{
		blockBevelsize = true;

	}
	else
	{
		blockBevelsize = false;

	}
	if (wnd.kbd.KeyIsPressed('M'))
	{
		maskselect = true;

	}
	else
	{
		maskselect = false;

	}
	if (wnd.kbd.KeyIsPressed('E'))
	{
		enemys = true;

	}
	else
	{
		enemys = false;

	}
	if (wnd.kbd.KeyIsPressed('P'))
	{
		bool powerups = true;

	}
	else
	{
		bool powerups = false;

	}
}

void Mapbuilder::MapBuilderUI_Graphics( Graphics& gfx)
{
	if (Colourpallet)
	{
		gfx.Drawrec(UL, BR, Colors::Magenta);
	}
}
