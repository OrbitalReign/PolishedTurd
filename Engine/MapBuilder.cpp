#include "MapBuilder.h"
#include "MainWindow.h"
#include "Graphics.h"

void Mapbuilder::MapBuilderUI_Keys(MainWindow& wnd)
{
	if (wnd.kbd.KeyIsPressed('C'))
	{
		Colourpallet = true;
	}
	else
	{
		Colourpallet = false;
	}
	//////////////////////////
	if (wnd.kbd.KeyIsPressed('B'))
	{
		blockBevelsize = true;
	}
	else
	{
		blockBevelsize = false;
	}
	/////////////////////////
	if (wnd.kbd.KeyIsPressed('M'))
	{
		maskselect = true;
	}
	else
	{
		maskselect = false;
	}
	/////////////////////////
	if (wnd.kbd.KeyIsPressed('E'))
	{
		enemys = true;
	}
	else
	{
		enemys = false;
	}
	/////////////////////////
	if (wnd.kbd.KeyIsPressed('P'))
	{
		powerups = true;
	}
	else
	{
	    powerups = false;
	}
	/////////////////////////
	if (wnd.kbd.KeyIsPressed('G'))
	{
		Grid = true;
	}
	else
	{
		Grid = false;
	}
	////////////////////////
	if (wnd.kbd.KeyIsPressed(VK_RETURN) && !ReturnCatch)
	{
		
		TempBlockLayerUL.push_back(TempUL);
		TempBlockLayerBR.push_back(TempBR);
		TempBevelLayer.push_back(TempBevel);
		TempColourLayer.push_back(TempColour);
		ReturnCatch = true;
		TempULSet = false;
	}
	else if (!wnd.kbd.KeyIsPressed(VK_RETURN))
	{
		ReturnCatch = false;
	}
	////////////////////////
	
	//////////////////////// <<<<<<<<<<<<< Fix make better !!!!!!
	if (wnd.mouse.RightIsPressed())
	{
		TempULSet = false;
	}
	if (wnd.mouse.LeftIsPressed() )
	{		
		Mouse_x = wnd.mouse.GetPosX();
	    Mouse_y = wnd.mouse.GetPosY();
	    ///////////////////////////
		if (!Colourpallet &&
			!blockBevelsize &&
			MouseCatch &&
			!TempULSet &&
			Mouse_x > 0 &&
			Mouse_x < Graphics::ScreenWidth &&
			Mouse_y > 0 &&
			Mouse_y < Graphics::ScreenHeight)
	    {
			TempUL.x = (float)Mouse_x;
			TempUL.y = (float)Mouse_y;
			TempULSet = true;			
		}
		if(!Colourpallet &&
			!blockBevelsize &&
			MouseCatch && 
			TempULSet &&
			Mouse_x > 0 &&
			Mouse_x < Graphics::ScreenWidth &&
			Mouse_y > 0 &&
			Mouse_y < Graphics::ScreenHeight )
		{
			TempBR.x = (float)Mouse_x;
			TempBR.y = (float)Mouse_y;
		}
		///////////////////////////
		if (Mouse_x >= 0 &&
			Mouse_x <= ArrayWidth * blockwidth &&
			Mouse_y >= 0 &&
			Mouse_y <= ArrayWidth * blockwidth &&
			Colourpallet)
		{
			ColourSelect();
		}
		///////////////////////////
		if (Mouse_x >= RedSet.x &&
			Mouse_x <= RedSet.x + 20 &&
			Mouse_y >= RedSet.y - 5 && 
			Mouse_y <= RedSet.y + 25  &&
			Colourpallet)
		{
			RedSet.y = (float)Mouse_y - 10; // centres to mouse
		}
		///////////////////////////
		if (Mouse_x >= GreenSet.x &&
			Mouse_x <= GreenSet.x + 20 &&
			Mouse_y >= GreenSet.y -5 &&
			Mouse_y <= GreenSet.y + 25 &&
			Colourpallet)
		{
			GreenSet.y = (float)Mouse_y - 10; // centres to mouse
		}
		///////////////////////////
		if (Mouse_x >= BlueSet.x &&
			Mouse_x <= BlueSet.x + 20 &&
			Mouse_y >= BlueSet.y -5 &&
			Mouse_y <= BlueSet.y + 25 &&
			Colourpallet)
		{
			BlueSet.y = (float)Mouse_y - 10; // centres to mouse
		}
		///////////////////////////
		if (Mouse_x >= Bevelset.x &&
			Mouse_x <= Bevelset.x + 20 &&
			Mouse_y >= Bevelset.y - 5 &&
			Mouse_y <= Bevelset.y + 25 &&
			blockBevelsize)
		{
			Bevelset.y = (float)Mouse_y - 10; // centres to mouse
		}
		else
		{			
			MouseCatch = true;
		}///////////////////////////
	}
}

void Mapbuilder::MapBuilderUI_Graphics( Graphics& gfx)
{
	BaseBack(gfx);
	MapBuilder_TempLevel(gfx);
	ColourPallet(gfx);
	ColourSlider(gfx);
	BevelSlider(gfx);
	gfx.Drawrecbeveled(TempUL, TempBR, TempBevel, TempColour);
}

void Mapbuilder::MapBuilder_TempLevel(Graphics & gfx)
{
	int VectorSize = (int)TempBlockLayerBR.size();
	for (int i = 0; i < VectorSize ; i++)
	{
		gfx.Drawrecbeveled(TempBlockLayerUL[i], TempBlockLayerBR[i], TempBevelLayer[i], TempColourLayer[i]);
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
	TempColour = selectedColour;
}

void Mapbuilder::BaseBack(Graphics & gfx)
{
	Vec2 temp_A{ 0, 0 };
	Vec2 temp_B{ 19,19 };
	int index = 0;

	///////////////////////////////////
	unsigned char rM = 0u;
	unsigned char gM = 0u;
	unsigned char bM = 0u;
	///////////////////////////////////
	float rMod = 0;
	float gMod = 0;
	float bMod = 0;
	///////////////////////////////////
	///////////////////////////
	for (int y = blockwidth; y <= Graphics::ScreenHeight; y += blockwidth)
	{
		for (int x = blockwidth; x <= Graphics::ScreenWidth; x += blockwidth)
		{
			gfx.Drawrecbeveled(temp_A, temp_B, 2, Color(rM , gM ,bM) );
			temp_A.x = (float)x + 1;
			temp_B.x = (float)x + blockwidth - 1;
			index++;
			if (index < 600)
			{
			
				rMod += r / 1000;
				gMod += g / 1000;
				bMod += b / 1000;
			}
			else
			{
				rMod -= r / 1000;
				gMod -= g / 1000;
				bMod -= b / 1000;
			}
			rM = (unsigned char)rMod;
			gM = (unsigned char)gMod;
			bM = (unsigned char)bMod;
		}
		temp_A.y = (float)y + 1;
		temp_B.y = (float)y + blockwidth - 1;
		temp_A.x = 0.0f;
		temp_B.x = (float)blockwidth - 1;
	}
}


void Mapbuilder::ColourPalletSet()
{
	///////////////////////////////////
	unsigned char rM = 0u;
	unsigned char gM = 0u;
	unsigned char bM = 0u;
	///////////////////////////////////
	float rMod = 0;
	float gMod = 0;
	float bMod = 0;
	///////////////////////////////////
	for (int i = 0; i < 100 ; i ++)
	{
		ColourPalletArray[i] = { rM,gM,bM };
		rM = (unsigned char)rMod;
		gM = (unsigned char)gMod;
		bM = (unsigned char)bMod;
		rMod += r / 100;
		gMod += g / 100;
		bMod += b / 100;
	}
}

void Mapbuilder::ColourPallet(Graphics & gfx)
{
	if (Colourpallet)
	{
		ColourPalletSet();
		gfx.Drawrecbeveled(BlockPreview , BlockPreviewSize,BevelSize , selectedColour);		
		Vec2 temp_A = UL;
		Vec2 temp_B = BR;
		int ArrayIndex = 0;
		int gridsize = (blockwidth * ArrayWidth) + blockwidth;
		///////////////////////////
		for (int y = blockwidth; y < gridsize; y += blockwidth )
		{
			for (int x = blockwidth; x < gridsize ; x += blockwidth )
			{						       				
				gfx.Drawrecbeveled(temp_A, temp_B, 2, ColourPalletArray[ArrayIndex]);
				temp_A.x = (float)x + 1 ;
				temp_B.x = (float)x + blockwidth -1 ;
				++ArrayIndex;
			}
			temp_A.y = (float)y + 1 ;
			temp_B.y = (float)y + blockwidth -1 ;
			temp_A.x = 0.0f ;
			temp_B.x = (float)blockwidth - 1;
		}
	}
}

void Mapbuilder::ColourSlider( Graphics& gfx)
{
	if (Colourpallet)
	{
		//Red
		gfx.Drawrecbeveled(RedSet, RedSet + 20, 2, Color( 200 , 0 ,0));
		//Green
		gfx.Drawrecbeveled(GreenSet, GreenSet + 20, 2, Color( 0 , 200 , 0));
		// Blue
		gfx.Drawrecbeveled(BlueSet, BlueSet + 20, 2, Color( 0 , 0 , 200));
		// outline
		gfx.DrawRecFrame(outline_UL, outline_BR, Colors::White);
		// sets r,g,b to the sliders y position.
		r = (RedSet.y - 300);
		g = (GreenSet.y - 300);
		b = (BlueSet.y - 300);
		/////////////////////////////
		if (RedSet.y < 300)
		{
			RedSet.y = 300;
		}
		else if (RedSet.y + 20 > 575)
		{
			RedSet.y = 555;
		}
		if (GreenSet.y < 300)
		{
			GreenSet.y = 300;
		}
		else if (GreenSet.y + 20 > 575)
		{
			GreenSet.y = 555;
		}
		if (BlueSet.y < 300)
		{
			BlueSet.y = 300;
		}
		else if (BlueSet.y +20 > 575)
		{
			BlueSet.y = 555;
		}
	}
}

void Mapbuilder::BevelSlider(Graphics& gfx)
{
	if (blockBevelsize)
	{
		gfx.DrawRecFrame(outline_UL, outline_BR, Colors::White);
		gfx.Drawrecbeveled(BlockPreview, BlockPreviewSize, BevelSize, selectedColour);
		gfx.Drawrecbeveled(Bevelset, Bevelset + 20, 2, Colors::Cyan);
		BevelSize = ((Bevelset.y - 300) / 10);
		TempBevel = BevelSize;
		//////////////////////////
		if (Bevelset.y < 299)
		{
			Bevelset.y = 300;
		}
		else if (Bevelset.y + 20 > 575)
		{
			Bevelset.y = 555;
		}

	}
}
