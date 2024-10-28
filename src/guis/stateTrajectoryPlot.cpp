#include "guis/stateTrajectoryPlot.hpp"

#include <imgui/imgui.h>
#include <implot/implot.h>

StateTrajectoryPlot::StateTrajectoryPlot(Simulation& simulation, const glm::vec2& pos,
	const glm::vec2& size, const bool& autoFitPlots) :
	m_simulation{simulation},
	m_pos{pos},
	m_size{size},
	m_autoFitPlots{autoFitPlots}
{ }

void StateTrajectoryPlot::update()
{
	static constexpr int offset = 17;

	ImGui::SetNextWindowPos({m_pos.x, m_pos.y}, ImGuiCond_Always);
	ImGui::SetNextWindowSize({m_size.x, m_size.y}, ImGuiCond_Always);
	ImGui::Begin("stateTrajectoryPlot", nullptr,
		ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

	if (ImPlot::BeginPlot("State trajectory", {m_size.x - offset, m_size.y - offset},
		ImPlotFlags_Equal))
	{
		ImPlot::SetupAxes("x", "v", m_autoFitPlots ? ImPlotAxisFlags_AutoFit : 0,
			m_autoFitPlots ? ImPlotAxisFlags_AutoFit : 0);
		ImPlot::PlotLine("", m_simulation.getXVector(), m_simulation.getVVector(),
			m_simulation.getIterations());
		ImPlot::EndPlot();
	}

	ImGui::End();
}
