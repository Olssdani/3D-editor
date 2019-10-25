#include "GUI.h"
#include <stdlib.h>

GUI::GUI(GLFWwindow *w, Render *r){
	window = w;
	Intialize();
	render = r;

	addPosition[0] = 0;
	addPosition[1] = 0;
	addPosition[2] = 0;
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
	static bool no_titlebar = false;
	static bool no_scrollbar = false;
	static bool no_menu = false;
	static bool no_move = false;
	static bool no_resize = false;
	static bool no_collapse = false;
	static bool no_close = false;
	static bool no_nav = false;
	static bool no_background = false;
	static bool no_bring_to_front = false;

	ImGuiWindowFlags window_flags = 0;
	if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
	if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
	if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
	if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
	if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
	if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
	if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	//if (no_close)           p_open = NULL; // Don't pass our bool* to Begin
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	//IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context. Refer to examples app!"); // Exceptionally add an extra assert here for people confused with initial dear imgui setup
	{

		ImGui::Begin("Scene",NULL, window_flags);                          // Create a window called "Hello, world!" and append into it.
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Menu"))
			{
				ImGui::MenuItem("New(Placeholder)");
				ImGui::MenuItem("Save(Placeholder)");
				ImGui::MenuItem("Open(Placeholder)");
				ImGui::EndMenu();
			}
			ImGui::MenuItem("Edit");
			ImGui::EndMenuBar();
		}	

		//Add object div
		if (ImGui::CollapsingHeader("Add Objects"))
		{
			
			if (ImGui::TreeNode("Cube"))
			{
				
				static char object_name[128] = "Box";
				//Name  of object
				const char default[5] = "Box";
				
				ImGui::Text("Name of Object");
				ImGui::SameLine();
				ImGui::InputText(" ", object_name, IM_ARRAYSIZE(object_name));
				//Position of object
				ImGui::Text("Position");
				ImGui::SameLine();
				ImGui::InputFloat3("", addPosition, 3);
				ImGui::SameLine();
				//Create object and add it to scene
				if (ImGui::Button("Add")) {
					Box *b = new Box();
					b->Translate(glm::vec3(addPosition[0], addPosition[1], addPosition[2]));
					if (strcmp(default, object_name) == 0) {
						b->setName(object_name + std::to_string(b->getID()));
					}
					else {
						b->setName(object_name);
					}
					
					render->getScene()->addObject(b);
				}
				
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Placeholder"))
			{
				ImGui::Text("Name of Object");
				ImGui::TreePop();
			}
			
		}


		//Display and edit all objects in scene
		if (ImGui::CollapsingHeader("Objects in scene"))
		{
			for (auto &object : render->getScene()->getObjectList()) {
				//TODO swap all to char*
				std::string temp_name = object->getName();	
				char *char_name = new char(temp_name.size() + 1);
				temp_name.copy(char_name, temp_name.size() + 1);
				char_name[temp_name.size()] = '\0';

				if (ImGui::TreeNode(char_name))
				{
					ImGui::Text("Name:(Cannot Change Right Now)");
					ImGui::SameLine();
					ImGui::InputText(" ", char_name, IM_ARRAYSIZE(char_name));
					object->setName(char_name);
					ImGui::TreePop();

					ImGui::Text("Translate:");
					ImGui::SameLine();
					ImGui::InputFloat3("", addPosition, 3);
					ImGui::SameLine();
					//Create object and add it to scene
					if (ImGui::Button("Add")) {

						object->Translate(glm::vec3(addPosition[0], addPosition[1], addPosition[2]));
					}
					ImGui::Indent();
					if (ImGui::TreeNode("Material"))
					{
						
						glm::vec3 temp = object->getMaterial()->getColor();
						my_color[0] = temp.x;
						my_color[1] = temp.y;
						my_color[2] = temp.z;
						ImGui::Text("Color");
						ImGui::SameLine();
						ImGui::ColorEdit3("Color", my_color);
						object->getMaterial()->setColor(my_color);
						ImGui::TreePop();
						
					}
					ImGui::Unindent();
				}
			}	
		}
		if (ImGui::CollapsingHeader("Lights"))
		{
			for (auto &object : render->getScene()->getObjectList()) {
			
		}


		
		ImGui::End();
	}
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


}


