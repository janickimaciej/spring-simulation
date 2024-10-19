#include "guis/statePlot.hpp"

#include <imgui/imgui.h>
#include <implot/implot.h>

StatePlot::StatePlot(Simulation& simulation, const glm::vec2& pos, const glm::vec2& size) :
	m_simulation{simulation},
	m_pos{pos},
	m_size{size}
{ }

void StatePlot::update()
{
	static constexpr int offset = 17;

	ImGui::SetNextWindowPos({m_pos.x, m_pos.y}, ImGuiCond_Always);
	ImGui::SetNextWindowSize({m_size.x, m_size.y}, ImGuiCond_Always);
	ImGui::Begin("statePlot", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

	if (ImPlot::BeginPlot("State", {m_size.x - offset, m_size.y - offset}))
	{
		ImPlot::SetupAxes("", "", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);
		ImPlot::PlotLine("x", m_simulation.getTVector(), m_simulation.getXVector(),
			m_simulation.getIterations());
		ImPlot::PlotLine("v", m_simulation.getTVector(), m_simulation.getVVector(),
			m_simulation.getIterations());
		ImPlot::PlotLine("a", m_simulation.getTVector(), m_simulation.getAVector(),
			m_simulation.getIterations());
		ImPlot::EndPlot();
	}

	ImGui::End();
}
