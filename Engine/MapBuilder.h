#pragma once
#include "Vec2.h"
#include "Colors.h"
#include <assert.h>
#include <vector>


class Mapbuilder
{
public:
	/////////////////////////
	void MapBuilderUI_Keys(class MainWindow& wnd);
	void MapBuilderUI_Graphics(class Graphics& gfx);	
	void MapBuilder_TempLevel(class Graphics& gfx);
	/////////////////////////
private:
	/////////////////////////
	void ColourPalletSet();
	void ColourSelect();	
	void ColourPallet(class Graphics& gfx);
	void ColourSlider(class Graphics& gfx);
	void BevelSlider(class Graphics& gfx);
	/////////////////////////
private:
	/////////////////////////
	int blockwidth = 20;
	int ArrayWidth = 10;
	int Mouse_x;
	int Mouse_y;
	int ArrayGet = 0; 	
	/////////////////////////
	bool Colourpallet = false;
	bool blockBevelsize = false;
	bool maskselect = false;
	bool enemys = false;
	bool powerups = false;
	bool Grid = false;
	bool ReturnCatch = false;
	bool MouseCatch = false;
	bool TempULSet = false;
	////////////////////////
	float r = 0;
	float g = 0;
	float b = 0;
	float BevelSize = 0;
	////////////////////////
	Color selectedColour;
	Color ColourPalletArray[100];
	////////////////////////
	// colour pallet start and block size
	Vec2 UL{ 0.0f , 0.0f };
	Vec2 BR{ 19.0f , 19.0f };
	///////////////////////
	Vec2 BlockPreview{ 300.0f , 50.0f };
	Vec2 BlockPreviewSize{ 400.0f , 150.0f };
	///////////////////////
	Vec2 RedSet{ 50, 300};
	Vec2 GreenSet{ 100, 300 };
	Vec2 BlueSet{ 150 , 300 };
	Vec2 outline_UL{ 49 , 299 };
	Vec2 outline_BR{ 171 , 576 };
	///////////////////////
	Vec2 Bevelset{ 50 , 300 };
	///////////////////////
	Vec2 TempUL{ 0 , 0 };
	Vec2 TempBR{ 20 , 20 };
	float TempBevel = 2;
	Color TempColour;
	///////////////////////
	std::vector<Vec2> TempBlockLayerUL;
	std::vector<Vec2> TempBlockLayerBR;
	std::vector<Color> TempColourLayer;
	std::vector<float> TempBevelLayer;
	//std::vector<float> TempBlockHealth; // <<<<<<<<<< maybe include 
	///////////////////////
	std::vector<Vec2> TempMaskLayer;
	std::vector<int> TempMaskTypeLayer;
	///////////////////////
	std::vector<Vec2> TempEnemyLayer;
	std::vector<int> TempEnemyTypeLayer;
	///////////////////////
};
