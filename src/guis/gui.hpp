#pragma once

#include "scene.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

class GUI
{
public:
	GUI(GLFWwindow* window, Scene& scene, const glm::ivec2& windowSize);
	~GUI();

	void update();
	void render();

private:
	Scene& m_scene;
};
