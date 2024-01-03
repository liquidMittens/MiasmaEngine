#include "gui\GUIBuilder.h"
#include "gui\imgui.h"
#include "gui\imgui_impl_opengl3.h"
#include "gui\imgui_impl_glfw.h"
#include "core\model\SandboxScene.h"
#include "core\components\MeshRenderable.h"
#include "core\rendering\Material.h"
#include "objects/GameObject.h"
using namespace Miasma::Component;
using namespace Miasma::UI;

void GUIBuilder::gbInitializeGUI(GLFWwindow* pWindow)
{
	// setup ImGui Context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// setup playfor/renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(pWindow, true);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();
}

void GUIBuilder::gbFeedInput()
{
	// im gui feed input 
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void GUIBuilder::gbShutdownGUI()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void GUIBuilder::gbRenderGUI()
{
	// render dear imgui to the screen 
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUIBuilder::gbTestWindow()
{
	// render dear imgui 
	ImGui::Begin("Test Window");
	ImGui::Button("Hello World!");
	ImGui::End();
}

void GUIBuilder::gbSceneInfoOverlay(tdogl::Camera& camera)
{
	static int location = 0;
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoSavedSettings;
	if (location >= 0) {
		const float PAD = 10.0f;
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 work_pos = viewport->WorkPos;
		ImVec2 work_size = viewport->WorkSize;
		ImVec2 window_pos, window_pos_pivot;
		window_pos.x = (location & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
		window_pos.y = (location & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
		window_pos_pivot.x = (location & 1) ? 1.0f : 0.0f;
		window_pos_pivot.y = (location & 2) ? 1.0f : 0.0f;
		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
		window_flags |= ImGuiWindowFlags_NoMove;
	}
	else if (location == -2) {
		// center the window
		ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		window_flags |= ImGuiWindowFlags_NoMove;
	}
	ImGui::SetNextWindowBgAlpha(0.25f); // transparent bg
	if (ImGui::Begin("Scene info", NULL, window_flags)) {
		ImGui::TextColored(GUI_TEXT_BLACK, "-Scene Information-");
		ImGui::Separator();
		ImGui::Text("FPS: %f", io.Framerate);
		ImGui::Separator();
		if (ImGui::IsMousePosValid()) {
			ImGui::Text("Mouse Position: %.1f,%.1f", io.MousePos.x, io.MousePos.y);
		}
		else {
			ImGui::TextColored(GUI_TEXT_RED, "Mouse Position: <invalid>");
		}
		ImGui::Separator();
		ImGui::Text("Camera pos: %.1f,%.1f,%.1f", camera.position().x, camera.position().y, camera.position().z);
		if (ImGui::BeginPopupContextWindow(0, ImGuiPopupFlags_MouseButtonLeft)) {
			if (ImGui::MenuItem("Custom", NULL, location == -1)) location = -1;
			if (ImGui::MenuItem("Center", NULL, location == -2)) location = -2;
			if (ImGui::MenuItem("Top-left", NULL, location == 0)) location = 0;
			if (ImGui::MenuItem("Top-right", NULL, location == 1)) location = 1;
			if (ImGui::MenuItem("Bottom-left", NULL, location == 2)) location = 2;
			if (ImGui::MenuItem("Bottom-right", NULL, location == 3)) location = 3;
			if (ImGui::MenuItem("Close")) ImGui::CloseCurrentPopup();
			ImGui::EndPopup();
		}
		ImGui::Separator();
		ImGui::Text("FoV: %.1f", camera.fieldOfView());
	}
	ImGui::End();
}

void GUIBuilder::gbSceneObjectsInfo(std::unique_ptr<IScene>& scene)
{
	ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanFullWidth;
	int ptr_id = 0;
	ImGui::Begin("Scene Graph");
	if (ImGui::TreeNodeEx("Scene Root", node_flags)) {
		for (const auto& gameobject : scene->GetGameObjectsList()) {
			Miasma::Component::MeshRenderable& mesh = gameobject->GetComponent<Miasma::Component::MeshRenderable>();
			if (&mesh != nullptr) {
				if (ImGui::TreeNodeEx((void*)(intptr_t)ptr_id, node_flags, gameobject->tag.c_str())) {
					ImGui::Text("MeshName: %s", mesh.m_meshName.c_str());
					bool objectActive = gameobject->IsActive();
					ImGui::Checkbox("Active ", &objectActive);
					gameobject->SetActive(objectActive);
					ImGui::Text("Pos: X: %.1f | Y: %.1f | Z: %.1f", mesh.gameObject->transform.GetPosition().x, mesh.gameObject->transform.GetPosition().y, mesh.gameObject->transform.GetPosition().z);
					float posX = mesh.gameObject->transform.GetPosition().x, posY = mesh.gameObject->transform.GetPosition().y, posZ = mesh.gameObject->transform.GetPosition().z;
					ImGui::SliderFloat("X ", &posX, SliderTransformMin, SliderTransformMax, "%.1f");
					ImGui::SliderFloat("Y ", &posY, SliderTransformMin, SliderTransformMax, "%.1f");
					ImGui::SliderFloat("Z ", &posZ, SliderTransformMin, SliderTransformMax, "%.1f");
					// set the transform if the sliders have moved
					mesh.gameObject->transform.SetPosition(glm::vec3(posX, posY, posZ));
					if (ImGui::TreeNodeEx((void*)(intptr_t)ptr_id, node_flags, "Material")) {
						ImGui::Text("Shader: %s", mesh.GetMaterial().GetShader().shaderName.c_str());
						ImGui::Text("Texture: %s", mesh.GetMaterial().GetTextureName().c_str());
						ImGui::TreePop();
					}
					ImGui::TreePop();
				}
				++ptr_id;
			}
		}
		for (auto& lightobject : scene->GetLights()) {
			Miasma::Component::PointLight& light = lightobject->GetComponent<PointLight>();
			if (&light != nullptr) {
				if (ImGui::TreeNodeEx((void*)(intptr_t)ptr_id, node_flags, lightobject->tag.c_str())) {
					// light position
					ImGui::Text("Pos: X: %.1f | Y: %.1f | Z: %.1f", light.GetLightPosition().x, light.GetLightPosition().y, light.GetLightPosition().z);
					float posX = light.GetLightPosition().x, posY = light.GetLightPosition().y, posZ = light.GetLightPosition().z;
					ImGui::SliderFloat("X ", &posX, SliderTransformMin, SliderTransformMax, "%.1f");
					ImGui::SliderFloat("Y ", &posY, SliderTransformMin, SliderTransformMax, "%.1f");
					ImGui::SliderFloat("Z ", &posZ, SliderTransformMin, SliderTransformMax, "%.1f");
					light.SetLightPosition(posX, posY, posZ);
					// light color
					ImGui::Text("Light Color: R: %.1f | G: %.1f | B: %.1f", light.GetLightColor().x, light.GetLightColor().y, light.GetLightColor().z);
					float colorR = light.GetLightColor().x, colorG = light.GetLightColor().y, colorB = light.GetLightColor().z;
					ImGui::SliderFloat("R ", &colorR, SliderColorMin, SliderColorMax, "%.1f");
					ImGui::SliderFloat("G ", &colorG, SliderColorMin, SliderColorMax, "%.1f");
					ImGui::SliderFloat("B ", &colorB, SliderColorMin, SliderColorMax, "%.1f");
					light.SetLightColor(colorR, colorG, colorB);
					// light strength
					ImGui::Text("Light Strength: %.1f", light.GetLightStrength());
					float lightStrength = light.GetLightStrength();
					ImGui::SliderFloat("S ", &lightStrength, 0, SliderLightStrength, "%.1f");
					light.SetLightStrength(lightStrength);
					ImGui::TreePop();
				}
				++ptr_id;
			}
		}
		ImGui::TreePop();
	}
	ImGui::End();
}

void GUIBuilder::gbShowImGuiDemoWindow()
{
	ImGui::ShowDemoWindow();
}