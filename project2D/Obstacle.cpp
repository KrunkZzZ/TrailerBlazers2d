#include "Obstacle.h"
#include "Application.h"
#include "Audio.h"
#include "Texture.h"
#include <list>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

Obstacle::Obstacle()
{
	
	m_ObstacleTexture = new aie::Texture("./textures/rock_small.png");
}

Obstacle::~Obstacle()
{

}

void Obstacle::Update(float dt)
{
	
}

void Obstacle::SetPosition(const glm::vec3& pos)
{
	m_position = pos;
	m_v2TopLeft.x = (pos.x + 10);
	m_v2TopLeft.y = (pos.y + 10);
	m_v2BtmRight.x = (pos.x - 10);
	m_v2BtmRight.y = (pos.y - 10);
}

aie::Texture* Obstacle::GetTexture()
{
	return m_ObstacleTexture;
}