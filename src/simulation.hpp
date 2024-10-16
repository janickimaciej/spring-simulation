#pragma once

#include <glm/glm.hpp>

#include <chrono>
#include <functional>
#include <vector>

class Simulation
{
	using Callback = std::function<void(float, float)>;

public:
	Simulation(const Callback& setWeightAndEquilibriumPosCallback);
	void update();
	void stop();
	void start();

private:
	Callback m_setWeightAndEquilibriumPosCallback{};
	bool m_running = false;

	float m_m = 1;
	float m_c = 1;
	float m_k = 0.1f;
	float m_x0 = 0;
	float m_xt0 = 0;
	float m_dt = 0.01f;

	std::chrono::time_point<std::chrono::system_clock> m_t0{};
	std::vector<glm::vec2> m_states{};

	float getTime() const;
	float getW(float t) const;
	float getH(float t) const;
	glm::vec2 rhs(const glm::vec2& state, float t) const;
};
