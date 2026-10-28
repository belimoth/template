#include "windows.h"

#include <wrl.h>
#include <wil/com.h>

#include <WebView2.h>
#pragma comment( lib, "WebView2LoaderStatic.lib" )
#pragma comment( lib, "Advapi32.lib" )

using namespace Microsoft::WRL;

struct {
	HWND hwnd;

	wil::com_ptr<ICoreWebView2Controller> wvc;
	wil::com_ptr<ICoreWebView2> wv;
} app;

void web_view_on_size() {
	if ( ! app.wvc ) return;

	RECT bounds;
	GetClientRect( app.hwnd, &bounds );
	app.wvc->put_Bounds( bounds );
}

void web_view_init() {
	CreateCoreWebView2EnvironmentWithOptions( 0, 0, 0, Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>( []( HRESULT result, ICoreWebView2Environment* wve ) -> HRESULT {
		wve->CreateCoreWebView2Controller( app.hwnd, Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>( []( HRESULT result, ICoreWebView2Controller* wvc ) -> HRESULT {
			app.wvc = wvc;
			app.wvc->get_CoreWebView2( &app.wv );

			//

			web_view_on_size();

			//

			app.wv->Navigate( L"https://www.bing.com/" );

			// navigation events

			EventRegistrationToken token;
			app.wv->add_NavigationStarting(Callback<ICoreWebView2NavigationStartingEventHandler>(
				[](ICoreWebView2* webview, ICoreWebView2NavigationStartingEventArgs* args) -> HRESULT {
					wil::unique_cotaskmem_string uri;
					args->get_Uri(&uri);
					std::wstring source(uri.get());
					if (source.substr(0, 5) != L"https") {
						args->put_Cancel(true);
					}
					return S_OK;
				}).Get(), &token);

			// scripting

			app.wv->AddScriptToExecuteOnDocumentCreated( L"Object.freeze(Object);", 0 );

			//

			app.wv->add_WebMessageReceived(Callback<ICoreWebView2WebMessageReceivedEventHandler>(
				[](ICoreWebView2* webview, ICoreWebView2WebMessageReceivedEventArgs* args) -> HRESULT {
					wil::unique_cotaskmem_string message;
					args->TryGetWebMessageAsString(&message);
					// processMessage(&message);
					webview->PostWebMessageAsString(message.get());
					return S_OK;
				}).Get(), &token);

			//

			app.wv->AddScriptToExecuteOnDocumentCreated(
				L"window.chrome.webview.addEventListener('message', event => alert(event.data));" \
				L"window.chrome.webview.postMessage(window.document.URL);",
				0
			);

			return S_OK;
		}).Get());

		return S_OK;
	}).Get());
}

LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam ) {
	switch (message) {
		case WM_SIZE:
			web_view_on_size();
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc( hwnd, message, wParam, lParam );
			break;
	}

	return 0;
}

int CALLBACK WinMain( HINSTANCE instance, HINSTANCE, LPSTR, int show ) {
	WNDCLASSEX wcex;

	wcex.cbSize        = sizeof(WNDCLASSEX);
	wcex.style         = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc   = WndProc;
	wcex.cbClsExtra    = 0;
	wcex.cbWndExtra    = 0;
	wcex.hInstance     = instance;
	wcex.hIcon         = LoadIcon( instance, IDI_APPLICATION );
	wcex.hCursor       = LoadCursor( 0, IDC_ARROW );
	wcex.hbrBackground = (HBRUSH)( COLOR_WINDOW + 1 );
	wcex.lpszMenuName  = NULL;
	wcex.lpszClassName = "DesktopApp";
	wcex.hIconSm       = LoadIcon( wcex.hInstance, IDI_APPLICATION );

	RegisterClassEx(&wcex);

	app.hwnd = CreateWindow(
		"DesktopApp",
		"WebView sample",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1200,
		900,
		0,
		0,
		instance,
		0
	);

	ShowWindow( app.hwnd, show );
	UpdateWindow( app.hwnd );

	//

	web_view_init();

	//

	MSG msg;
	while ( GetMessage( &msg, 0, 0, 0 ) )
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
