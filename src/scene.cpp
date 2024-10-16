#include "scene.hpp"

#include "mesh.hpp"
#include "vertex.hpp"

#include <glad/glad.h>

static constexpr float fovYDeg = 60.0f;
static constexpr float nearPlane = 0.1f;
static constexpr float farPlane = 1000.0f;
static constexpr glm::vec3 boxColor = {0, 0.5f, 1.0f};

static constexpr float springFreeLength = 5;
static constexpr float springThickness = 0.1f;
static constexpr float weightSize = 1;

Scene::Scene(const glm::ivec2& windowSize) :
	m_windowSize{windowSize},
	m_camera{fovYDeg, static_cast<float>(windowSize.x) / windowSize.y, nearPlane, farPlane,
		m_shaderProgram},
	m_ceiling{m_shaderProgram, boxColor},
	m_spring{m_shaderProgram, boxColor},
	m_weight{m_shaderProgram, boxColor},
	m_simulation
	{
		[this] (float pos)
		{
			setWeightPos(pos);
		}
	}
{
	static constexpr float ceilingThickness = 0.2f;
	static constexpr float ceilingSize = 3;

	m_ceiling.setScale({ceilingSize, ceilingThickness, ceilingSize});
	m_weight.setScale({weightSize, weightSize, weightSize});

	m_ceiling.setPosition({0, weightSize / 2 + springFreeLength + ceilingThickness / 2, 0});

	setWeightPos(0);
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

void Scene::updateWindowSize()
{
	setAspectRatio(static_cast<float>(m_windowSize.x) / m_windowSize.y);
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

void Scene::setAspectRatio(float aspectRatio)
{
	m_camera.setAspectRatio(aspectRatio);
}

void Scene::setWeightPos(float pos)
{
	float springLength = springFreeLength - pos;

	m_spring.setScale({springThickness, springLength, springThickness});

	m_spring.setPosition({0, pos + weightSize / 2 + springLength / 2, 0});
	m_weight.setPosition({0, pos, 0});
}
