#pragma once

#include "box.hpp"
#include "camera/perspectiveCamera.hpp"
#include "simulation.hpp"

#include <glm/glm.hpp>

class Scene
{
public:
	Scene(const glm::ivec2& viewportSize);
	void update();
	void render() const;

	void addPitchCamera(float pitchRad);
	void addYawCamera(float yawRad);
	void moveXCamera(float x);
	void moveYCamera(float y);
	void zoomCamera(float zoom);

	Simulation& getSimulation();

private:
	PerspectiveCamera m_camera;

	Box m_ceiling;
	Box m_spring;
	Box m_weight;

	Simulation m_simulation;

	void setAspectRatio(float aspectRatio);
	void setWeightAndEquilibriumPos(float weightPos, float equilibriumPos);
};
