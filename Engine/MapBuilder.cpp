#include "MapBuilder.h"
#include "MainWindow.h"
#include "Graphics.h"

void Mapbuilder::MapBuilderUI_Keys(MainWindow& wnd)
{
	////////////////////////
	PlaceBlock = wnd.kbd.KeyIsPressed('P');
	Colourpallet = wnd.kbd.KeyIsPressed('C');
	blockBevelsize = wnd.kbd.KeyIsPressed('B');
	maskselect = wnd.kbd.KeyIsPressed('M');	
	enemys = wnd.kbd.KeyIsPressed('E');
	powerups = wnd.kbd.KeyIsPressed('P');
	Grid = wnd.kbd.KeyIsPressed('G');
	DeleteBack = wnd.kbd.KeyIsPressed('D');
	if (wnd.kbd.KeyIsPressed('S')) //// clears old layers then lets set new layers
	{
		BaseDraw = false;
		BackColourLayer.clear();
		BackBlockLayerUL.clear();
		BackBlockLayerBR.clear();
		BackBevelLayer.clear();
		BaseSet = true;
	}

	//////////////////////// save blocks in layers
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
	
	//////////////////////// <<<<<<<<<<<<< Fix make better !!!!!!
	if (wnd.mouse.RightIsPressed())
	{
		TempULSet = false; // clears top left vec of current block placment
		
	}

	if (wnd.mouse.LeftIsPressed())
	{		
		Mouse = { (float)wnd.mouse.GetPosX(), (float)wnd.mouse.GetPosY() };
	    /////////////////////////// Block Place
		if (!Colourpallet &&
			!blockBevelsize &&
			MouseCatch &&
			!TempULSet &&
			Mouse.x > 0 &&
			Mouse.x < Graphics::ScreenWidth &&
			Mouse.y > 0 &&
			Mouse.y < Graphics::ScreenHeight)
	    {
			TempUL.x = (float)Mouse.x;
			TempUL.y = (float)Mouse.y;
			TempULSet = true;			
		}
		if(!Colourpallet &&
			!blockBevelsize &&
			MouseCatch && 
			TempULSet &&
			Mouse.x > 0 &&
			Mouse.x < Graphics::ScreenWidth &&
			Mouse.y > 0 &&
			Mouse.y < Graphics::ScreenHeight )
		{
			TempBR.x = (float)Mouse.x;
			TempBR.y = (float)Mouse.y;
		}
		
		///////////////////////////
		if (Mouse.x >= 0 &&
			Mouse.x <= ArrayWidth * blockwidth &&
			Mouse.y >= 0 &&
			Mouse.y <= ArrayWidth * blockwidth &&
			Colourpallet)
		{
			ColourSelect();
		}
		///////////////////////////
		if (coltest.CollideTest( RedSet , RedSet + 20 , Mouse) &&
			Colourpallet)
		{
			RedSet.y = (float)Mouse.y - 10; // centres to mouse
		}
		///////////////////////////
		if (coltest.CollideTest( GreenSet , GreenSet  + 20 , Mouse) &&
			Colourpallet)
		{
			GreenSet.y = (float)Mouse.y - 10; // centres to mouse
		}
		///////////////////////////
		if (coltest.CollideTest(BlueSet, BlueSet + 20 , Mouse) &&
			Colourpallet)
		{
			BlueSet.y = (float)Mouse.y - 10; // centres to mouse
		}
		///////////////////////////
		if (coltest.CollideTest(Bevelset, (Bevelset + 20), Mouse ) &&
			blockBevelsize)
		{
			Bevelset.y = (float)Mouse.y - 10; // centres to mouse
		}
		/////////////////////////// deletes block out the backblock layers
		if (!Colourpallet &&
			!blockBevelsize &&

			!PlaceBlock &&
			Mouse.x > 0 &&
			Mouse.x < Graphics::ScreenWidth &&
			Mouse.y > 0 &&
			Mouse.y < Graphics::ScreenHeight)
		{
			auto Arraysize = BackBlockLayerUL.size();
			for (int i = 0; i < Arraysize; i++)
			{
				if (Mouse.x > BackBlockLayerUL[i].x &&
					Mouse.x < BackBlockLayerBR[i].x &&
					Mouse.y > BackBlockLayerUL[i].y &&
					Mouse.y < BackBlockLayerBR[i].y )
				{
					BackColourLayer.erase(BackColourLayer.begin() + i);
					BackBlockLayerUL.erase(BackBlockLayerUL.begin() + i);
					BackBlockLayerBR.erase(BackBlockLayerBR.begin() + i);
					BackBevelLayer.erase(BackBevelLayer.begin() + i);
					break;
				}
			}
		}
		MouseRelease = false;
		///////////////////////////
	}
	else
		{			
			MouseCatch = true;
			MouseRelease = true;
		}
}

void Mapbuilder::MapBuilderUI_Graphics( Graphics& gfx)
{
	BaseBackSet();
	BaseBackDraw(gfx);
	if(PlaceBlock)MapBuilder_TempLevel(gfx);
	if(PlaceBlock)gfx.Drawrecbeveled(TempUL, TempBR, TempBevel, TempColour);
	ColourPallet(gfx);
	ColourSlider(gfx);
	BevelSlider(gfx);
	
}

void Mapbuilder::MapBuilder_TempLevel(Graphics & gfx)
{	
	int VectorSize = (int)TempBlockLayerBR.size();
	for (int i = 0; i < VectorSize; i++)
	{
		gfx.Drawrecbeveled(TempBlockLayerUL[i], TempBlockLayerBR[i], TempBevelLayer[i], TempColourLayer[i]);
	}
}

void Mapbuilder::ColourSelect()
{
	//// gets colour in the array when you click the left mouse
	assert(Mouse.x >= 0 &&
		   Mouse.x <= ArrayWidth * blockwidth &&
		   Mouse.y >= 0 &&
		   Mouse.y < ArrayWidth * blockwidth);

	Mouse.x = (Mouse.x / blockwidth);
	Mouse.y = (Mouse.y / blockwidth);
	ArrayGet = (int)((Mouse.y * ArrayWidth) + Mouse.x);
	selectedColour = ColourPalletArray[ArrayGet];
	TempColour = selectedColour;
}

void Mapbuilder::BaseBackDraw(Graphics & gfx)
{
	auto Arraysize = BackBlockLayerUL.size();
	if (BaseDraw)
	{
		for (int i = 0; i < Arraysize; i++)
		{
			gfx.Drawrecbeveled(BackBlockLayerUL[i], BackBlockLayerBR[i], BackBevelLayer[i], BackColourLayer[i]);
		}
	}
}

void Mapbuilder::BaseBackSet()
{
	if (BaseSet)
	{
		///////////////////////////////////
		unsigned char rM = 0u;
		unsigned char gM = 0u;
		unsigned char bM = 0u;
		///////////////////////////////////
		float rMod = 0.f;
		float gMod = 0.f;
		float bMod = 0.f;
		float x = 0.f;
		float y = 0.f;
		///////////////////////////////////
		for (int i = 0; i < 1200; i++)
		{
			BackColourLayer.push_back({ rM,gM,bM });
			BackBlockLayerUL.push_back({ x ,y });
			BackBlockLayerBR.push_back({ x + 18 ,y + 18 });
			BackBevelLayer.push_back(2);
			////////////
			rM = (unsigned char)rMod;
			gM = (unsigned char)gMod;
			bM = (unsigned char)bMod;
			if (i < 600)
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
			///////////
			x += blockwidth ;
			if (x + blockwidth > 800)
			{
				x = 0;
				y += blockwidth ;
			}
		}
		BaseDraw = true;
		BaseSet = false;
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


