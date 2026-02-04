#pragma once

#include "mesh.hpp"
#include "shaderProgram.hpp"

#include <glm/glm.hpp>

class Model
{
public:
	virtual void render() const = 0;
	void setPos(const glm::vec3& pos);
	void setYaw(float yawRad);
	void setPitch(float pitchRad);
	void setRoll(float rollRad);
	void setScale(const glm::vec3& scale);

protected:
	glm::mat4 getMatrix() const;

private:
	static constexpr float m_size = 0.48f;

	glm::mat4 m_modelMatrix{1};

	glm::vec3 m_pos{};
	float m_yawRad = 0;
	float m_pitchRad = 0;
	float m_rollRad = 0;
	glm::vec3 m_scale{1, 1, 1};

	void updateMatrix();
};
