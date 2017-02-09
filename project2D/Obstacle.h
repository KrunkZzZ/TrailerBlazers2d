#pragma once
#include "Application.h"
#include "Audio.h"
#include "Texture.h"
#include <stack>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Obstacle
{
protected:
	aie::Texture *m_ObstacleTexture;

public:
	Obstacle();
	~Obstacle();

	void Update(float);

	glm::vec3 m_position;

	void SetPosition(const glm::vec3& pos);
	glm::vec3 GetPosition() { return m_position; }

	aie::Texture* GetTexture();

	glm::vec2 m_v2TopLeft;
	glm::vec2 m_v2BtmRight;

};