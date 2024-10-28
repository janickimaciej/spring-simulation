#pragma once

#include "simulation.hpp"

#include <glm/glm.hpp>

class EquilibriumPlot
{
public:
	EquilibriumPlot(Simulation& simulation, const glm::vec2& pos, const glm::vec2& size,
		const bool& autoFitPlots);
	void update();

private:
	const Simulation& m_simulation;
	const glm::vec2 m_pos;
	const glm::vec2 m_size;
	const bool& m_autoFitPlots;
};
