#pragma once
#include "Vec2.h"


class Collision
{
public:
	bool CollideTest( Vec2& UL , Vec2& BR , Vec2& test);  // single point collision
	bool CollideTest(Vec2& UL, Vec2& BR, Vec2& UL2, Vec2& BR2); // box collision
};
