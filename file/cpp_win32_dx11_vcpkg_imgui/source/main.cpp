#include "windows.h"

// float windowBorder = 1.0;

LRESULT CALLBACK window_procedure( HWND window, UINT message, WPARAM w_param, LPARAM l_param ) {
	extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND, UINT, WPARAM, LPARAM );

	if ( ImGui_ImplWin32_WndProcHandler( window, message, w_param, l_param ) ) return true;

	switch ( message ) {
		// device

		case WM_DEVICECHANGE: {
			// TODO

			break;
		}

		case WM_DPICHANGED: {
			zed_app_system_on_dpi();

			break;
		}

		// window

		case WM_ACTIVATEAPP: {
			if ( (bool)w_param == true ) {
				app.system.is_idle = false;
				// zed_hide_cursor();
			} else {
				app.system.is_idle = true;
				// zed_show_cursor();
			}

			break;
		}

		// case WM_CANCELMODE:
		// case WM_CHILDACTIVATE:
		// case WM_CLOSE:
		// case WM_COMPACTING:
		// case WM_CREATE:

		case WM_DESTROY: {
			PostQuitMessage( 0 );
			return 0;
		}

		// case WM_ENABLE:
		// case WM_GETICON:
		// case WM_INPUTLANGCHANGE:
		// case WM_INPUTLANGCHANGEREQUEST:
		// case WM_NCACTIVATE:
		// case WM_NCCALCSIZE:
		// case WM_NCCREATE:
		// case WM_NCDESTROY:
		// case WM_NULL:
		// case WM_QUERYDRAGICON:
		// case WM_QUERYOPEN:
		// case WM_QUIT:
		// case WM_SHOWWINDOW:
		// case WM_STYLECHANGED:
		// case WM_STYLECHANGING:
		// case WM_THEMECHANGED:
		// case WM_USERCHANGED:
		// case WM_WINDOWPOSCHANGED:
		// case WM_WINDOWPOSCHANGING:

		// window moving & sizing

		// case WM_MOVE:
		// case WM_MOVING:

		// case WM_GETMINMAXINFO:

		case WM_ENTERSIZEMOVE: {
			app.system.is_idle = true;
			break;
		}

		case WM_EXITSIZEMOVE: {
			app.system.is_idle = false;
			break;
		}

		// TODO doesn't minimize
		case WM_SIZE: {
			switch ( w_param ) {
				case SIZE_MAXIMIZED:
				case SIZE_RESTORED: {
					zed_app_system_on_size();

					// TODO is_sizing is never assigned
					if ( app.system.is_sizing ) {
						// TODO re-render held frame, not render a new one
						// zed_graphics_render();
					}

					app.system.is_idle = false;
					break;
				}

				case SIZE_MINIMIZED: {
					app.system.is_idle = true;
					break;
				}
			}

			return 0;
		}

		// case WM_SIZING:
	}

	return DefWindowProc( window, message, w_param, l_param );
}
