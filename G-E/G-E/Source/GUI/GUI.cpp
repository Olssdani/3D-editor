#include "GUI.h"
GUI::GUI(GLFWwindow *w, Render *r){
	window = w;
	Intialize();
	render = r;
}

void GUI::Intialize() {
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls


	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Read 'misc/fonts/README.txt' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != NULL);

}

void GUI::guiRender(){
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Scene");                          // Create a window called "Hello, world!" and append into it.
		// Most "big" widgets share a common width settings by default.
	//ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.65f);    // Use 2/3 of the space for widgets and 1/3 for labels (default)
		ImGui::PushItemWidth(ImGui::GetFontSize() * -12);           // Use fixed width for labels (by passing a negative value), the rest goes to widgets. We choose a width proportional to our font size.

		// Menu Bar
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Menu"))
			{
				//ShowExampleMenuFile();
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Examples"))
			{
				/*ImGui::MenuItem("Main menu bar", NULL, &show_app_main_menu_bar);
				ImGui::MenuItem("Console", NULL, &show_app_console);
				ImGui::MenuItem("Log", NULL, &show_app_log);
				ImGui::MenuItem("Simple layout", NULL, &show_app_layout);
				ImGui::MenuItem("Property editor", NULL, &show_app_property_editor);
				ImGui::MenuItem("Long text display", NULL, &show_app_long_text);
				ImGui::MenuItem("Auto-resizing window", NULL, &show_app_auto_resize);
				ImGui::MenuItem("Constrained-resizing window", NULL, &show_app_constrained_resize);
				ImGui::MenuItem("Simple overlay", NULL, &show_app_simple_overlay);
				ImGui::MenuItem("Manipulating window titles", NULL, &show_app_window_titles);
				ImGui::MenuItem("Custom rendering", NULL, &show_app_custom_rendering);
				ImGui::MenuItem("Documents", NULL, &show_app_documents);*/
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Help"))
			{
				/*ImGui::MenuItem("Metrics", NULL, &show_app_metrics);
				ImGui::MenuItem("Style Editor", NULL, &show_app_style_editor);
				ImGui::MenuItem("About Dear ImGui", NULL, &show_app_about);*/
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::End();
	}
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


	/*ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Objects");                          // Create a window called "Hello, world!" and append into it.



			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			{
				Box b = Box(1, 1, 1);
				std::cout << (((float)rand()) / RAND_MAX * 4) - 2 << std::endl;
				b.Translate(glm::vec3((((float)rand())/RAND_MAX*4)-2, (((float)rand()) / RAND_MAX * 4) - 2, (((float)rand()) / RAND_MAX * 4) - 2));
				b.RotateY(45.0f * D2R);
				b.RotateX(45.0f * D2R);
				b.RotateZ(45.0f * D2R);
				objects.push_back(b);
			}

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}*/

}