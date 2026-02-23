#pragma once

#include <d2d1_1.h>
#pragma comment (lib, "d2d1.lib")

#include <dwrite.h>
#pragma comment (lib, "dwrite.lib")

ID2D1DeviceContext *d2d_context;

// void d2d_init() {
//
// 	// create render target texture
// 	D3D11_TEXTURE2D_DESC td;
// 	td.Width          = 1024;
// 	td.Height         = 1024;
// 	td.MipLevels      = 1;
// 	td.ArraySize      = 1;
// 	td.Format         = DXGI_FORMAT_R8G8B8A8_UNORM;
// 	td.SampleDesc     = { 1, 0 };
// 	td.Usage          = D3D11_USAGE_DEFAULT; //D3D11_USAGE_STAGING;
// 	td.BindFlags      = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
// 	td.CPUAccessFlags = 0; //D3D11_CPU_ACCESS_READ;
// 	td.MiscFlags      = 0;
//
// 	ID3D11Texture2D *fontTexture;
// 	device->CreateTexture2D( &td, 0, &fontTexture );
//
// 	IDWriteFactory *dwf;
// 	DWriteCreateFactory( DWRITE_FACTORY_TYPE_SHARED, __uuidof( IDWriteFactory ), (IUnknown**) &dwf );
//
// 	IDWriteTextFormat *dwtf;
//
// 	dwf->CreateTextFormat(
// 		L"Segoe MDL2 Assets",
// 		0,
// 		DWRITE_FONT_WEIGHT_REGULAR,
// 		DWRITE_FONT_STYLE_NORMAL,
// 		DWRITE_FONT_STRETCH_NORMAL,
// 		32.0,
// 		L"",//L"en-us",
// 		&dwtf
// 	);
//
// 	dwtf->SetTextAlignment( DWRITE_TEXT_ALIGNMENT_CENTER );
// 	dwtf->SetParagraphAlignment( DWRITE_PARAGRAPH_ALIGNMENT_CENTER );
//
// 	D2D1_RECT_F rect = { 0.0, 0.0, 1024.0, 1024.0 };
//
// 	ID2D1SolidColorBrush *brush;
// 	d2d_context->CreateSolidColorBrush( { 1.0, 1.0, 1.0, 1.0 }, &brush);
// 	d2d_context->SetTextAntialiasMode( D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE );
// 	d2d_context->BeginDraw();
//
// 	int length = sizeof( glyphs ) / sizeof( *glyphs );
//
// 	for( int i = 0; i < length; i ++ ) {
// 		float x, y;
// 		x = fmod( 32.0f * i, 1024.0f );
// 		y = ( 32.0f * i - x ) / 32.0f;
//
// 		d2dContext->DrawText(
// 			&glyphs[i],
// 			1,
// 			dwtf,
// 			{ x, y, x + 32.0f, y + 32.0f },
// 			brush,
// 			D2D1_DRAW_TEXT_OPTIONS_CLIP // NOTE NOTE NOTE NOTE NOTE, actually measure glyphs please
// 		);
// 	}
//
// 	d2dContext->EndDraw();
//
// 	SaveDDSTextureToFile( deviceContext, fontTexture, L"output.dds" );
// }
