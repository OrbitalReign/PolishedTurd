#pragma once
#include "Vec2.h"


class Mapbuilder
{
public:
	void MapBuilderUI_Keys(class MainWindow& wnd);
	void MapBuilderUI_Graphics(class Graphics& gfx);
private:
	bool Colourpallet = false;
	bool blockBevelsize = false;
	bool maskselect = false;
	bool enemys = false;
	bool powerups = false;
	Vec2 UL{ 0 , 0 };
	Vec2 BR{ 20,20 };
};
