#include "scene.hpp"

#include "mesh.hpp"
#include "vertex.hpp"

#include <glad/glad.h>

static constexpr float nearPlane = 0.1f;
static constexpr float farPlane = 1000.0f;
static constexpr float initFOVYDeg = 60.0f;

static constexpr glm::vec3 boxColor = {0, 0.5f, 1.0f};

static constexpr float ceilingThickness = 0.2f;
static constexpr float ceilingSize = 3;
static constexpr float springFreeLength = 5;
static constexpr float springThickness = 0.1f;
static constexpr float weightSize = 1;

Scene::Scene(const glm::ivec2& viewportSize) :
	m_camera{viewportSize, nearPlane, farPlane, initFOVYDeg},
	m_ceiling{boxColor},
	m_spring{boxColor},
	m_weight{boxColor},
	m_simulation
	{
		[this] (float weightPos, float equilibriumPos)
		{
			setWeightAndEquilibriumPos(weightPos, equilibriumPos);
		}
	}
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);

	m_ceiling.setScale({ceilingSize, ceilingThickness, ceilingSize});
	m_weight.setScale({weightSize, weightSize, weightSize});

	setWeightAndEquilibriumPos(0, 0);
}

void Scene::update()
{
	m_simulation.update();
}

void Scene::render() const
{
	static constexpr glm::vec3 backgroundColor{0.1f, 0.1f, 0.1f};
	glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_camera.use();
	m_ceiling.render();
	m_spring.render();
	m_weight.render();
}

void Scene::addPitchCamera(float pitchRad)
{
	m_camera.addPitch(pitchRad);
}

void Scene::addYawCamera(float yawRad)
{
	m_camera.addYaw(yawRad);
}

void Scene::moveXCamera(float x)
{
	m_camera.moveX(x);
}

void Scene::moveYCamera(float y)
{
	m_camera.moveY(y);
}

void Scene::zoomCamera(float zoom)
{
	m_camera.zoom(zoom);
}

Simulation& Scene::getSimulation()
{
	return m_simulation;
}

void Scene::setWeightAndEquilibriumPos(float weightPos, float equilibriumPos)
{
	float springLength = springFreeLength - weightPos + equilibriumPos;

	m_spring.setScale({springThickness, springLength, springThickness});

	m_ceiling.setPos({0, weightPos + weightSize / 2 + springLength + ceilingThickness / 2, 0});
	m_spring.setPos({0, weightPos + weightSize / 2 + springLength / 2, 0});
	m_weight.setPos({0, weightPos, 0});
}
