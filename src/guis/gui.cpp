#include "guis/gui.hpp"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <implot/implot.h>

GUI::GUI(GLFWwindow* window, Scene& scene) :
	m_scene{scene},
	m_controlPanel{scene.getSimulation(), {0, 0}, {360, 640}, m_autofitPlots},
	m_stateTrajectoryPlot{scene.getSimulation(), {0, 640}, {360, 360}, m_autofitPlots},
	m_statePlot{scene.getSimulation(), {360, 0}, {840, 333}, m_autofitPlots},
	m_forcesPlot{scene.getSimulation(), {360, 333}, {840, 333}, m_autofitPlots},
	m_equilibriumPlot{scene.getSimulation(), {360, 666}, {840, 334}, m_autofitPlots}
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImPlot::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
}

GUI::~GUI()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImPlot::DestroyContext();
	ImGui::DestroyContext();
}

void GUI::update()
{
	ImGui_ImplGlfw_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

	m_controlPanel.update();
	m_stateTrajectoryPlot.update();
	m_statePlot.update();
	m_forcesPlot.update();
	m_equilibriumPlot.update();
}

void GUI::render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
