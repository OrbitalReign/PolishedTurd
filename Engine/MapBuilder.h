#pragma once
#include "Vec2.h"
#include "Colors.h"
#include <assert.h>


class Mapbuilder
{
public:
	void MapBuilderUI_Keys(class MainWindow& wnd);
	void MapBuilderUI_Graphics(class Graphics& gfx);
	void ColourSelect();
	void ColourPalletSet();
private:
	int blockwidth = 20;
	int ArrayWidth = 10;
	int Mouse_x;
	int Mouse_y;
	int ArrayGet;
	
	bool Colourpallet = false;
	bool blockBevelsize = false;
	bool maskselect = false;
	bool enemys = false;
	bool powerups = false;
	Color selectedColour;
	Color ColourPalletArray[100];
	// colour pallet start and block size
	Vec2 UL{ 0 , 0 };
	Vec2 BR{ 19,19 };
	////////////
	Vec2 BlockPreview{ 300 , 50 };
	Vec2 BlockPreviewSize{ 400, 150 };
};
