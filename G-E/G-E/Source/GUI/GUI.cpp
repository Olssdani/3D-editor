#include "GUI.h"
#include "Object/Box.h"
#include "Object/Object.h"
#include "Light/Light.h"
#include "Light/DirectionalLight.h"
#include "Light/PointLight.h"
#include "Scene/Scene.h"



GUI::GUI(GLFWwindow *w, Render *r) {
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

	ImGui::StyleColorsLight();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
}

void GUI::guiRender(const unsigned int editorTexture, const unsigned int gameTexture, 
					const unsigned int viewportWidth, const unsigned int viewportHeight,
					const unsigned int textureWidth, const unsigned int textureHeight) {
	static bool no_titlebar = true;
	static bool no_scrollbar = false;
	static bool no_menu = false;
	static bool no_move = true;
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
		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(viewportWidth, viewportHeight), ImGuiCond_Once);
		ImGui::Begin("Scene", NULL, window_flags);                          // Create a window called "Hello, world!" and append into it.
		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("Menu")) {
				ImGui::MenuItem("New(Placeholder)");
				ImGui::MenuItem("Save(Placeholder)");
				ImGui::MenuItem("Open(Placeholder)");
				ImGui::EndMenu();
			}
			ImGui::MenuItem("Edit");
			ImGui::EndMenuBar();
		}

		// left
		static int selected = 0;
		ImGui::BeginChild("left pane", ImVec2(viewportWidth *0.15, 200), true);
		//Add div
		if (ImGui::CollapsingHeader("Add")) {
			//Objects
			if (ImGui::TreeNode("Objects")) {
				//Cube
				if (ImGui::TreeNode("Cube")) {
					static char object_name[128] = "Box";
					const char default[5] = "Box";
					ImGui::Text("Name of Object");
					ImGui::SameLine();
					ImGui::InputText(" ", object_name, IM_ARRAYSIZE(object_name));
					//Position of object
					ImGui::Text("Position");
					ImGui::SameLine();
					ImGui::InputFloat3("", addPosition, 3);
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
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Lightning")) {
				if (ImGui::TreeNode("Point Light")){
					static char object_name[128] = "Light";
					const char default[11] = "Light";
					ImGui::Text("Name of light");
					ImGui::SameLine();
					ImGui::InputText(" ", object_name, IM_ARRAYSIZE(object_name));

					ImGui::Text("Position");
					ImGui::SameLine();
					ImGui::InputFloat3("", addPosition, 3);
					ImGui::SameLine();
					if (ImGui::Button("Add")) {
						glm::vec3 pos = glm::vec3(addPosition[0], addPosition[1], addPosition[2]);
						PointLight *l = new PointLight(pos);

						if (strcmp(default, object_name) == 0) {
							l->setName(object_name + std::to_string(l->getID()));
						}
						else {
							l->setName(object_name);
						}
						render->getScene()->addPointLight(l);
					}
					ImGui::TreePop();
				}
				ImGui::TreePop();
			}
		}

		ImGui::EndChild();
		ImGui::SameLine();

		// right
		ImGui::BeginChild("item view", ImVec2(textureWidth, 0));
		{
			if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None)) {
				if (ImGui::BeginTabItem("Editor")){
					ImGui::Image((void*)(intptr_t)editorTexture, ImVec2(textureWidth, textureHeight));
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Game")){
					ImGui::Image((void*)(intptr_t)gameTexture, ImVec2(textureWidth, textureHeight));
					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}
		}
		ImGui::EndChild();
		ImGui::SameLine();

		ImGui::BeginChild("Scene graph", ImVec2(0, 0)); // Leave room for 1 line below us
		{
			//Display and edit all objects in scene
			if (ImGui::CollapsingHeader("Objects in scene")) {
				for (auto &object : render->getScene()->getObjectList()) {
					char *char_name = string2char(object->getName());
					if (ImGui::TreeNode(char_name)) {
						ImGui::Text("Name:(Cannot Change Right Now)");
						ImGui::SameLine();
						ImGui::InputText(" ", char_name, IM_ARRAYSIZE(char_name));
						object->setName(char_name);
						ImGui::TreePop();

						ImGui::Indent();
						ImGui::Text("Translate:");
						ImGui::SameLine();
						ImGui::InputFloat3("", addPosition, 3);
						ImGui::SameLine();
						//Create object and add it to scene
						if (ImGui::Button("Add")) {

							object->Translate(glm::vec3(addPosition[0], addPosition[1], addPosition[2]));
						}

						if (ImGui::TreeNode("Material")) {
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
			if (ImGui::CollapsingHeader("Lights")){
				if (ImGui::TreeNode("Directional Light")) {
					ImGui::Text("Name:(Cannot Change Right Now)");
					ImGui::TreePop();
				}

				for (PointLight *light : render->getScene()->getPointLights()) {
					char *char_name = string2char(light->getName());
					if (ImGui::TreeNode(char_name)) {
						ImGui::Text("Name:(Cannot Change Right Now)");
						ImGui::SameLine();
						ImGui::InputText(" ", char_name, IM_ARRAYSIZE(char_name));
						light->setName(char_name);

						//Constant
						ImGui::Text("Constant Factor:");
						ImGui::SameLine();
						float c = light->getConstant();
						ImGui::InputFloat("Constant", &c, 0.01f, 1.0f, "%.3f");
						light->setConstant(c);

						//Linear
						ImGui::Text("Linear Factor:");
						ImGui::SameLine();
						float l = light->getLinear();
						ImGui::InputFloat("Linear", &l, 0.01f, 1.0f, "%.3f");
						light->setLinear(l);

						//Quadratic
						ImGui::Text("Quadratic Factor:");
						ImGui::SameLine();
						float q = light->getQuadratic();
						ImGui::InputFloat("Quadratic", &q, 0.01f, 1.0f, "%.3f");
						light->setQuadratic(q);

						//Ambient light
						glm::vec3 temp = light->getAmbient();
						my_color[0] = temp.x;
						my_color[1] = temp.y;
						my_color[2] = temp.z;
						ImGui::Text("Ambient");
						ImGui::SameLine();
						ImGui::ColorEdit3("Ambient", my_color);
						temp.x = my_color[0];
						temp.y = my_color[1];
						temp.z = my_color[2];
						light->SetAmbient(temp);

						//Ambient light
						temp = light->getDiffuse();
						my_color[0] = temp.x;
						my_color[1] = temp.y;
						my_color[2] = temp.z;
						ImGui::Text("Diffuse");
						ImGui::SameLine();
						ImGui::ColorEdit3("Diffuse", my_color);
						temp.x = my_color[0];
						temp.y = my_color[1];
						temp.z = my_color[2];
						light->SetDiffuse(temp);

						//Ambient light
						temp = light->getSpecular();
						my_color[0] = temp.x;
						my_color[1] = temp.y;
						my_color[2] = temp.z;
						ImGui::Text("Specular");
						ImGui::SameLine();
						ImGui::ColorEdit3("Specular", my_color);
						temp.x = my_color[0];
						temp.y = my_color[1];
						temp.z = my_color[2];
						light->SetSpecular(temp);

						ImGui::TreePop();
					}
				}
			}
		}
		ImGui::EndChild();
		ImGui::End();
	}
	ImGui::ShowDemoWindow();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
