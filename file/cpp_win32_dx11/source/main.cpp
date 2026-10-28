#pragma warning(disable : 4820)

#include "windows.h"
#include "d3d11.h"

#define window_width  800
#define window_height 600
#define window_title  "Hello, World!"

typedef void *handle;
typedef unsigned int uint;

struct app_t {
	int  quit;
    HWND window;

    struct app_graphics_t {
        ID3D11Device           *device;
        ID3D11DeviceContext    *device_context;
        IDXGISwapChain         *swap_chain;
        ID3D11Texture2D        *rtb;
        ID3D11RenderTargetView *rtv;
        ID3D11Texture2D        *dsb;
        ID3D11DepthStencilView *dsv;
        void                   *waitable;
    } graphics;
} app;

LRESULT __stdcall app_window_procedure( HWND window, UINT message, WPARAM w_param, LPARAM l_param ) {
    switch ( message ) {
        case WM_QUIT: {
            app.quit = true;
			break;
		}
    }

	return DefWindowProc( window, message, w_param, l_param );
}

void app_window() {
	HINSTANCE instance = GetModuleHandle(0);

	//

	WNDCLASS window_class      = {};
	window_class.style         = CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	window_class.lpfnWndProc   = app_window_procedure;
	window_class.hInstance     = instance;
	window_class.lpszClassName = "AppWindowClass";
	window_class.hCursor       = LoadCursor( 0, IDC_ARROW );

	RegisterClass( &window_class );

	//

	uint style = 0;

	// fullscreen

	// style |= WS_POPUP;
	// width  = app.system.device_size.x;
	// height = app.system.device_size.y;

	// windowed

	style |= WS_OVERLAPPEDWINDOW;
	// style |= WS_VISIBLE;

	//

	app.window = CreateWindowEx(
		0,
		window_class.lpszClassName,
		window_title,
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		window_width,
		window_height,
		0,
		0,
		instance,
		0
	);
}

void app_graphics_device_and_swap_chain_0() {
    DXGI_SWAP_CHAIN_DESC scd   = {};
	scd.BufferCount            = 2;
	scd.BufferUsage            = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferDesc.Width       = 0;
	scd.BufferDesc.Height      = 0;
	scd.BufferDesc.RefreshRate = { 60, 1 };
	scd.BufferDesc.Format      = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Scaling     = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.SampleDesc.Count       = 1;
	scd.SampleDesc.Quality     = 0;
	scd.OutputWindow           = app.window;
	scd.Windowed               = true;
	scd.SwapEffect             = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	scd.Flags                  = 0;

	uint flags = 0;

	// flags |= D3D11_CREATE_DEVICE_BGRA_SUPPORT;
	// flags |= D3D11_CREATE_DEVICE_DEBUG;

	D3D11CreateDeviceAndSwapChain(
		0,
		D3D_DRIVER_TYPE_HARDWARE,
		0,
		flags,
		0,
		0,
		D3D11_SDK_VERSION,
		&scd,
		&app.graphics.swap_chain,
		&app.graphics.device,
		0,
		&app.graphics.device_context
	);

	app.graphics.swap_chain->GetDesc( &scd );

	//

	struct {
		IDXGIFactory *f;
		IDXGIAdapter *a;
		IDXGIDevice  *d;
	} dxgi;

	app.graphics.device->QueryInterface( __uuidof( IDXGIDevice   ), (handle *)&dxgi.d );
	dxgi.d             ->GetParent     ( __uuidof( IDXGIAdapter  ), (handle *)&dxgi.a );
	dxgi.a             ->GetParent     ( __uuidof( IDXGIFactory  ), (handle *)&dxgi.f );

	dxgi.f->MakeWindowAssociation( app.window, DXGI_MWA_NO_WINDOW_CHANGES );
}

void app_graphics_rtv() {
	app.graphics.swap_chain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), (void **)&app.graphics.rtb );
	app.graphics.device->CreateRenderTargetView( app.graphics.rtb, 0, &app.graphics.rtv );
}

void app_graphics_dsv() {
    D3D11_TEXTURE2D_DESC dbd = {};
	dbd.Width              = window_width;
	dbd.Height             = window_height;
	dbd.MipLevels          = 1;
	dbd.ArraySize          = 1;
	dbd.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dbd.SampleDesc.Count   = 1;
	dbd.SampleDesc.Quality = 0;
	dbd.Usage              = D3D11_USAGE_DEFAULT;
	dbd.BindFlags          = D3D11_BIND_DEPTH_STENCIL;
	dbd.CPUAccessFlags     = 0;
	dbd.MiscFlags          = 0;

	app.graphics.device->CreateTexture2D( &dbd, 0, &app.graphics.dsb );

    //

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd = {};
	dsvd.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvd.ViewDimension      = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Texture2D.MipSlice = 0;

	app.graphics.device->CreateDepthStencilView( app.graphics.dsb, &dsvd, &app.graphics.dsv );
}

void app_graphics_set_render_target() {
    app.graphics.device_context->OMSetRenderTargets( 1, &app.graphics.rtv, app.graphics.dsv );
}

void app_graphics() {
    app_graphics_device_and_swap_chain_0();
	app_graphics_rtv();
	app_graphics_dsv();
    app_graphics_set_render_target();
}

void app_window_show() {
    ShowWindow( app.window, SW_SHOWNORMAL );
    UpdateWindow( app.window );
}

void app_init() {
    app_window();
    app_graphics();
    app_window_show();
}

void app_step() {
    float colour_array[4] = { 0.1f, 0.2f, 0.3f, 1.0f };
    app.graphics.device_context->ClearRenderTargetView( app.graphics.rtv, colour_array );
    app.graphics.swap_chain->Present( 0, 0 );
}

int main() {
    app_init();

    while( app.quit == false ) {
        MSG msg;

        while( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) ) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        app_step();
    }

    return 0;
}
