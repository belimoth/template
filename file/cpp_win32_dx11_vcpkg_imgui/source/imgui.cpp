#include <imgui/imgui.h>
#include <imgui/imgui_impl_win32.h>
#include <imgui/imgui_impl_dx11.h>

#pragma comment( lib, "imgui.lib" )

void ui_init() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui_ImplWin32_Init( app.system.window );
	ImGui_ImplDX11_Init( app.graphics.device, app.graphics.device_context );

	float dpi_scale = 1.5;
	// io.Fonts->AddFontDefault();
	io.Fonts->AddFontFromFileTTF( "C:\\Windows\\Fonts\\segoeui.ttf", 18 * dpi_scale );
	// ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18 * dpi_scale, nullptr, io.Fonts->GetGlyphRangesJapanese() );
	// IM_ASSERT(font != nullptr);
}

void ui_render() {
	ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

	//

    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos ( ImVec2( main_viewport->WorkPos .x, main_viewport->WorkPos .y ), ImGuiCond_FirstUseEver );

	int width = main_viewport->WorkSize.x;
	width = 450;
    ImGui::SetNextWindowSize( ImVec2( width, main_viewport->WorkSize.y ), ImGuiCond_FirstUseEver );

	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	window_flags |= ImGuiWindowFlags_NoBackground;

    ImGui::Begin( "Clay", 0, window_flags );

	ImGui::Text( "Scenes" );

	static bool hide_unavailable = false;

	ImGui::Checkbox( "Hide unavailable", &hide_unavailable );

	char* scenes[] = {
		"Game",
		"Wolfenstein",
		"StarCraft",
	};

    static int scenes_i = 0;

	for ( int i = 0; i < zed_data_size( scenes ); i++ ) {
		const bool is_selected = ( scenes_i == i );
		if ( ImGui::Selectable( scenes[i], is_selected ) ) scenes_i = i;
		if ( is_selected ) ImGui::SetItemDefaultFocus();
	}

	ImGui::End();

	//

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void ui_fini() {
	ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}
