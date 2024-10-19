#pragma once

#include "guis/controlPanel.hpp"
#include "guis/equilibriumPlot.hpp"
#include "guis/forcesPlot.hpp"
#include "guis/statePlot.hpp"
#include "guis/stateTrajectoryPlot.hpp"
#include "scene.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

class GUI
{
public:
	GUI(GLFWwindow* window, Scene& scene);
	~GUI();

	void update();
	void render();

private:
	Scene& m_scene;
	ControlPanel m_controlPanel;
	StateTrajectoryPlot m_stateTrajectoryPlot;
	StatePlot m_statePlot;
	ForcesPlot m_forcesPlot;
	EquilibriumPlot m_equilibriumPlot;
};
