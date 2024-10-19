#pragma once

#include "simulation.hpp"

#include <glm/glm.hpp>

#include <functional>
#include <optional>
#include <string>

class ControlPanel
{
public:
	ControlPanel(Simulation& simulation, const glm::vec2& pos, const glm::vec2& size);
	void update();

private:
	Simulation& m_simulation;
	glm::vec2 m_pos;
	glm::vec2 m_size;

	void updateValue(const std::function<float()>& get, const std::function<void(float)>& set,
		const std::string& name, std::optional<float> min = std::nullopt);
	void separator();
};
