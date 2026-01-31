#pragma once

#include "gui/controlPanel.hpp"
#include "gui/equilibriumPlot.hpp"
#include "gui/forcesPlot.hpp"
#include "gui/statePlot.hpp"
#include "gui/stateTrajectoryPlot.hpp"
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
	ControlPanel m_controlPanel;
	StateTrajectoryPlot m_stateTrajectoryPlot;
	StatePlot m_statePlot;
	ForcesPlot m_forcesPlot;
	EquilibriumPlot m_equilibriumPlot;

	bool m_autofitPlots = true;
};
