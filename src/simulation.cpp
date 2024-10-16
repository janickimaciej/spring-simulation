#include "simulation.hpp"

Simulation::Simulation(const std::function<void(float)>& setPositionCallback) :
	m_setPositionCallback{setPositionCallback}
{ }

void Simulation::update()
{
	// TODO
}
