#pragma once
#include "Vec2.h"
#include <vector>
#include "ScreenBounds.h"


class Dude
{
public:
	///////////////////
	void Update(class MainWindow& wnd);
	void DrawFace(class Graphics& gfx);
	void DrawBody(class Graphics& gfx);
	void DrawGuns(class Graphics& gfx);
	void DrawBullets(class Graphics& gfx);
	///////////////////
private:
	/////////////////// animation
	void Running();
	void Arms();
	void Jumping();
	void Shooting();
	void Using();
	void ClipUpdate();
	//////////////////
	Vec2 TrigFunc(float in_x, float in_y, int Hypotenuse);
private:
	class Bullet
	{
	public:
		Vec2 Location{ 0 ,0 };
		Vec2 Direction{ 0,0 };
		float Speed = 2.f;
	};
private:
	////////////////// bools
	bool Fire = false;
	bool SecondShot = false;
	bool LoadBullet_L = true;
	bool LoadBullet_R = true;
	////////////////// body Vecs
	int Base_x = 400;
	int Base_y = 300;
	Vec2 Head;
	Vec2 Neck;
	Vec2 Waist;
	Vec2 FakeSholderLeft;
	Vec2 FakeSholderRight;
	Vec2 ElboLeft;
	Vec2 ElboRight;
	Vec2 HandLeft;
	Vec2 HandRight;
	Vec2 KneeLeft;
	Vec2 KneeRight;
	Vec2 FootLeft;
	Vec2 FootRight;
	////////////////// body dims
	int forearm = 15;
	int RecoilLeft = 10;
	int RecoilRight = 10;
	/////////////////
	Vec2 Target;
	ScreenBounds ScreenCheck;
	int Modifier_L = 1;
	int Modifier_R = 1;
	///////////////////
	Vec2 BulletVec;
	int Clipsize = 50;
	int LeftClipPos = 0 ;
	int RightClipPos = 0;
	Bullet Shot;
	std::vector<Bullet> LeftClip{ Clipsize , Shot };
	std::vector<Bullet> RightClip{ Clipsize , Shot };
};
