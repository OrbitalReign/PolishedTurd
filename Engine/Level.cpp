#include "Level.h"
#include "Graphics.h"




void Level::BlockLayer( )  
{
	Vec2 test{ 100,100 };
	Vec2 increase{ 40,40 };
	float bevel = 5;
	Color c{ 100 , 100 , 100 };
	
    // load in block vec array
	for (int i = 0; i <= 11; ++i)
	{
		BlockArray.push_back(test);
		BlockBevel.push_back(bevel);
		BlockColour.push_back(c);
		test += increase;
	}
}

void Level::EnemyLayer()
{
}

void Level::PowerupLayer()
{
}

void Level::CollisionMask()
{
}

Vec2 Level::Get_block_vec2(const int Index)
{

	////// to do ///////
	Vec2 Get = BlockArray.at(Index);
	return Get;
}
/*
Vec2 & Level::Get_Enemy_vec2(const int Index)
{
	Vec2 test{ 100,100 };
	// TODO: insert return statement here
	return test;
}

Vec2 & Level::Get_Powerup_vec2(const int Index)
{
	Vec2 test{ 100,100 };
	// TODO: insert return statement here
	return test;
}
*/
float Level::Get_Bevel(const int Index)
{
	return BlockBevel.at(Index);
}
/*
float Level::Get_EnemyHealth(const int Index)
{
	return 0.0f;
}
*/
Color & Level::Get_Block_Col(const int Index)
{
	return BlockColour.at(Index);
}
