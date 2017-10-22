#include "poo.h"
#include "Graphics.h"

void poo::update()
{
	x += vx;
	y += vy;

	const int right = x + Width;
	if ( x < 0)
	{
          x = 0;
		  vx = -vx;
	}
	else if (right >= Graphics::ScreenWidth)
	{
		x = (Graphics::ScreenWidth - 1) - Width;
		vx = -vx;
	}

	const int bottom = y + Height;
	if (y < 0)
	{
		y = 0;
		vy = -vy;
	}
	else if (bottom >= Graphics::ScreenHeight)
	{
		y = (Graphics::ScreenHeight - 1) - Height;
		vy = -vy;
	}
	
}





