#pragma once

#include "box.hpp"
#include "cameras/perspectiveCamera.hpp"
#include "shaderProgram.hpp"
#include "simulation.hpp"

#include <glm/glm.hpp>

class Scene
{
public:
	Scene(const glm::ivec2& windowSize);
	void update();
	void render() const;
	void updateWindowSize();

	void addPitchCamera(float pitchRad);
	void addYawCamera(float yawRad);
	void moveXCamera(float x);
	void moveYCamera(float y);
	void zoomCamera(float zoom);

private:
	ShaderProgram m_shaderProgram{"src/shaders/VS.glsl", "src/shaders/FS.glsl"};
	const glm::ivec2& m_windowSize{};
	PerspectiveCamera m_camera;

	Box m_ceiling;
	Box m_spring;
	Box m_weight;

	Simulation m_simulation;

	void setAspectRatio(float aspectRatio);
	void setWeightAndEquilibriumPos(float weightPos, float equilibriumPos);
};
