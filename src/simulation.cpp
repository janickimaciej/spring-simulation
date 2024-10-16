#include "simulation.hpp"

#include <cmath>

Simulation::Simulation(const Callback& setWeightAndEquilibriumPosCallback) :
	m_setWeightAndEquilibriumPosCallback{setWeightAndEquilibriumPosCallback}
{ }

void Simulation::update()
{
	if (!m_running)
	{
		return;
	}

	float t = getTime();
	int iterations = t / m_dt;

	while (m_states.size() <= iterations)
	{
		glm::vec2 prevState = m_states.back();
		float prevT = (m_states.size() - 1) * m_dt;
		glm::vec2 state = prevState + m_dt * rhs(prevState, prevT);
		m_states.push_back(state);
	}

	m_setWeightAndEquilibriumPosCallback(m_states.back().x, getW(iterations * m_dt));
}

void Simulation::stop()
{
	m_running = false;
}

void Simulation::start()
{
	m_states.clear();
	m_states.push_back({m_x0, m_xt0});
	m_t0 = std::chrono::system_clock::now();
	m_running = true;
}

float Simulation::getTime() const
{
	std::chrono::time_point<std::chrono::system_clock> t = std::chrono::system_clock::now();
	std::chrono::duration<float> deltaT = t - m_t0;
	return deltaT.count();
}

float Simulation::getW(float t) const
{
	return 0.2f * std::sin(t);
}

float Simulation::getH(float t) const
{
	return 0;
}

glm::vec2 Simulation::rhs(const glm::vec2& state, float t) const
{
	return
		{
			state.y,
			(m_c * (getW(t) - state.x) - m_k * state.y + getH(t)) / m_m
		};
}
