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
	if (wnd.mouse.LeftIsPressed())
	{
		Mouse_x = wnd.mouse.GetPosX();
		Mouse_y = wnd.mouse.GetPosY();
		if (Mouse_x >= 0 &&
			Mouse_x <= ArrayWidth * blockwidth &&
			Mouse_y >= 0 &&
			Mouse_y < ArrayWidth * blockwidth)
		{
			ColourSelect();
		}
		
	}
}

void Mapbuilder::MapBuilderUI_Graphics( Graphics& gfx)
{
	if (Colourpallet)
	{
		gfx.Drawrecbeveled(BlockPreview , BlockPreviewSize,10 , selectedColour);
		//// turn into array ////
		 Color bev_col(50u, 50u, 10u);
		float scalerincement = 0.1f;
		int blockwidth = 20;
		Vec2 temp_A = UL;
		Vec2 temp_B = BR;
		int i = 0;
		for (int y = 0; y < 200; y += blockwidth + 1)
		{
			for (int x = 0; x < 200; x += blockwidth + 1)
			{						       				
				gfx.Drawrecbeveled(temp_A, temp_B, 2, ColourPalletArray[i]);
				temp_A.x = (float)x + 1;
				temp_B.x = (float)x + blockwidth;
				scalerincement += 0.1f;
				i++;
			}
			temp_A.y = (float)y + 1;
			temp_B.y = (float)y + blockwidth;
			temp_A.x = 0;
			temp_B.x = 20;
		}
		/////////
	}
}

void Mapbuilder::ColourSelect()
{
	//// gets colour in the array when you click the left mouse
	assert(Mouse_x >= 0 &&
		   Mouse_x <= ArrayWidth * blockwidth &&
		   Mouse_y >= 0 &&
		   Mouse_y < ArrayWidth * blockwidth);

	Mouse_x = (int)(Mouse_x / blockwidth);
	Mouse_y = (int)(Mouse_y / blockwidth);
	ArrayGet = (Mouse_y * ArrayWidth) + Mouse_x;
	selectedColour = ColourPalletArray[ArrayGet];
}

void Mapbuilder::ColourPalletSet()
{
	unsigned char r = 0u;
	unsigned char g = 0u;
	unsigned char b = 0u;

	for (int i = 0; i < 100 ; i ++)
	{
		ColourPalletArray[i] = { r,g,b };
		r++;
		g++;
		b++;
	}
}
