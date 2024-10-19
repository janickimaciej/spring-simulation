#include "guis/forcesPlot.hpp"

#include <imgui/imgui.h>
#include <implot/implot.h>

ForcesPlot::ForcesPlot(Simulation& simulation, const glm::vec2& pos, const glm::vec2& size) :
	m_simulation{simulation},
	m_pos{pos},
	m_size{size}
{ }

void ForcesPlot::update()
{
	static constexpr int offset = 17;

	ImGui::SetNextWindowPos({m_pos.x, m_pos.y}, ImGuiCond_Always);
	ImGui::SetNextWindowSize({m_size.x, m_size.y}, ImGuiCond_Always);
	ImGui::Begin("forcesPlot", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

	if (ImPlot::BeginPlot("Forces", {m_size.x - offset, m_size.y - offset}))
	{
		ImPlot::SetupAxes("", "", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);
		ImPlot::PlotLine("f", m_simulation.getTVector(), m_simulation.getFVector(),
			m_simulation.getIterations());
		ImPlot::PlotLine("g", m_simulation.getTVector(), m_simulation.getGVector(),
			m_simulation.getIterations());
		ImPlot::PlotLine("h", m_simulation.getTVector(), m_simulation.getHVector(),
			m_simulation.getIterations());
		ImPlot::EndPlot();
	}

	ImGui::End();
}
