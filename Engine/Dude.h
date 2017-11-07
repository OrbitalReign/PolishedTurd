#pragma once
#include"Vec2.h"

#include "ScreenBounds.h"


class Dude
{
public:
	///////////////////
	void Update(class MainWindow& wnd);
	void DrawFace(class Graphics& gfx);
	void DrawBody(class Graphics& gfx);
	void DrawGuns(class Graphics& gfx);
	///////////////////
private:
	/////////////////// animation
	void Running();
	void Arms();
	void Jumping();
	void Shooting();
	void Using();
	Vec2 TrigFunc(float in_x , float in_y , int Hypotenuse);
	//////////////////
private:
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
	int Rotate = 0;
	int RecoilLeft = 10;
	int RecoilRight = 0;
	double Degrees;
	Vec2 Target;
	ScreenBounds ScreenCheck;
	int Modifier = -1;
	Vec2 A;
	Vec2 B;
	Vec2 C;
	Vec2 D;

};
