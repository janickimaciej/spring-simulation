#include "guis/equilibriumPlot.hpp"

#include <imgui/imgui.h>
#include <implot/implot.h>

EquilibriumPlot::EquilibriumPlot(Simulation& simulation, const glm::vec2& pos,
	const glm::vec2& size) :
	m_simulation{simulation},
	m_pos{pos},
	m_size{size}
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
		ImPlot::SetupAxes("", "", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);
		ImPlot::PlotLine("x", m_simulation.getTVector(), m_simulation.getXVector(),
			m_simulation.getIterations());
		ImPlot::PlotLine("w", m_simulation.getTVector(), m_simulation.getWVector(),
			m_simulation.getIterations());
		ImPlot::EndPlot();
	}

	ImGui::End();
}
