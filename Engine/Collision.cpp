#include "Collision.h"

bool Collision::CollideTest(Vec2 & UL, Vec2 & BR ,Vec2& test)
{
	return (test.x > UL.x &&
			test.x < BR.x &&
			test.y > UL.y &&
			test.y < BR.y);	
}

bool Collision::CollideTest(Vec2 & UL, Vec2 & BR, Vec2 & UL2, Vec2 & BR2)
{
	return ((UL.x <= BR2.x && BR.x >= BR2.x) || (BR.x >= UL2.x && UL.x <= UL2.x) &&  ////// <<<<<<< test and rename to understand 
		    (UL.y <= BR2.y && BR.y >= BR2.y) || (BR.y >= UL2.y && UL.y <= UL2.y));
}
