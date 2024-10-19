#pragma once

#include "simulation.hpp"

#include <glm/glm.hpp>

class StateTrajectoryPlot
{
public:
	StateTrajectoryPlot(Simulation& simulation, const glm::vec2& pos, const glm::vec2& size);
	void update();

private:
	const Simulation& m_simulation;
	glm::vec2 m_pos;
	glm::vec2 m_size;
};
