#include "SpaceCar.h"
#include "Input.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>


SpaceCar::SpaceCar()
{

	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;

	m_bFacingNorth = true;
	m_bFacingEast = false;
	m_bFacingSouth = false;

	m_fCarX = 0;
	m_fCarY = 0;
	m_fCarR = 0;
	m_fSpeed = 0;
	m_fAccel = m_fSpeed + 5;
	m_audio = new aie::Audio("./audio/powerup.wav");
	m_CarTexture = new aie::Texture ("./textures/Car.png");
	m_iRoundsWons = 0;

	glm::vec2 m_v2TopLeft;
	glm::vec2 m_v2BtmRight;


}

SpaceCar::~SpaceCar()
{

}

bool SpaceCar::Update(float dt)
{
	if(this->GetCarX() >= 2000 || this->GetCarX() <= -2000 ||this->GetCarY() >= 2000 || this->GetCarY() <= -2000)
	{
		this->SetX();
		this->SetY();
		this->SetTextureRed();
		this->m_iRoundsWons = m_iRoundsWons + 1;
		return true;
	}
	

	aie::Input* input = aie::Input::getInstance();


	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE) == true)
	{
		m_fCarR += glm::pi<float>() * 0.5f;
		if (m_bFacingNorth)
		{
			m_bFacingNorth = !m_bFacingNorth;
			m_bFacingEast = !m_bFacingEast;
		}
		else if (m_bFacingEast)
		{
			m_bFacingEast = !m_bFacingEast;
			m_bFacingSouth = !m_bFacingSouth;
		}
		else if (m_bFacingSouth)
		{
			m_bFacingSouth = !m_bFacingSouth;
		}
		else
		{
			m_bFacingNorth = true;
			m_bFacingEast = false;
			m_bFacingSouth = false;
		}
	}

	if (m_bFacingNorth)
	{
		m_fCarY = m_fCarY += m_fSpeed;
	}

	if (m_bFacingEast)
	{
		m_fCarX = m_fCarX -= m_fSpeed;
	}

	if (m_bFacingSouth)
	{
		m_fCarY = m_fCarY -= m_fSpeed;
	}

	if (!m_bFacingNorth && !m_bFacingEast && !m_bFacingSouth)
	{
		m_fCarX = m_fCarX += m_fSpeed;
	}


	m_fSpeed += m_fAccel * dt;
	
	

	// example of audio
	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
	{
		m_audio->play();
		m_fSpeed = m_fSpeed * 0.8f;
	}

	m_TopLeft.x = m_fCarX - 18;
	m_TopLeft.y = m_fCarY + 18;
	m_BtmRight.x = m_fCarX + 18;
	m_BtmRight.y = m_fCarY - 18;
	return false;
}

float SpaceCar::GetCarX()
{
	return m_fCarX;
}

float SpaceCar::GetCarY()
{
	return m_fCarY;
}

float SpaceCar::GetCarR()
{
	return m_fCarR;
}

float SpaceCar::GetSpeed()
{
	return m_fSpeed;
}

float SpaceCar::GetAccel()
{
	return m_fAccel;
}

bool SpaceCar::GetFacingNorth()
{
	return m_bFacingNorth;
}

bool SpaceCar::GetFacingEast()
{
	return m_bFacingEast;
}

bool SpaceCar::GetFacingSouth()
{
	return m_bFacingSouth;
}

int SpaceCar::GetRoundsWon()
{
	return m_iRoundsWons;
}

aie::Texture* SpaceCar::GetTexture()
{
	return m_CarTexture;
}

void SpaceCar::SetSpeed(float a)
{
	m_fSpeed = a;
}

void SpaceCar::SetTextureExplosion()
{
	m_CarTexture->load("./textures/explosion.png");
}

void SpaceCar::SetTextureRed()
{
	m_CarTexture->load("./textures/RedCar.png");
}

void SpaceCar::SetX()
{
	m_fCarX = 0;
		
}

void SpaceCar::SetY()
{
	m_fCarY = 0;
}
