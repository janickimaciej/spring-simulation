#include "simulation.hpp"

#include <cmath>

Simulation::Simulation(const Callback& setXAndWCallback) :
	m_setXAndWCallback{setXAndWCallback}
{ }

void Simulation::update()
{
	if (!m_running)
	{
		return;
	}

	float frameT = getTime();
	int iterations = static_cast<int>(frameT / m_dt);

	while (m_t.size() <= iterations)
	{
		glm::vec2 prevState = {m_x.back(), m_v.back()};
		float prevT = (m_t.size() - 1) * m_dt;
		float t = prevT + m_dt;
		glm::vec2 state = prevState + m_dt * getRHS(prevState, prevT);

		m_t.push_back(t);
		m_x.push_back(state.x);
		m_v.push_back(state.y);
		m_a.push_back(getRHS(state, t).y);
		m_w.push_back(getW(t));
		m_f.push_back(getF(t, state.x));
		m_g.push_back(getG(state.y));
		m_h.push_back(getH(t));
	}

	m_setXAndWCallback(m_x.back(), getW(iterations * m_dt));
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

	m_t.clear();
	m_x.clear();
	m_v.clear();
	m_a.clear();
	m_w.clear();
	m_f.clear();
	m_g.clear();
	m_h.clear();

	glm::vec2 rhs = getRHS({m_x0, m_v0}, 0);

	m_t.push_back(0);
	m_x.push_back(m_x0);
	m_v.push_back(m_v0);
	m_a.push_back(rhs.y);
	m_w.push_back(getW(0));
	m_f.push_back(getF(0, m_x0));
	m_g.push_back(getG(m_v0));
	m_h.push_back(getH(0));

	resetTime();
	m_running = true;
}

float Simulation::getDT() const
{
	return m_dt;
}

void Simulation::setDT(float dt)
{
	if (m_running)
	{
		return;
	}

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
	if (m_running)
	{
		return;
	}

	m_x0 = x0;
}

float Simulation::getV0() const
{
	return m_v0;
}

void Simulation::setV0(float v0)
{
	if (m_running)
	{
		return;
	}

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

int Simulation::getIterations() const
{
	return static_cast<int>(m_t.size());
}

float Simulation::getT() const
{
	if (m_t.empty())
	{
		return 0;
	}
	return m_t.back();
}

const float* Simulation::getTVector() const
{
	return m_t.data();
}

const float* Simulation::getXVector() const
{
	return m_x.data();
}

const float* Simulation::getVVector() const
{
	return m_v.data();
}

const float* Simulation::getAVector() const
{
	return m_a.data();
}

const float* Simulation::getWVector() const
{
	return m_w.data();
}

const float* Simulation::getFVector() const
{
	return m_f.data();
}

const float* Simulation::getGVector() const
{
	return m_g.data();
}

const float* Simulation::getHVector() const
{
	return m_h.data();
}

float Simulation::getTime() const
{
	std::chrono::time_point<std::chrono::system_clock> t = std::chrono::system_clock::now();
	std::chrono::duration<float> deltaT = t - m_t0;
	return deltaT.count();
}

void Simulation::resetTime()
{
	m_t0 = std::chrono::system_clock::now();
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

float Simulation::getF(float t, float x) const
{
	return m_c * (getW(t) - x);
}

float Simulation::getG(float v) const
{
	return -m_k * v;
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

glm::vec2 Simulation::getRHS(const glm::vec2& state, float t) const
{
	return
		{
			state.y,
			(getF(t, state.x) + getG(state.y) + getH(t)) / m_m
		};
}
