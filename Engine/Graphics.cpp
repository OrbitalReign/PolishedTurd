/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Graphics.cpp																		  *
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
#include "MainWindow.h"
#include "Graphics.h"
#include "DXErr.h"
#include "ChiliException.h"
#include <cmath>
#include <assert.h>
#include <string>
#include <array>

// Ignore the intellisense error "cannot open source file" for .shh files.
// They will be created during the build sequence before the preprocessor runs.
namespace FramebufferShaders
{
#include "FramebufferPS.shh"
#include "FramebufferVS.shh"
}

#pragma comment( lib,"d3d11.lib" )

#define CHILI_GFX_EXCEPTION( hr,note ) Graphics::Exception( hr,note,_CRT_WIDE(__FILE__),__LINE__ )

using Microsoft::WRL::ComPtr;

Graphics::Graphics( HWNDKey& key )
{
	assert( key.hWnd != nullptr );

	//////////////////////////////////////////////////////
	// create device and swap chain/get render target view
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferCount = 1;
	sd.BufferDesc.Width = Graphics::ScreenWidth;
	sd.BufferDesc.Height = Graphics::ScreenHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 1;
	sd.BufferDesc.RefreshRate.Denominator = 60;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = key.hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	HRESULT				hr;
	UINT				createFlags = 0u;
#ifdef CHILI_USE_D3D_DEBUG_LAYER
#ifdef _DEBUG
	createFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
#endif
	
	// create device and front/back buffers
	if( FAILED( hr = D3D11CreateDeviceAndSwapChain( 
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwapChain,
		&pDevice,
		nullptr,
		&pImmediateContext ) ) )
	{
		throw CHILI_GFX_EXCEPTION( hr,L"Creating device and swap chain" );
	}

	// get handle to backbuffer
	ComPtr<ID3D11Resource> pBackBuffer;
	if( FAILED( hr = pSwapChain->GetBuffer(
		0,
		__uuidof( ID3D11Texture2D ),
		(LPVOID*)&pBackBuffer ) ) )
	{
		throw CHILI_GFX_EXCEPTION( hr,L"Getting back buffer" );
	}

	// create a view on backbuffer that we can render to
	if( FAILED( hr = pDevice->CreateRenderTargetView( 
		pBackBuffer.Get(),
		nullptr,
		&pRenderTargetView ) ) )
	{
		throw CHILI_GFX_EXCEPTION( hr,L"Creating render target view on backbuffer" );
	}


	// set backbuffer as the render target using created view
	pImmediateContext->OMSetRenderTargets( 1,pRenderTargetView.GetAddressOf(),nullptr );


	// set viewport dimensions
	D3D11_VIEWPORT vp;
	vp.Width = float( Graphics::ScreenWidth );
	vp.Height = float( Graphics::ScreenHeight );
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	pImmediateContext->RSSetViewports( 1,&vp );


	///////////////////////////////////////
	// create texture for cpu render target
	D3D11_TEXTURE2D_DESC sysTexDesc;
	sysTexDesc.Width = Graphics::ScreenWidth;
	sysTexDesc.Height = Graphics::ScreenHeight;
	sysTexDesc.MipLevels = 1;
	sysTexDesc.ArraySize = 1;
	sysTexDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sysTexDesc.SampleDesc.Count = 1;
	sysTexDesc.SampleDesc.Quality = 0;
	sysTexDesc.Usage = D3D11_USAGE_DYNAMIC;
	sysTexDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	sysTexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	sysTexDesc.MiscFlags = 0;
	// create the texture
	if( FAILED( hr = pDevice->CreateTexture2D( &sysTexDesc,nullptr,&pSysBufferTexture ) ) )
	{
		throw CHILI_GFX_EXCEPTION( hr,L"Creating sysbuffer texture" );
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = sysTexDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	// create the resource view on the texture
	if( FAILED( hr = pDevice->CreateShaderResourceView( pSysBufferTexture.Get(),
		&srvDesc,&pSysBufferTextureView ) ) )
	{
		throw CHILI_GFX_EXCEPTION( hr,L"Creating view on sysBuffer texture" );
	}


	////////////////////////////////////////////////
	// create pixel shader for framebuffer
	// Ignore the intellisense error "namespace has no member"
	if( FAILED( hr = pDevice->CreatePixelShader(
		FramebufferShaders::FramebufferPSBytecode,
		sizeof( FramebufferShaders::FramebufferPSBytecode ),
		nullptr,
		&pPixelShader ) ) )
	{
		throw CHILI_GFX_EXCEPTION( hr,L"Creating pixel shader" );
	}
	

	/////////////////////////////////////////////////
	// create vertex shader for framebuffer
	// Ignore the intellisense error "namespace has no member"
	if( FAILED( hr = pDevice->CreateVertexShader(
		FramebufferShaders::FramebufferVSBytecode,
		sizeof( FramebufferShaders::FramebufferVSBytecode ),
		nullptr,
		&pVertexShader ) ) )
	{
		throw CHILI_GFX_EXCEPTION( hr,L"Creating vertex shader" );
	}
	

	//////////////////////////////////////////////////////////////
	// create and fill vertex buffer with quad for rendering frame
	const FSQVertex vertices[] =
	{
		{ -1.0f,1.0f,0.5f,0.0f,0.0f },
		{ 1.0f,1.0f,0.5f,1.0f,0.0f },
		{ 1.0f,-1.0f,0.5f,1.0f,1.0f },
		{ -1.0f,1.0f,0.5f,0.0f,0.0f },
		{ 1.0f,-1.0f,0.5f,1.0f,1.0f },
		{ -1.0f,-1.0f,0.5f,0.0f,1.0f },
	};
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof( FSQVertex ) * 6;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0u;
	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = vertices;
	if( FAILED( hr = pDevice->CreateBuffer( &bd,&initData,&pVertexBuffer ) ) )
	{
		throw CHILI_GFX_EXCEPTION( hr,L"Creating vertex buffer" );
	}

	
	//////////////////////////////////////////
	// create input layout for fullscreen quad
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 }
	};

	// Ignore the intellisense error "namespace has no member"
	if( FAILED( hr = pDevice->CreateInputLayout( ied,2,
		FramebufferShaders::FramebufferVSBytecode,
		sizeof( FramebufferShaders::FramebufferVSBytecode ),
		&pInputLayout ) ) )
	{
		throw CHILI_GFX_EXCEPTION( hr,L"Creating input layout" );
	}


	////////////////////////////////////////////////////
	// Create sampler state for fullscreen textured quad
	D3D11_SAMPLER_DESC sampDesc = {};
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	if( FAILED( hr = pDevice->CreateSamplerState( &sampDesc,&pSamplerState ) ) )
	{
		throw CHILI_GFX_EXCEPTION( hr,L"Creating sampler state" );
	}

	// allocate memory for sysbuffer (16-byte aligned for faster access)
	pSysBuffer = reinterpret_cast<Color*>( 
		_aligned_malloc( sizeof( Color ) * Graphics::ScreenWidth * Graphics::ScreenHeight,16u ) );
}

Graphics::~Graphics()
{
	// free sysbuffer memory (aligned free)
	if( pSysBuffer )
	{
		_aligned_free( pSysBuffer );
		pSysBuffer = nullptr;
	}
	// clear the state of the device context before destruction
	if( pImmediateContext ) pImmediateContext->ClearState();
}

void Graphics::EndFrame()
{
	HRESULT hr;

	// lock and map the adapter memory for copying over the sysbuffer
	if( FAILED( hr = pImmediateContext->Map( pSysBufferTexture.Get(),0u,
		D3D11_MAP_WRITE_DISCARD,0u,&mappedSysBufferTexture ) ) )
	{
		throw CHILI_GFX_EXCEPTION( hr,L"Mapping sysbuffer" );
	}
	// setup parameters for copy operation
	Color* pDst = reinterpret_cast<Color*>(mappedSysBufferTexture.pData );
	const size_t dstPitch = mappedSysBufferTexture.RowPitch / sizeof( Color );
	const size_t srcPitch = Graphics::ScreenWidth;
	const size_t rowBytes = srcPitch * sizeof( Color );
	// perform the copy line-by-line
	for( size_t y = 0u; y < Graphics::ScreenHeight; y++ )
	{
		memcpy( &pDst[ y * dstPitch ],&pSysBuffer[y * srcPitch],rowBytes );
	}
	// release the adapter memory
	pImmediateContext->Unmap( pSysBufferTexture.Get(),0u );

	// render offscreen scene texture to back buffer
	pImmediateContext->IASetInputLayout( pInputLayout.Get() );
	pImmediateContext->VSSetShader( pVertexShader.Get(),nullptr,0u );
	pImmediateContext->PSSetShader( pPixelShader.Get(),nullptr,0u );
	pImmediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	const UINT stride = sizeof( FSQVertex );
	const UINT offset = 0u;
	pImmediateContext->IASetVertexBuffers( 0u,1u,pVertexBuffer.GetAddressOf(),&stride,&offset );
	pImmediateContext->PSSetShaderResources( 0u,1u,pSysBufferTextureView.GetAddressOf() );
	pImmediateContext->PSSetSamplers( 0u,1u,pSamplerState.GetAddressOf() );
	pImmediateContext->Draw( 6u,0u );

	// flip back/front buffers
	if( FAILED( hr = pSwapChain->Present( 1u,0u ) ) )
	{
		if( hr == DXGI_ERROR_DEVICE_REMOVED )
		{
			throw CHILI_GFX_EXCEPTION( pDevice->GetDeviceRemovedReason(),L"Presenting back buffer [device removed]" );
		}
		else
		{
			throw CHILI_GFX_EXCEPTION( hr,L"Presenting back buffer" );
		}
	}
}

void Graphics::BeginFrame()
{
	// clear the sysbuffer
	memset( pSysBuffer,0u,sizeof( Color ) * Graphics::ScreenHeight * Graphics::ScreenWidth );
}

void Graphics::DrawrecAligned(const Vec2 & PointA, const Vec2 & PointB, const float Width, Color c)
{
	Vec2 A;
	Vec2 B;
	Vec2 C;
	Vec2 D;
	Vec2 Result;
	double Radian;
	float Calc_vx;
	float Calc_vy;
	{		
	    Radian = (double)atan2(PointB.x - PointA.x, PointB.y - PointA.y);    // gets radians for trig function
		Radian = Radian + 1.571; // plus 90 deg
		Calc_vx = float(sin(Radian) * Width); // trig functions
		Calc_vy = float(cos(Radian) * Width);
		Result = { Calc_vx, Calc_vy };
		A = PointA + Result;
		C = PointB - Result;
	}
	{
		Radian = (double)atan2(PointB.x - PointA.x, PointB.y - PointA.y);    // gets radians for trig function
		Radian = Radian - 1.571; // minus 90 deg
		Calc_vx = float(sin(Radian) * Width); // trig functions
		Calc_vy = float(cos(Radian) * Width);
		Result = { Calc_vx, Calc_vy };
		B = PointA + Result;
		D = PointB - Result;
	}
	
	DrawPoly( A , B , C , c );
	DrawPoly( A , C , D , c );
	

}

void Graphics::DrawLine(Vec2 & Start, Vec2 & Finish, Color c)
{
	// gets the right angle triangle 
	int dirived_x = int(Finish.x - Start.x);
	int dirived_y = int(Finish.y - Start.y);
	// gets the longest side of triangle in absolute for both sides 
	int steps = abs(dirived_x) > abs(dirived_y) ? abs(dirived_x) : abs(dirived_y);
	// sets x and y increments per loop by dividing by the steps for first set of lines;
	float x_inc = dirived_x / float(steps);
	float y_inc = dirived_y / float(steps);
	float Line_x = Start.x;
	float Line_y = Start.y;
	////////////////////////////////
	for (int i = 0; i < steps; i++)
	{
		PutPixel( (int)Line_x, (int)Line_y, c);
		Line_x += x_inc;
		Line_y += y_inc;
	}
	///////////////////////////////
}

void Graphics::DrawRecFrame(const Vec2 & UL, const Vec2 & BR, Color c)
{
	for (int y = (int)UL.y; y <= BR.y; y++)
	{
		PutPixel((int)UL.x, y, c);
		PutPixel((int)BR.x, y, c);
	}
	for (int x = (int)UL.x + 1; x <= BR.x - 1; x++)
	{
		PutPixel(x, (int)UL.y, c);
		PutPixel(x, (int)BR.y, c);
	}
}

void Graphics::Drawrec(const Vec2 & top_left, const Vec2 & bottom_right, Color c)
{
	for (int y = (int)top_left.y; y <= bottom_right.y ; y++ )
	{
		for (int x = (int)top_left.x; x <= bottom_right.x; x++ )
		{
			PutPixel(x, y, c );
		}
	}
}

void Graphics::Drawrec(const float Lx, const float Rx, const float Ty, const float By, Color c)
{
	for (int y = (int)Ty; y <= By; y++)
	{
		for (int x = (int)Lx; x <= Rx; x++)
		{
			PutPixel(x, y, c);
		}
	}
}

void Graphics::Drawrecbeveled(const Vec2 & Point_a, const Vec2 & Point_b, const float& Bev_width, Color c)
{ 
	
	Color Top = Scaler(c, 1.3f);
	Color Left = Scaler(c, 1.1f);
	Color Right = Scaler(c, 0.9f);
	Color Bottom = Scaler(c, 0.7f);

	// inner rec
	Vec2 inner_a = Point_a;
	Vec2 inner_b = Point_b;
	inner_a = inner_a + Bev_width;
	inner_b = inner_b - Bev_width;
	// inner rec
	Drawrec(inner_a , inner_b , c );
	// top bevel
	Drawrec(inner_a.x, inner_b.x, Point_a.y, inner_a.y, Top);
	Right_tri_RT( inner_a.x , Point_a.y , Bev_width , Top );	
	Right_tri_LT( inner_b.x, Point_a.y , Bev_width , Top );

	// Left bevel
	Drawrec(Point_a.x, inner_a.x, inner_a.y, inner_b.y, Left);
	Right_tri_LB(Point_a.x, inner_a.y, Bev_width, Left);
	Right_tri_LT(Point_a.x, inner_b.y, Bev_width, Left);

	// right bevel 
	Drawrec(inner_b.x, Point_b.x, inner_a.y, inner_b.y, Right);
	Right_tri_RB(Point_b.x, inner_a.y, Bev_width, Right);
	Right_tri_RT(Point_b.x, inner_b.y, Bev_width, Right);

	// bottom bevel
	Drawrec(inner_a.x, inner_b.x, inner_b.y, Point_b.y, Bottom);
	Right_tri_RB(inner_a.x, Point_b.y, Bev_width, Bottom);
	Right_tri_LB(inner_b.x, Point_b.y, Bev_width, Bottom);
	
}

void Graphics::DrawPoly(const Vec2& Point_A, const Vec2& Point_B, const Vec2& Point_C, Color poly_c)
{

	/////// fix swaping of coords so poly draws with any dimensions ////////

	// 28.4 fixed point coords
	const int x1 = (int)round(16.0f * Point_A.x);
	const int y1 = (int)round(16.0f * Point_A.y);

	const int x2 = (int)round(16.0f * Point_B.x);
	const int y2 = (int)round(16.0f * Point_B.y);

	const int x3 = (int)round(16.0f * Point_C.x);
	const int y3 = (int)round(16.0f * Point_C.y);

	// deltas
	const int DX12 = x1 - x2;
	const int DX23 = x2 - x3;
	const int DX31 = x3 - x1;

	const int DY12 = y1 - y2;
	const int DY23 = y2 - y3;
	const int DY31 = y3 - y1;

	// fixed point deltas 
	const int FDX12 = DX12 << 4;
	const int FDX23 = DX23 << 4;
	const int FDX31 = DX31 << 4;

	const int FDY12 = DY12 << 4;
	const int FDY23 = DY23 << 4;
	const int FDY31 = DY31 << 4;

	// bounding rect 
	int minx = (custom_min(x1, x2, x3) + 15) >> 4;
	int maxx = (custom_max(x1, x2, x3) + 15) >> 4;
	int miny = (custom_min(y1, y2, y3) + 15) >> 4;
	int maxy = (custom_max(y1, y2, y3) + 15) >> 4;

	// set block size 
	const int quad = 8;

	// start in corner of block
	minx &= ~(quad - 1);
	miny &= ~(quad - 1);

	// half edge constants 
	int C1 = DY12 * x1 - DX12 * y1;
	int C2 = DY23 * x2 - DX23 * y2;
	int C3 = DY31 * x3 - DX31 * y3;

	// correct for fill convention 
	if (DY12 < 0 || (DY12 == 0 && DX12 > 0)) C1++;
	if (DY23 < 0 || (DY23 == 0 && DX23 > 0)) C2++;
	if (DY31 < 0 || (DY31 == 0 && DX31 > 0)) C3++;

/////////////// seperate ////////////////

	// loop though blocks of quad size
	for (int y = miny; y < maxy; y += quad)
	{
		for (int x = minx; x < maxx; x += quad)
		{
			// corners of quad block check
			int X0 = x << 4;
			int X1 = (x + quad - 1) << 4;
			int Y0 = y << 4;
			int Y1 = (y + quad - 1) << 4;

			// evaluate halfspace functions
			bool a00 = C1 + DX12 * Y0 - DY12 * X0 > 0;
			bool a10 = C1 + DX12 * Y0 - DY12 * X1 > 0;
			bool a01 = C1 + DX12 * Y1 - DY12 * X0 > 0;
			bool a11 = C1 + DX12 * Y1 - DY12 * X1 > 0;
			int a = (a00 << 0) | (a10 << 1) | (a01 << 2) | (a11 << 3);

			bool b00 = C2 + DX23 * Y0 - DY23 * X0 > 0;
			bool b10 = C2 + DX23 * Y0 - DY23 * X1 > 0;
			bool b01 = C2 + DX23 * Y1 - DY23 * X0 > 0;
			bool b11 = C2 + DX23 * Y1 - DY23 * X1 > 0;
			int b = (b00 << 0) | (b10 << 1) | (b01 << 2) | (b11 << 3);

			bool c00 = C3 + DX31 * Y0 - DY31 * X0 > 0;
			bool c10 = C3 + DX31 * Y0 - DY31 * X1 > 0;
			bool c01 = C3 + DX31 * Y1 - DY31 * X0 > 0;
			bool c11 = C3 + DX31 * Y1 - DY31 * X1 > 0;
			int c = (c00 << 0) | (c10 << 1) | (c01 << 2) | (c11 << 3);

			// skip quad block when outside an edge 
			if (a == 0 || b == 0 || c == 0 ) continue;

			// accept whole quad block when totally covered
			if (a == 15 && b == 15 && c == 15)
			{
				for (int iy = 0; iy < quad; iy++)
				{
					for (int ix = x; ix < x + quad; ix++)
					{
						PutPixel(ix, iy + y , poly_c);
					}
				}
			}
			else  // partially coverd quad block
			{
				int CY1 = C1 + (DX12 * Y0) - (DY12 * X0);
				int CY2 = C2 + (DX23 * Y0) - (DY23 * X0);
				int CY3 = C3 + (DX31 * Y0) - (DY31 * X0);

				for (int iy = y; iy < y + quad; iy++)
				{
					int CX1 = CY1;
					int CX2 = CY2;
					int CX3 = CY3;

					bool done = false;
					for (int ix = x; ix < x + quad; ix++)
					{
						if (CX1 > 0 && CX2 > 0 && CX3 > 0)
						{
							PutPixel(ix, iy , poly_c);
							done = true;
						}
						else if (done) break;

						CX1 -= FDY12;
						CX2 -= FDY23;
						CX3 -= FDY31;
					}
					CY1 += FDX12;
					CY2 += FDX23;
					CY3 += FDX31;
				}
			}
		}
	}
}

Color Graphics::Scaler(const Color& base, const float& scaler)
{
	//////////// could be better ////////////
	int Rmod = base.GetR();
	int Gmod = base.GetG();
	int Bmod = base.GetB();

	if (Rmod * scaler > 255u)
	{
		Rmod = 255u;
	}
	else
	{
		Rmod = (int)round(Rmod * scaler);
	}
	if (Gmod * scaler > 255u)
	{
		Gmod = 255u;
	}
	else
	{
		Gmod = (int)round(Gmod * scaler);
	}
	if (Bmod * scaler > 255u)
	{
		Bmod = 255u;
	}
	else
	{
		Bmod = (int)round(Bmod * scaler);
	}

	return Color(Rmod, Gmod, Bmod);
}

void Graphics::Right_tri_LT(const float& Ax, const float& By, const float& Bev_width, Color c)
{
	// LT 
	int mod = 0;
	for (int y = (int)By; y <= By + Bev_width; y++)
	{
		for (int x = (int)Ax; x <= Ax + Bev_width - mod; x++)
		{
			PutPixel(x, y, c);
		}
		mod++;
	}
}

void Graphics::Right_tri_RT(const float& Ax, const float& By, const float& Bev_width, Color c)
{
	// RT
	int mod = 0;
	for (int y = (int)By; y <= By + Bev_width; y++)
	{
		for (int x = (int)Ax ; x >= Ax - Bev_width + mod ; x--)
		{
			PutPixel(x, y, c);
		}
		mod++;
	}
}

void Graphics::Right_tri_LB(const float& Ax, const float& By, const float& Bev_width, Color c)
{
	// LB
	int mod = 0;
	for (int y = (int)By; y >= By - Bev_width; y--)
	{
		for (int x = (int)Ax; x <= Ax + Bev_width - mod; x++)
		{
			PutPixel(x, y, c);
		}
		mod++;
	}
}

void Graphics::Right_tri_RB(const float& Ax, const float& By, const float& Bev_width, Color c)
{
	// RB
	int mod = 0;
	for (int y = (int)By; y >= By - Bev_width; y--)
	{
		for (int x = (int)Ax; x >= Ax - Bev_width + mod; x--)
		{
			PutPixel(x, y, c);
		}
		mod++;
	}
}

int Graphics::custom_min(const int A, const int B, const int C)
{
	int mintemp = A < B ? A : B;
	int minreturn = C < mintemp ? C : mintemp;
	return minreturn;
}

int Graphics::custom_max(const int A, const int B, const int C)
{
	int maxtemp = A > B ? A : B;
	int maxreturn = C > maxtemp ? C : maxtemp;
	return maxreturn;
}

void Graphics::PutPixel( int x,int y,Color c )
{
	assert( x >= 0 );
	assert( x < int( Graphics::ScreenWidth ) );
	assert( y >= 0 );
	assert( y < int( Graphics::ScreenHeight ) );
	pSysBuffer[Graphics::ScreenWidth * y + x] = c;
}


//////////////////////////////////////////////////
//           Graphics Exception
Graphics::Exception::Exception( HRESULT hr,const std::wstring& note,const wchar_t* file,unsigned int line )
	:
	ChiliException( file,line,note ),
	hr( hr )
{}

std::wstring Graphics::Exception::GetFullMessage() const
{
	const std::wstring empty = L"";
	const std::wstring errorName = GetErrorName();
	const std::wstring errorDesc = GetErrorDescription();
	const std::wstring& note = GetNote();
	const std::wstring location = GetLocation();
	return    (!errorName.empty() ? std::wstring( L"Error: " ) + errorName + L"\n"
		: empty)
		+ (!errorDesc.empty() ? std::wstring( L"Description: " ) + errorDesc + L"\n"
			: empty)
		+ (!note.empty() ? std::wstring( L"Note: " ) + note + L"\n"
			: empty)
		+ (!location.empty() ? std::wstring( L"Location: " ) + location
			: empty);
}

std::wstring Graphics::Exception::GetErrorName() const
{
	return DXGetErrorString( hr );
}

std::wstring Graphics::Exception::GetErrorDescription() const
{
	std::array<wchar_t,512> wideDescription;
	DXGetErrorDescription( hr,wideDescription.data(),wideDescription.size() );
	return wideDescription.data();
}

std::wstring Graphics::Exception::GetExceptionType() const
{
	return L"Chili Graphics Exception";
}