#include "Dude.h"
#include "MainWindow.h"
#include "Graphics.h"
#include <cmath>



void Dude::Update( MainWindow& wnd)
{
	///////////////////////
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
	///////////////////////
	Head = { (float)Base_x,(float)Base_y };
	Neck = { (float)Base_x + 10, (float)Base_y + 20 };
	FakeSholderLeft = { Head.x , Neck.y };
	FakeSholderRight = { Head.x + 20, Neck.y };
	Waist = { Neck.x , Neck.y + 20 };
	///////////////////////
	if (ScreenCheck.BoundsCheck(wnd.mouse.GetPosX(), wnd.mouse.GetPosY()))
	{
		Target = { (float)wnd.mouse.GetPosX() , (float)wnd.mouse.GetPosY() };		
		Fire = wnd.mouse.LeftIsPressed();
	}
	///////////////////////	
	Arms();
	Shooting();
	Jumping();
	HitBoxSet();
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
	//gfx.DrawLine(Neck, ElboLeft, Colors::Gray); //leftarm
	gfx.DrawrecAligned(Neck, ElboLeft, 1, Colors::Gray);// draws rec aligned with arm
	////////////
	//gfx.DrawLine(Neck, ElboRight, Colors::Gray); //rightarm
	gfx.DrawrecAligned(Neck, ElboRight, 1, Colors::Gray);// draws rec aligned with arm
	////////////
	//gfx.DrawLine(ElboLeft, HandLeft, Colors::Gray); //leftgun	
	////////////
	//gfx.DrawLine(ElboRight, HandRight, Colors::Gray); //Rightgun	
	////////////
	//gfx.DrawLine(Neck, Waist, Colors::Gray); // torso
	gfx.DrawrecAligned(Neck, Waist, 1, Colors::Gray);// draws rec aligned with torso
	////////////
	//gfx.DrawLine(Waist, KneeLeft, Colors::Gray); // left thigh
	gfx.DrawrecAligned(Waist, KneeLeft, 1, Colors::Gray);// draws rec aligned with thigh
	////////////
	//gfx.DrawLine(Waist, KneeRight, Colors::Gray); // right thigh
	gfx.DrawrecAligned(Waist, KneeRight, 1, Colors::Gray);// draws rec aligned with thigh
	////////////
	//gfx.DrawLine(KneeLeft, FootLeft, Colors::Gray); // left shin
	gfx.DrawrecAligned(KneeLeft, FootLeft, 1, Colors::Gray);// draws rec aligned with shin
	////////////
	//gfx.DrawLine(KneeRight, FootRight, Colors::Gray); // right shin
	gfx.DrawrecAligned(KneeRight, FootRight, 1, Colors::Gray);// draws rec aligned with shin
	////////////	
}

void Dude::DrawGuns(Graphics & gfx)
{
	gfx.DrawrecAligned(ElboLeft, HandLeft, 3, Colors::Purple);// draws rec aligned with arm
	gfx.DrawrecAligned(ElboRight, HandRight, 3, Colors::Blue);// draws rec aligned with arm
}

void Dude::DrawBullets(Graphics & gfx)
{	
	Color Col{ 255, 200 , 0 };
	for (int i = 0; i < Clipsize; i++)
	{	
		LeftClip[i].Location +=  LeftClip[i].Direction;
		RightClip[i].Location +=  RightClip[i].Direction;

		if (ScreenCheck.BoundsCheck(LeftClip[i].Location)) // checks is in screen
		{
			gfx.PutPixel((int)LeftClip[i].Location.x, (int)LeftClip[i].Location.y, Col);   // DrawBullet
		}
		if (ScreenCheck.BoundsCheck(RightClip[i].Location)) // Checks is in screen
		{
			gfx.PutPixel((int)RightClip[i].Location.x, (int)RightClip[i].Location.y, Col); 	// DrawBullet
		}
	}
}

void Dude::Running()
{
}

void Dude::Arms()
{
	//////////////
	ElboLeft = FakeSholderLeft + TrigFunc((Target.x - FakeSholderLeft.x),(Target.y - FakeSholderLeft.y), RecoilLeft);	
	ElboRight = FakeSholderRight + TrigFunc((Target.x - FakeSholderRight.x), (Target.y - FakeSholderRight.y), RecoilRight);
	//////////////	
	HandLeft = ElboLeft + TrigFunc((Target.x - ElboLeft.x), (Target.y - ElboLeft.y), forearm);
	HandRight = ElboRight + TrigFunc((Target.x - ElboRight.x), (Target.y - ElboRight.y), forearm);
	//////////////
}

void Dude::Jumping()
{
	//////////////
	KneeLeft = Waist + TrigFunc( (Target.x - Waist.x) , ( Target.y - Waist.y) , 15 );
	KneeRight = Waist + TrigFunc((Target.x + 40 - Waist.x), (Target.y + 40 - Waist.y), 15);
	//////////////
	FootLeft = { KneeLeft.x - 2 , KneeLeft.y + 10 };
	FootRight = { KneeRight.x + 2 , KneeRight.y + 10 };
	/////////////
}

void Dude::Shooting()
{	
	
	if (Fire)
	{
		//////////////// gets bullets vector from hand
		Vec2 LeftDirection = HandLeft - ElboLeft;
		Vec2 RightDirection = HandRight - ElboRight;		
		///////////////
		RecoilLeft += Modifier_L;		//// first shot
		///////////////
		if (RecoilLeft < 1)
		{
			Modifier_L = 2;
			SecondShot = true;
		}
		else if (RecoilLeft > 10)
		{		
			LeftClip[LeftClipPos].Direction = LeftDirection.Normalized() * LeftClip[LeftClipPos].Speed; // sets bullets vector
			LeftClip[LeftClipPos].Location = HandLeft; // base location
			Modifier_L = -4; // recoil
			LeftClipPos++;
		}
		//////////////
		if (SecondShot) RecoilRight += Modifier_R;  ///// second shot
		//////////////
		if (RecoilRight < 1 )
		{
			Modifier_R = 2;
		}
		else if (RecoilRight > 10 )
		{ 		
			RightClip[RightClipPos].Direction = RightDirection.Normalized() * RightClip[RightClipPos].Speed; // sets bullet vector
			RightClip[RightClipPos].Location = HandRight; // base location
			Modifier_R = -4;  // recoil
			RightClipPos++;
		}
		////////////// 
	}
	else
	{
		////////////// resets
		RecoilLeft = 10;
		RecoilRight = 10;
		// guns move forward slightly first before firing first shot 
		Modifier_R = 1;
		Modifier_L = 1;
		SecondShot = false;
	}
	/////////////////// Reload
	
	///// Add Timmer Function ////// <<<<<<<<<<<<<<<<<<<<

	if (LeftClipPos >= Clipsize)
	{
		LeftClipPos = 0;
	}
	if (RightClipPos >= Clipsize)
	{
		RightClipPos = 0;
	}
	///////////////////
}

void Dude::Using()
{
}

void Dude::ClipUpdate()
{

}

void Dude::HitBoxSet()
{
	// min max X
	////////////////////// stacked Min 
	HitBox.Min_x = std::min(std::min(std::min(Head.x,ElboLeft.x ),
									 std::min(HandLeft.x ,HandRight.x)),
									 std::min(std::min(KneeLeft.x, KneeRight.x),
								     std::min(FootLeft.x, FootRight.x)));
	///////////////////// stacked Max
	HitBox.Max_x = std::max(std::max(std::max(Head.x +20 , ElboRight.x),
								     std::max(HandLeft.x,HandRight.x )),
									 std::max(std::min(KneeLeft.x, KneeRight.x),
									 std::max(FootLeft.x, FootRight.x)));
	// min max Y
	///////////////////// stacked Min
	HitBox.Min_y = std::min(std::min(std::min(Head.y, ElboLeft.y),
								   	 std::min(HandLeft.y, HandRight.y)),
									 std::min(std::min(KneeLeft.y, KneeRight.y),
									 std::min(FootLeft.y, FootRight.y)));
	///////////////////// stacked Max
	HitBox.Max_y = std::max( Waist.y, std::max( std::max(KneeLeft.y, KneeRight.y),
												std::max(FootLeft.y, FootRight.y)));
									 
}

Vec2 Dude::TrigFunc(float in_x , float in_y , int Hypotenuse)
{
	float Calc_vx;
	float Calc_vy;
	double Radian;
	Radian = (double)atan2(in_x , in_y );    // gets radians for trig function
	Calc_vx = float(sin(Radian) * Hypotenuse); // trig functions
	Calc_vy = float(cos(Radian) * Hypotenuse);
    return Vec2{ Calc_vx, Calc_vy };

}

