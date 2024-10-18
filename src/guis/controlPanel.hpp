#pragma once

#include "simulation.hpp"

#include <glm/glm.hpp>

#include <functional>
#include <optional>
#include <string>

class ControlPanel
{
public:
	ControlPanel(Simulation& simulation, const glm::ivec2& windowSize);
	void update();

private:
	Simulation& m_simulation;
	const glm::ivec2& m_windowSize;

	void updateValue(const std::function<float()>& get, const std::function<void(float)>& set,
		const std::string& name, std::optional<float> min = std::nullopt);
	void separator();
};
