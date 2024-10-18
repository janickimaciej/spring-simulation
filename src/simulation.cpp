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
	int iterations = static_cast<int>(t / m_dt);

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
	if (m_running)
	{
		return;
	}

	m_states.clear();
	m_states.push_back({m_x0, m_v0});
	m_t0 = std::chrono::system_clock::now();
	m_running = true;
}

float Simulation::getDT() const
{
	return m_dt;
}

void Simulation::setDT(float dt)
{
	m_dt = dt;
}

float Simulation::getM() const
{
	return m_m;
}

void Simulation::setM(float m)
{
	m_m = m;
}

float Simulation::getC() const
{
	return m_c;
}

void Simulation::setC(float c)
{
	m_c = c;
}

float Simulation::getK() const
{
	return m_k;
}

void Simulation::setK(float k)
{
	m_k = k;
}

float Simulation::getX0() const
{
	return m_x0;
}

void Simulation::setX0(float x0)
{
	m_x0 = x0;
}

float Simulation::getV0() const
{
	return m_v0;
}

void Simulation::setV0(float v0)
{
	m_v0 = v0;
}

Simulation::FunctionType Simulation::getWFunctionType() const
{
	return m_wFunctionType;
}

void Simulation::setWFunctionType(FunctionType type)
{
	m_wFunctionType = type;
}

float Simulation::getWA() const
{
	return m_wA;
}

void Simulation::setWA(float a)
{
	m_wA = a;
}

float Simulation::getWOmega() const
{
	return m_wOmega;
}

void Simulation::setWOmega(float omega)
{
	m_wOmega = omega;
}

float Simulation::getWPhi() const
{
	return m_wPhi;
}

void Simulation::setWPhi(float phi)
{
	m_wPhi = phi;
}

float Simulation::getWT0() const
{
	return m_wT0;
}

void Simulation::setWT0(float t0)
{
	m_wT0 = t0;
}

Simulation::FunctionType Simulation::getHFunctionType() const
{
	return m_hFunctionType;
}

void Simulation::setHFunctionType(FunctionType type)
{
	m_hFunctionType = type;
}

float Simulation::getHA() const
{
	return m_hA;
}

void Simulation::setHA(float a)
{
	m_hA = a;
}

float Simulation::getHOmega() const
{
	return m_hOmega;
}

void Simulation::setHOmega(float omega)
{
	m_hOmega = omega;
}

float Simulation::getHPhi() const
{
	return m_hPhi;
}

void Simulation::setHPhi(float phi)
{
	m_hPhi = phi;
}

float Simulation::getHT0() const
{
	return m_hT0;
}

void Simulation::setHT0(float t0)
{
	m_hT0 = t0;
}

float Simulation::getTime() const
{
	std::chrono::time_point<std::chrono::system_clock> t = std::chrono::system_clock::now();
	std::chrono::duration<float> deltaT = t - m_t0;
	return deltaT.count();
}

float Simulation::getW(float t) const
{
	switch (m_wFunctionType)
	{
		case FunctionType::none:
			return 0;

		case FunctionType::constant:
			return m_wA;

		case FunctionType::step:
			return t >= m_wT0 ? m_wA : 0;

		case FunctionType::stepPeriodic:
			return m_wA * (std::sin(m_wOmega * t + m_wPhi) >= 0 ? 1 : -1);

		case FunctionType::sinus:
			return m_wA * std::sin(m_wOmega * t + m_wPhi);
	}
	return {};
}

float Simulation::getH(float t) const
{
	switch (m_hFunctionType)
	{
		case FunctionType::none:
			return 0;

		case FunctionType::constant:
			return m_hA;

		case FunctionType::step:
			return t >= m_hT0 ? m_hA : 0;

		case FunctionType::stepPeriodic:
			return m_hA * (std::sin(m_hOmega * t + m_hPhi) >= 0 ? 1 : -1);

		case FunctionType::sinus:
			return m_hA * std::sin(m_hOmega * t + m_hPhi);
	}
	return {};
}

glm::vec2 Simulation::rhs(const glm::vec2& state, float t) const
{
	return
		{
			state.y,
			(m_c * (getW(t) - state.x) - m_k * state.y + getH(t)) / m_m
		};
}
