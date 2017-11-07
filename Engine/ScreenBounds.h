#pragma once
#include "Vec2.h"



class ScreenBounds
{
public:
	bool BoundsCheck( Vec2 Test );
	bool BoundsCheck(int in_x, int in_y);
};
