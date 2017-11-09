/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "poo.h"
#include "Level.h"
#include "MapBuilder.h"
#include "Collision.h"
#include "Dude.h"


class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	void DrawPoo( int x,int y );
	void DrawGameOver( int x,int y );
	void DrawTitleScreen( int x,int y );
	int ClampScreenX( int x,int width );
	int ClampScreenY( int y,int height );
	bool IsColliding( int x0,int y0,int width0,int height0,
		int x1,int y1,int width1,int height1 );

	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	Mapbuilder MapEdit;
	int dudeX = 400;
	int dudeY = 300;
	int dudeWidth = 20;
	int dudeHeight = 20;
	poo poo0;
	poo poo1;
	poo poo2;
	bool isStarted = false;
	Dude Smiles;

	Level Level1;
	Level Level2;
	Level Level3;
	Level Level4;
	Level Level5;

    Vec2 A;
	Vec2 B;
	Vec2 C;
	////////////// map builder //////////////
	Collision Collide;

	/////////////////////////////////////////
	/********************************/
};