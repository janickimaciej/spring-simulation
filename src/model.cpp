#include "model.hpp"

void Model::setPosition(const glm::vec3& position)
{
	m_position = position;
	updateMatrix();
}

void Model::setYaw(float yawRad)
{
	m_yawRad = yawRad;
	updateMatrix();
}

void Model::setPitch(float pitchRad)
{
	m_pitchRad = pitchRad;
	updateMatrix();
}

void Model::setRoll(float rollRad)
{
	m_rollRad = rollRad;
	updateMatrix();
}

void Model::setScale(const glm::vec3& scale)
{
	m_scale = scale;
	updateMatrix();
}

glm::mat4 Model::getMatrix() const
{
	return m_modelMatrix;
}

void Model::updateMatrix()
{
	glm::mat4 scaleMatrix
	{
		m_scale.x, 0, 0, 0,
		0, m_scale.y, 0, 0,
		0, 0, m_scale.z, 0,
		0, 0, 0, 1
	};

	glm::mat4 rotationYawMatrix
	{
		cos(m_yawRad), 0, -sin(m_yawRad), 0,
		0, 1, 0, 0,
		sin(m_yawRad), 0, cos(m_yawRad), 0,
		0, 0, 0, 1
	};

	glm::mat4 rotationPitchMatrix
	{
		1, 0, 0, 0,
		0, cos(m_pitchRad), sin(m_pitchRad), 0,
		0, -sin(m_pitchRad), cos(m_pitchRad), 0,
		0, 0, 0, 1
	};

	glm::mat4 rotationRollMatrix
	{
		cos(m_rollRad), sin(m_rollRad), 0, 0,
		-sin(m_rollRad), cos(m_rollRad), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	glm::mat4 positionMatrix
		{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			m_position.x, m_position.y, m_position.z, 1
		};

	m_modelMatrix =
		positionMatrix * rotationRollMatrix * rotationYawMatrix * rotationPitchMatrix * scaleMatrix;
}
