#pragma once
#include "Vec2.h"
#include "Colors.h"
#include <vector>


class Level
{
public:
	///// file input /////
	void BlockLayer(); 
	void EnemyLayer();
	void PowerupLayer();
	void CollisionMask();
	//////////////////////
	Vec2 Get_block_vec2( const int Index );
//	Vec2& Get_Enemy_vec2(const int Index);
//	Vec2& Get_Powerup_vec2(const int Index);
	///////////////////////////////
	float Get_Bevel(const int Index);
//	float Get_EnemyHealth(const int Index);
	///////////////////////////////
	Color& Get_Block_Col(const int Index);

private:
    std::vector<Vec2> BlockArray;
	std::vector<Vec2> EnemyArray;
	std::vector<Vec2> PowerupArray;
	std::vector<Vec2> CollisionArray;
	///////////////////////////////
	std::vector<float> BlockBevel;
	std::vector<float> Enemyhealth;
	///////////////////////////////
	std::vector<Color> BlockColour;
};
