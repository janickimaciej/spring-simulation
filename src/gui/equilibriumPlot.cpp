#include "gui/equilibriumPlot.hpp"

#include <imgui/imgui.h>
#include <implot/implot.h>

EquilibriumPlot::EquilibriumPlot(Simulation& simulation, const glm::vec2& pos,
	const glm::vec2& size, const bool& autoFitPlots) :
	m_simulation{simulation},
	m_pos{pos},
	m_size{size},
	m_autoFitPlots{autoFitPlots}
{ }

void EquilibriumPlot::update()
{
	static constexpr int offset = 17;

	ImGui::SetNextWindowPos({m_pos.x, m_pos.y}, ImGuiCond_Always);
	ImGui::SetNextWindowSize({m_size.x, m_size.y}, ImGuiCond_Always);
	ImGui::Begin("equilibriumPlot", nullptr,
		ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

	if (ImPlot::BeginPlot("Equilibrium", {m_size.x - offset, m_size.y - offset}))
	{
		ImPlot::SetupAxes("", "", m_autoFitPlots ? ImPlotAxisFlags_AutoFit : 0,
			m_autoFitPlots ? ImPlotAxisFlags_AutoFit : 0);
		ImPlot::PlotLine("x", m_simulation.getTVector(), m_simulation.getXVector(),
			m_simulation.getIterations());
		ImPlot::PlotLine("w", m_simulation.getTVector(), m_simulation.getWVector(),
			m_simulation.getIterations());
		ImPlot::PlotLine("w - x", m_simulation.getTVector(), m_simulation.getWMinusXVector(),
			m_simulation.getIterations());
		ImPlot::EndPlot();
	}

	ImGui::End();
}
