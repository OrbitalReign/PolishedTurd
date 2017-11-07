#include "Dude.h"
#include "MainWindow.h"
#include "Graphics.h"
#include <cmath>
#define PI 3.1415926536


void Dude::Update( MainWindow& wnd)
{
	if (wnd.kbd.KeyIsPressed('W'))
	{
		Base_y -= 2;
	}
	if (wnd.kbd.KeyIsPressed('A'))
	{
		Base_x -= 2;
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		Base_y += 2;
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		Base_x += 2;
	}

	Head = { (float)Base_x,(float)Base_y };
	Neck = { (float)Base_x + 10, (float)Base_y + 20 };
	FakeSholderLeft = { Head.x , Neck.y };
	FakeSholderRight = { Head.x + 20, Neck.y };
	Waist = { Neck.x , Neck.y + 20 };



	///////////////////////
	if (ScreenCheck.BoundsCheck(wnd.mouse.GetPosX(), wnd.mouse.GetPosY()))
	{
		Target = { (float)wnd.mouse.GetPosX() , (float)wnd.mouse.GetPosY() };
		
		if ( wnd.mouse.LeftIsPressed() )
		{
			Shooting();
		}
		else
		{
			RecoilLeft = 10;
			RecoilRight = 10;
		}
	}
	

	///////////////////////	
	Arms();
	Jumping();
	///////////////////////

}


void Dude::DrawFace(Graphics & gfx)
{
	gfx.PutPixel(7 +Base_x, 0 +Base_y, 0, 0, 0);
	gfx.PutPixel(8 +Base_x, 0 +Base_y, 0, 0, 0);
	gfx.PutPixel(9 +Base_x, 0 +Base_y, 0, 0, 0);
	gfx.PutPixel(10 +Base_x, 0 +Base_y, 0, 0, 0);
	gfx.PutPixel(11 +Base_x, 0 +Base_y, 0, 0, 0);
	gfx.PutPixel(12 +Base_x, 0 +Base_y, 0, 0, 0);
	gfx.PutPixel(5 +Base_x, 1 +Base_y, 0, 0, 0);
	gfx.PutPixel(6 +Base_x, 1 +Base_y, 0, 0, 0);
	gfx.PutPixel(7 +Base_x, 1 +Base_y, 254, 221, 88);
	gfx.PutPixel(8 +Base_x, 1 +Base_y, 254, 221, 88);
	gfx.PutPixel(9 +Base_x, 1 +Base_y, 254, 221, 88);
	gfx.PutPixel(10 +Base_x, 1 +Base_y, 254, 221, 88);
	gfx.PutPixel(11 +Base_x, 1 +Base_y, 254, 221, 88);
	gfx.PutPixel(12 +Base_x, 1 +Base_y, 254, 221, 88);
	gfx.PutPixel(13 +Base_x, 1 +Base_y, 0, 0, 0);
	gfx.PutPixel(14 +Base_x, 1 +Base_y, 0, 0, 0);
	gfx.PutPixel(3 +Base_x, 2 +Base_y, 0, 0, 0);
	gfx.PutPixel(4 +Base_x, 2 +Base_y, 0, 0, 0);
	gfx.PutPixel(5 +Base_x, 2 +Base_y, 254, 221, 88);
	gfx.PutPixel(6 +Base_x, 2 +Base_y, 254, 221, 88);
	gfx.PutPixel(7 +Base_x, 2 +Base_y, 254, 221, 88);
	gfx.PutPixel(8 +Base_x, 2 +Base_y, 254, 221, 88);
	gfx.PutPixel(9 +Base_x, 2 +Base_y, 254, 221, 88);
	gfx.PutPixel(10 +Base_x, 2 +Base_y, 254, 221, 88);
	gfx.PutPixel(11 +Base_x, 2 +Base_y, 254, 221, 88);
	gfx.PutPixel(12 +Base_x, 2 +Base_y, 254, 221, 88);
	gfx.PutPixel(13 +Base_x, 2 +Base_y, 254, 221, 88);
	gfx.PutPixel(14 +Base_x, 2 +Base_y, 254, 221, 88);
	gfx.PutPixel(15 +Base_x, 2 +Base_y, 0, 0, 0);
	gfx.PutPixel(16 +Base_x, 2 +Base_y, 0, 0, 0);
	gfx.PutPixel(2 +Base_x, 3 +Base_y, 0, 0, 0);
	gfx.PutPixel(3 +Base_x, 3 +Base_y, 254, 221, 88);
	gfx.PutPixel(4 +Base_x, 3 +Base_y, 254, 221, 88);
	gfx.PutPixel(5 +Base_x, 3 +Base_y, 254, 221, 88);
	gfx.PutPixel(6 +Base_x, 3 +Base_y, 254, 221, 88);
	gfx.PutPixel(7 +Base_x, 3 +Base_y, 254, 221, 88);
	gfx.PutPixel(8 +Base_x, 3 +Base_y, 254, 221, 88);
	gfx.PutPixel(9 +Base_x, 3 +Base_y, 254, 221, 88);
	gfx.PutPixel(10 +Base_x, 3 +Base_y, 254, 221, 88);
	gfx.PutPixel(11 +Base_x, 3 +Base_y, 254, 221, 88);
	gfx.PutPixel(12 +Base_x, 3 +Base_y, 254, 221, 88);
	gfx.PutPixel(13 +Base_x, 3 +Base_y, 254, 221, 88);
	gfx.PutPixel(14 +Base_x, 3 +Base_y, 254, 221, 88);
	gfx.PutPixel(15 +Base_x, 3 +Base_y, 254, 221, 88);
	gfx.PutPixel(16 +Base_x, 3 +Base_y, 254, 221, 88);
	gfx.PutPixel(17 +Base_x, 3 +Base_y, 0, 0, 0);
	gfx.PutPixel(2 +Base_x, 4 +Base_y, 0, 0, 0);
	gfx.PutPixel(3 +Base_x, 4 +Base_y, 254, 221, 88);
	gfx.PutPixel(4 +Base_x, 4 +Base_y, 254, 221, 88);
	gfx.PutPixel(5 +Base_x, 4 +Base_y, 254, 221, 88);
	gfx.PutPixel(6 +Base_x, 4 +Base_y, 254, 221, 88);
	gfx.PutPixel(7 +Base_x, 4 +Base_y, 254, 221, 88);
	gfx.PutPixel(8 +Base_x, 4 +Base_y, 254, 221, 88);
	gfx.PutPixel(9 +Base_x, 4 +Base_y, 254, 221, 88);
	gfx.PutPixel(10 +Base_x, 4 +Base_y, 254, 221, 88);
	gfx.PutPixel(11 +Base_x, 4 +Base_y, 254, 221, 88);
	gfx.PutPixel(12 +Base_x, 4 +Base_y, 254, 221, 88);
	gfx.PutPixel(13 +Base_x, 4 +Base_y, 254, 221, 88);
	gfx.PutPixel(14 +Base_x, 4 +Base_y, 254, 221, 88);
	gfx.PutPixel(15 +Base_x, 4 +Base_y, 254, 221, 88);
	gfx.PutPixel(16 +Base_x, 4 +Base_y, 254, 221, 88);
	gfx.PutPixel(17 +Base_x, 4 +Base_y, 0, 0, 0);
	gfx.PutPixel(1 +Base_x, 5 +Base_y, 0, 0, 0);
	gfx.PutPixel(2 +Base_x, 5 +Base_y, 254, 221, 88);
	gfx.PutPixel(3 +Base_x, 5 +Base_y, 0, 0, 0);
	gfx.PutPixel(4 +Base_x, 5 +Base_y, 0, 0, 0);
	gfx.PutPixel(5 +Base_x, 5 +Base_y, 254, 221, 88);
	gfx.PutPixel(6 +Base_x, 5 +Base_y, 254, 221, 88);
	gfx.PutPixel(7 +Base_x, 5 +Base_y, 254, 221, 88);
	gfx.PutPixel(8 +Base_x, 5 +Base_y, 254, 221, 88);
	gfx.PutPixel(9 +Base_x, 5 +Base_y, 254, 221, 88);
	gfx.PutPixel(10 +Base_x, 5 +Base_y, 254, 221, 88);
	gfx.PutPixel(11 +Base_x, 5 +Base_y, 0, 0, 0);
	gfx.PutPixel(12 +Base_x, 5 +Base_y, 0, 0, 0);
	gfx.PutPixel(13 +Base_x, 5 +Base_y, 0, 0, 0);
	gfx.PutPixel(14 +Base_x, 5 +Base_y, 0, 0, 0);
	gfx.PutPixel(15 +Base_x, 5 +Base_y, 254, 221, 88);
	gfx.PutPixel(16 +Base_x, 5 +Base_y, 254, 221, 88);
	gfx.PutPixel(17 +Base_x, 5 +Base_y, 254, 221, 88);
	gfx.PutPixel(18 +Base_x, 5 +Base_y, 0, 0, 0);
	gfx.PutPixel(1 +Base_x, 6 +Base_y, 0, 0, 0);
	gfx.PutPixel(2 +Base_x, 6 +Base_y, 0, 0, 0);
	gfx.PutPixel(3 +Base_x, 6 +Base_y, 255, 255, 255);
	gfx.PutPixel(4 +Base_x, 6 +Base_y, 0, 0, 0);
	gfx.PutPixel(5 +Base_x, 6 +Base_y, 0, 0, 0);
	gfx.PutPixel(6 +Base_x, 6 +Base_y, 254, 221, 88);
	gfx.PutPixel(7 +Base_x, 6 +Base_y, 254, 221, 88);
	gfx.PutPixel(8 +Base_x, 6 +Base_y, 254, 221, 88);
	gfx.PutPixel(9 +Base_x, 6 +Base_y, 254, 221, 88);
	gfx.PutPixel(10 +Base_x, 6 +Base_y, 0, 0, 0);
	gfx.PutPixel(11 +Base_x, 6 +Base_y, 255, 255, 255);
	gfx.PutPixel(12 +Base_x, 6 +Base_y, 255, 255, 255);
	gfx.PutPixel(13 +Base_x, 6 +Base_y, 0, 0, 0);
	gfx.PutPixel(14 +Base_x, 6 +Base_y, 0, 0, 0);
	gfx.PutPixel(15 +Base_x, 6 +Base_y, 0, 0, 0);
	gfx.PutPixel(16 +Base_x, 6 +Base_y, 254, 221, 88);
	gfx.PutPixel(17 +Base_x, 6 +Base_y, 254, 221, 88);
	gfx.PutPixel(18 +Base_x, 6 +Base_y, 0, 0, 0);
	gfx.PutPixel(0 +Base_x, 7 +Base_y, 0, 0, 0);
	gfx.PutPixel(1 +Base_x, 7 +Base_y, 0, 0, 0);
	gfx.PutPixel(2 +Base_x, 7 +Base_y, 255, 255, 255);
	gfx.PutPixel(3 +Base_x, 7 +Base_y, 255, 255, 255);
	gfx.PutPixel(4 +Base_x, 7 +Base_y, 0, 0, 0);
	gfx.PutPixel(5 +Base_x, 7 +Base_y, 0, 0, 0);
	gfx.PutPixel(6 +Base_x, 7 +Base_y, 254, 221, 88);
	gfx.PutPixel(7 +Base_x, 7 +Base_y, 254, 221, 88);
	gfx.PutPixel(8 +Base_x, 7 +Base_y, 254, 221, 88);
	gfx.PutPixel(9 +Base_x, 7 +Base_y, 254, 221, 88);
	gfx.PutPixel(10 +Base_x, 7 +Base_y, 0, 0, 0);
	gfx.PutPixel(11 +Base_x, 7 +Base_y, 255, 255, 255);
	gfx.PutPixel(12 +Base_x, 7 +Base_y, 255, 255, 255);
	gfx.PutPixel(13 +Base_x, 7 +Base_y, 0, 0, 0);
	gfx.PutPixel(14 +Base_x, 7 +Base_y, 0, 0, 0);
	gfx.PutPixel(15 +Base_x, 7 +Base_y, 0, 0, 0);
	gfx.PutPixel(16 +Base_x, 7 +Base_y, 254, 221, 88);
	gfx.PutPixel(17 +Base_x, 7 +Base_y, 254, 221, 88);
	gfx.PutPixel(18 +Base_x, 7 +Base_y, 254, 221, 88);
	gfx.PutPixel(19 +Base_x, 7 +Base_y, 0, 0, 0);
	gfx.PutPixel(0 +Base_x, 8 +Base_y, 0, 0, 0);
	gfx.PutPixel(1 +Base_x, 8 +Base_y, 0, 0, 0);
	gfx.PutPixel(2 +Base_x, 8 +Base_y, 255, 255, 255);
	gfx.PutPixel(3 +Base_x, 8 +Base_y, 255, 255, 255);
	gfx.PutPixel(4 +Base_x, 8 +Base_y, 255, 255, 255);
	gfx.PutPixel(5 +Base_x, 8 +Base_y, 0, 0, 0);
	gfx.PutPixel(6 +Base_x, 8 +Base_y, 254, 221, 88);
	gfx.PutPixel(7 +Base_x, 8 +Base_y, 254, 221, 88);
	gfx.PutPixel(8 +Base_x, 8 +Base_y, 254, 221, 88);
	gfx.PutPixel(9 +Base_x, 8 +Base_y, 254, 221, 88);
	gfx.PutPixel(10 +Base_x, 8 +Base_y, 0, 0, 0);
	gfx.PutPixel(11 +Base_x, 8 +Base_y, 255, 255, 255);
	gfx.PutPixel(12 +Base_x, 8 +Base_y, 255, 255, 255);
	gfx.PutPixel(13 +Base_x, 8 +Base_y, 255, 255, 255);
	gfx.PutPixel(14 +Base_x, 8 +Base_y, 255, 255, 255);
	gfx.PutPixel(15 +Base_x, 8 +Base_y, 0, 0, 0);
	gfx.PutPixel(16 +Base_x, 8 +Base_y, 254, 221, 88);
	gfx.PutPixel(17 +Base_x, 8 +Base_y, 254, 221, 88);
	gfx.PutPixel(18 +Base_x, 8 +Base_y, 254, 221, 88);
	gfx.PutPixel(19 +Base_x, 8 +Base_y, 0, 0, 0);
	gfx.PutPixel(0 +Base_x, 9 +Base_y, 0, 0, 0);
	gfx.PutPixel(1 +Base_x, 9 +Base_y, 254, 221, 88);
	gfx.PutPixel(2 +Base_x, 9 +Base_y, 0, 0, 0);
	gfx.PutPixel(3 +Base_x, 9 +Base_y, 0, 0, 0);
	gfx.PutPixel(4 +Base_x, 9 +Base_y, 0, 0, 0);
	gfx.PutPixel(5 +Base_x, 9 +Base_y, 0, 0, 0);
	gfx.PutPixel(6 +Base_x, 9 +Base_y, 254, 221, 88);
	gfx.PutPixel(7 +Base_x, 9 +Base_y, 254, 221, 88);
	gfx.PutPixel(8 +Base_x, 9 +Base_y, 254, 221, 88);
	gfx.PutPixel(9 +Base_x, 9 +Base_y, 254, 221, 88);
	gfx.PutPixel(10 +Base_x, 9 +Base_y, 254, 221, 88);
	gfx.PutPixel(11 +Base_x, 9 +Base_y, 0, 0, 0);
	gfx.PutPixel(12 +Base_x, 9 +Base_y, 0, 0, 0);
	gfx.PutPixel(13 +Base_x, 9 +Base_y, 0, 0, 0);
	gfx.PutPixel(14 +Base_x, 9 +Base_y, 0, 0, 0);
	gfx.PutPixel(15 +Base_x, 9 +Base_y, 254, 221, 88);
	gfx.PutPixel(16 +Base_x, 9 +Base_y, 254, 221, 88);
	gfx.PutPixel(17 +Base_x, 9 +Base_y, 254, 221, 88);
	gfx.PutPixel(18 +Base_x, 9 +Base_y, 254, 221, 88);
	gfx.PutPixel(19 +Base_x, 9 +Base_y, 0, 0, 0);
	gfx.PutPixel(0 +Base_x, 10 +Base_y, 0, 0, 0);
	gfx.PutPixel(1 +Base_x, 10 +Base_y, 254, 221, 88);
	gfx.PutPixel(2 +Base_x, 10 +Base_y, 254, 221, 88);
	gfx.PutPixel(3 +Base_x, 10 +Base_y, 254, 221, 88);
	gfx.PutPixel(4 +Base_x, 10 +Base_y, 254, 221, 88);
	gfx.PutPixel(5 +Base_x, 10 +Base_y, 254, 221, 88);
	gfx.PutPixel(6 +Base_x, 10 +Base_y, 254, 221, 88);
	gfx.PutPixel(7 +Base_x, 10 +Base_y, 254, 221, 88);
	gfx.PutPixel(8 +Base_x, 10 +Base_y, 254, 221, 88);
	gfx.PutPixel(9 +Base_x, 10 +Base_y, 254, 221, 88);
	gfx.PutPixel(10 +Base_x, 10 +Base_y, 254, 221, 88);
	gfx.PutPixel(11 +Base_x, 10 +Base_y, 254, 221, 88);
	gfx.PutPixel(12 +Base_x, 10 +Base_y, 254, 221, 88);
	gfx.PutPixel(13 +Base_x, 10 +Base_y, 254, 221, 88);
	gfx.PutPixel(14 +Base_x, 10 +Base_y, 254, 221, 88);
	gfx.PutPixel(15 +Base_x, 10 +Base_y, 254, 221, 88);
	gfx.PutPixel(16 +Base_x, 10 +Base_y, 254, 221, 88);
	gfx.PutPixel(17 +Base_x, 10 +Base_y, 254, 221, 88);
	gfx.PutPixel(18 +Base_x, 10 +Base_y, 254, 221, 88);
	gfx.PutPixel(19 +Base_x, 10 +Base_y, 0, 0, 0);
	gfx.PutPixel(0 +Base_x, 11 +Base_y, 0, 0, 0);
	gfx.PutPixel(1 +Base_x, 11 +Base_y, 254, 221, 88);
	gfx.PutPixel(2 +Base_x, 11 +Base_y, 254, 221, 88);
	gfx.PutPixel(3 +Base_x, 11 +Base_y, 254, 221, 88);
	gfx.PutPixel(4 +Base_x, 11 +Base_y, 254, 221, 88);
	gfx.PutPixel(5 +Base_x, 11 +Base_y, 254, 221, 88);
	gfx.PutPixel(6 +Base_x, 11 +Base_y, 254, 221, 88);
	gfx.PutPixel(7 +Base_x, 11 +Base_y, 20, 14, 18);
	gfx.PutPixel(8 +Base_x, 11 +Base_y, 18, 11, 14);
	gfx.PutPixel(9 +Base_x, 11 +Base_y, 18, 12, 14);
	gfx.PutPixel(10 +Base_x, 11 +Base_y, 18, 12, 14);
	gfx.PutPixel(11 +Base_x, 11 +Base_y, 21, 13, 16);
	gfx.PutPixel(12 +Base_x, 11 +Base_y, 24, 11, 15);
	gfx.PutPixel(13 +Base_x, 11 +Base_y, 0, 0, 0);
	gfx.PutPixel(14 +Base_x, 11 +Base_y, 254, 221, 88);
	gfx.PutPixel(15 +Base_x, 11 +Base_y, 254, 221, 88);
	gfx.PutPixel(16 +Base_x, 11 +Base_y, 254, 221, 88);
	gfx.PutPixel(17 +Base_x, 11 +Base_y, 254, 221, 88);
	gfx.PutPixel(18 +Base_x, 11 +Base_y, 254, 221, 88);
	gfx.PutPixel(19 +Base_x, 11 +Base_y, 0, 0, 0);
	gfx.PutPixel(0 +Base_x, 12 +Base_y, 0, 0, 0);
	gfx.PutPixel(1 +Base_x, 12 +Base_y, 254, 221, 88);
	gfx.PutPixel(2 +Base_x, 12 +Base_y, 254, 221, 88);
	gfx.PutPixel(3 +Base_x, 12 +Base_y, 254, 221, 88);
	gfx.PutPixel(4 +Base_x, 12 +Base_y, 254, 221, 88);
	gfx.PutPixel(5 +Base_x, 12 +Base_y, 254, 221, 88);
	gfx.PutPixel(6 +Base_x, 12 +Base_y, 23, 9, 23);
	gfx.PutPixel(7 +Base_x, 12 +Base_y, 135, 26, 68);
	gfx.PutPixel(8 +Base_x, 12 +Base_y, 135, 26, 68);
	gfx.PutPixel(9 +Base_x, 12 +Base_y, 135, 26, 68);
	gfx.PutPixel(10 +Base_x, 12 +Base_y, 135, 26, 68);
	gfx.PutPixel(11 +Base_x, 12 +Base_y, 135, 26, 68);
	gfx.PutPixel(12 +Base_x, 12 +Base_y, 135, 26, 68);
	gfx.PutPixel(13 +Base_x, 12 +Base_y, 135, 26, 68);
	gfx.PutPixel(14 +Base_x, 12 +Base_y, 0, 0, 0);
	gfx.PutPixel(15 +Base_x, 12 +Base_y, 254, 221, 88);
	gfx.PutPixel(16 +Base_x, 12 +Base_y, 254, 221, 88);
	gfx.PutPixel(17 +Base_x, 12 +Base_y, 254, 221, 88);
	gfx.PutPixel(18 +Base_x, 12 +Base_y, 254, 221, 88);
	gfx.PutPixel(19 +Base_x, 12 +Base_y, 0, 0, 0);
	gfx.PutPixel(1 +Base_x, 13 +Base_y, 0, 0, 0);
	gfx.PutPixel(2 +Base_x, 13 +Base_y, 254, 221, 88);
	gfx.PutPixel(3 +Base_x, 13 +Base_y, 254, 221, 88);
	gfx.PutPixel(4 +Base_x, 13 +Base_y, 254, 221, 88);
	gfx.PutPixel(5 +Base_x, 13 +Base_y, 0, 0, 0);
	gfx.PutPixel(6 +Base_x, 13 +Base_y, 135, 26, 68);
	gfx.PutPixel(7 +Base_x, 13 +Base_y, 135, 26, 68);
	gfx.PutPixel(8 +Base_x, 13 +Base_y, 135, 26, 68);
	gfx.PutPixel(9 +Base_x, 13 +Base_y, 135, 26, 68);
	gfx.PutPixel(10 +Base_x, 13 +Base_y, 135, 26, 68);
	gfx.PutPixel(11 +Base_x, 13 +Base_y, 135, 26, 68);
	gfx.PutPixel(12 +Base_x, 13 +Base_y, 135, 26, 68);
	gfx.PutPixel(13 +Base_x, 13 +Base_y, 135, 26, 68);
	gfx.PutPixel(14 +Base_x, 13 +Base_y, 135, 26, 68);
	gfx.PutPixel(15 +Base_x, 13 +Base_y, 0, 0, 0);
	gfx.PutPixel(16 +Base_x, 13 +Base_y, 254, 221, 88);
	gfx.PutPixel(17 +Base_x, 13 +Base_y, 254, 221, 88);
	gfx.PutPixel(18 +Base_x, 13 +Base_y, 0, 0, 0);
	gfx.PutPixel(1 +Base_x, 14 +Base_y, 0, 0, 0);
	gfx.PutPixel(2 +Base_x, 14 +Base_y, 254, 221, 88);
	gfx.PutPixel(3 +Base_x, 14 +Base_y, 254, 221, 88);
	gfx.PutPixel(4 +Base_x, 14 +Base_y, 0, 0, 0);
	gfx.PutPixel(5 +Base_x, 14 +Base_y, 135, 26, 68);
	gfx.PutPixel(6 +Base_x, 14 +Base_y, 135, 26, 68);
	gfx.PutPixel(7 +Base_x, 14 +Base_y, 135, 26, 68);
	gfx.PutPixel(8 +Base_x, 14 +Base_y, 135, 26, 68);
	gfx.PutPixel(9 +Base_x, 14 +Base_y, 251, 192, 224);
	gfx.PutPixel(10 +Base_x, 14 +Base_y, 251, 192, 224);
	gfx.PutPixel(11 +Base_x, 14 +Base_y, 251, 192, 224);
	gfx.PutPixel(12 +Base_x, 14 +Base_y, 251, 192, 224);
	gfx.PutPixel(13 +Base_x, 14 +Base_y, 135, 26, 68);
	gfx.PutPixel(14 +Base_x, 14 +Base_y, 135, 26, 68);
	gfx.PutPixel(15 +Base_x, 14 +Base_y, 0, 0, 0);
	gfx.PutPixel(16 +Base_x, 14 +Base_y, 254, 221, 88);
	gfx.PutPixel(17 +Base_x, 14 +Base_y, 254, 221, 88);
	gfx.PutPixel(18 +Base_x, 14 +Base_y, 0, 0, 0);
	gfx.PutPixel(2 +Base_x, 15 +Base_y, 0, 0, 0);
	gfx.PutPixel(3 +Base_x, 15 +Base_y, 254, 221, 88);
	gfx.PutPixel(4 +Base_x, 15 +Base_y, 0, 0, 0);
	gfx.PutPixel(5 +Base_x, 15 +Base_y, 135, 26, 68);
	gfx.PutPixel(6 +Base_x, 15 +Base_y, 135, 26, 68);
	gfx.PutPixel(7 +Base_x, 15 +Base_y, 135, 26, 68);
	gfx.PutPixel(8 +Base_x, 15 +Base_y, 251, 192, 224);
	gfx.PutPixel(9 +Base_x, 15 +Base_y, 251, 192, 224);
	gfx.PutPixel(10 +Base_x, 15 +Base_y, 251, 192, 224);
	gfx.PutPixel(11 +Base_x, 15 +Base_y, 251, 192, 224);
	gfx.PutPixel(12 +Base_x, 15 +Base_y, 251, 192, 224);
	gfx.PutPixel(13 +Base_x, 15 +Base_y, 251, 192, 224);
	gfx.PutPixel(14 +Base_x, 15 +Base_y, 135, 26, 68);
	gfx.PutPixel(15 +Base_x, 15 +Base_y, 0, 0, 0);
	gfx.PutPixel(16 +Base_x, 15 +Base_y, 254, 221, 88);
	gfx.PutPixel(17 +Base_x, 15 +Base_y, 0, 0, 0);
	gfx.PutPixel(2 +Base_x, 16 +Base_y, 0, 0, 0);
	gfx.PutPixel(3 +Base_x, 16 +Base_y, 254, 221, 88);
	gfx.PutPixel(4 +Base_x, 16 +Base_y, 0, 0, 0);
	gfx.PutPixel(5 +Base_x, 16 +Base_y, 135, 26, 68);
	gfx.PutPixel(6 +Base_x, 16 +Base_y, 135, 26, 68);
	gfx.PutPixel(7 +Base_x, 16 +Base_y, 135, 26, 68);
	gfx.PutPixel(8 +Base_x, 16 +Base_y, 251, 192, 224);
	gfx.PutPixel(9 +Base_x, 16 +Base_y, 251, 192, 224);
	gfx.PutPixel(10 +Base_x, 16 +Base_y, 251, 192, 224);
	gfx.PutPixel(11 +Base_x, 16 +Base_y, 251, 192, 224);
	gfx.PutPixel(12 +Base_x, 16 +Base_y, 251, 192, 224);
	gfx.PutPixel(13 +Base_x, 16 +Base_y, 251, 192, 224);
	gfx.PutPixel(14 +Base_x, 16 +Base_y, 135, 26, 68);
	gfx.PutPixel(15 +Base_x, 16 +Base_y, 0, 0, 0);
	gfx.PutPixel(16 +Base_x, 16 +Base_y, 254, 221, 88);
	gfx.PutPixel(17 +Base_x, 16 +Base_y, 0, 0, 0);
	gfx.PutPixel(3 +Base_x, 17 +Base_y, 0, 0, 0);
	gfx.PutPixel(4 +Base_x, 17 +Base_y, 0, 0, 0);
	gfx.PutPixel(5 +Base_x, 17 +Base_y, 0, 0, 0);
	gfx.PutPixel(6 +Base_x, 17 +Base_y, 0, 0, 0);
	gfx.PutPixel(7 +Base_x, 17 +Base_y, 0, 0, 0);
	gfx.PutPixel(8 +Base_x, 17 +Base_y, 0, 0, 0);
	gfx.PutPixel(9 +Base_x, 17 +Base_y, 0, 0, 0);
	gfx.PutPixel(10 +Base_x, 17 +Base_y, 0, 0, 0);
	gfx.PutPixel(11 +Base_x, 17 +Base_y, 0, 0, 0);
	gfx.PutPixel(12 +Base_x, 17 +Base_y, 0, 0, 0);
	gfx.PutPixel(13 +Base_x, 17 +Base_y, 0, 0, 0);
	gfx.PutPixel(14 +Base_x, 17 +Base_y, 0, 0, 0);
	gfx.PutPixel(15 +Base_x, 17 +Base_y, 0, 0, 0);
	gfx.PutPixel(16 +Base_x, 17 +Base_y, 0, 0, 0);
	gfx.PutPixel(5 +Base_x, 18 +Base_y, 0, 0, 0);
	gfx.PutPixel(6 +Base_x, 18 +Base_y, 0, 0, 0);
	gfx.PutPixel(7 +Base_x, 18 +Base_y, 254, 221, 88);
	gfx.PutPixel(8 +Base_x, 18 +Base_y, 254, 221, 88);
	gfx.PutPixel(9 +Base_x, 18 +Base_y, 254, 221, 88);
	gfx.PutPixel(10 +Base_x, 18 +Base_y, 254, 221, 88);
	gfx.PutPixel(11 +Base_x, 18 +Base_y, 254, 221, 88);
	gfx.PutPixel(12 +Base_x, 18 +Base_y, 254, 221, 88);
	gfx.PutPixel(13 +Base_x, 18 +Base_y, 0, 0, 0);
	gfx.PutPixel(14 +Base_x, 18 +Base_y, 0, 0, 0);
	gfx.PutPixel(7 +Base_x, 19 +Base_y, 0, 0, 0);
	gfx.PutPixel(8 +Base_x, 19 +Base_y, 0, 0, 0);
	gfx.PutPixel(9 +Base_x, 19 +Base_y, 0, 0, 0);
	gfx.PutPixel(10 +Base_x, 19 +Base_y, 0, 0, 0);
	gfx.PutPixel(11 +Base_x, 19 +Base_y, 0, 0, 0);
	gfx.PutPixel(12 +Base_x, 19 +Base_y, 0, 0, 0);
}

void Dude::DrawBody(Graphics & gfx)
{
	////////////
	gfx.DrawLine(Neck, ElboLeft, Colors::Gray); //leftarm
	gfx.DrawrecAligned(Neck, ElboLeft, 1, Colors::Gray);// draws rec aligned with arm
	////////////
	gfx.DrawLine(Neck, ElboRight, Colors::Gray); //rightarm
	gfx.DrawrecAligned(Neck, ElboRight, 1, Colors::Gray);// draws rec aligned with arm
	////////////
	gfx.DrawLine(ElboLeft, HandLeft, Colors::Gray); //leftgun
	gfx.DrawrecAligned(ElboLeft, HandLeft, 2, Colors::Blue);// draws rec aligned with arm
	////////////
	gfx.DrawLine(ElboRight, HandRight, Colors::Gray); //Rightgun
	gfx.DrawrecAligned(ElboRight, HandRight, 2, Colors::Blue);// draws rec aligned with arm
	////////////
	gfx.DrawLine(Neck, Waist, Colors::Gray);
	gfx.DrawrecAligned(Neck, Waist, 1, Colors::Gray);// draws rec aligned with arm
	////////////
	gfx.DrawLine(Waist, KneeLeft, Colors::Gray);
	gfx.DrawrecAligned(Waist, KneeLeft, 1, Colors::Gray);// draws rec aligned with arm
	////////////
	gfx.DrawLine(Waist, KneeRight, Colors::Gray);
	gfx.DrawrecAligned(Waist, KneeRight, 1, Colors::Gray);// draws rec aligned with arm
	////////////
	gfx.DrawLine(KneeLeft, FootLeft, Colors::Gray);
	gfx.DrawrecAligned(KneeLeft, FootLeft, 1, Colors::Gray);// draws rec aligned with arm
	////////////
	gfx.DrawLine(KneeRight, FootRight, Colors::Gray);
	gfx.DrawrecAligned(KneeRight, FootRight, 1, Colors::Gray);// draws rec aligned with arm
	////////////

	
}

void Dude::DrawGuns(Graphics & gfx)
{
}

void Dude::Running()
{
}

void Dude::Arms()
{
	///////////////////////	
	ElboLeft = FakeSholderLeft + TrigFunc((Target.x - FakeSholderLeft.x),(Target.y - FakeSholderLeft.y), RecoilLeft);	
	ElboRight = FakeSholderRight + TrigFunc((Target.x - FakeSholderRight.x), (Target.y - FakeSholderRight.y), RecoilRight);
	//////////////	
	HandLeft = ElboLeft + TrigFunc((Target.x - ElboLeft.x), (Target.y - ElboLeft.y), forearm);
	HandRight = ElboRight + TrigFunc((Target.x - ElboRight.x), (Target.y - ElboRight.y), forearm);
	//////////////
}

void Dude::Jumping()
{
	KneeLeft = Waist + TrigFunc( (Target.x - Waist.x) , ( Target.y - Waist.y) , 15 );
	KneeRight = Waist + TrigFunc((Target.x + 40 - Waist.x), (Target.y + 40 - Waist.y), 15);
	FootLeft = { KneeLeft.x - 2 , KneeLeft.y + 10 };
	FootRight = { KneeRight.x + 2 , KneeRight.y + 10 };
}

void Dude::Shooting()
{	
	RecoilLeft += Modifier;
	RecoilRight += Modifier;
	if (RecoilLeft < 2)
	{
		Modifier = 1 ;
	}
	else if (RecoilLeft > 10)
	{
		Modifier = -5; 
	}
}

void Dude::Using()
{
}

Vec2 Dude::TrigFunc(float in_x , float in_y , int Hypotenuse)
{
	float Calc_vx;
	float Calc_vy;
	double Radian;
	Radian = (double)atan2(in_x , in_y );    // gets radians for trig function
	Calc_vx = float(sin(Radian) * Hypotenuse); // trig functions
	Calc_vy = float(cos(Radian) * Hypotenuse);
	Vec2 Result{ Calc_vx, Calc_vy };
	return Result;
}
