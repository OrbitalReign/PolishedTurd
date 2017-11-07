#include "ScreenBounds.h"
#include "Graphics.h"

bool ScreenBounds::BoundsCheck(Vec2 Test)
{
	return (Test.x > 0 &&
			Test.x < Graphics::ScreenWidth &&
			Test.y > 0 &&
			Test.y < Graphics::ScreenHeight);
}

bool ScreenBounds::BoundsCheck(int in_x, int in_y)
{
	return (in_x > 0 &&
			in_x < Graphics::ScreenWidth &&
			in_y > 0 &&
			in_y < Graphics::ScreenHeight);
}
