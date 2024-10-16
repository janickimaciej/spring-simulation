#pragma once

#include <functional>

class Simulation
{
	using Callback = std::function<void(float)>;

public:
	Simulation(const Callback& setPositionCallback);
	void update();

private:
	Callback m_setPositionCallback{};
};
