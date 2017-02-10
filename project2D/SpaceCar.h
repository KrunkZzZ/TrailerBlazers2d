#pragma once
#include "Application.h"
#include "Audio.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class SpaceCar
{
protected:
		int m_iRoundsWons;
		float m_fCarX;
		float m_fCarY;
		float m_fCarR;
		float m_fSpeed;
		float m_fAccel;
		bool m_bFacingNorth;
		bool m_bFacingEast;
		bool m_bFacingSouth;

		float m_cameraX, m_cameraY;
		float m_timer;
		aie::Audio	*m_audio;
		aie::Texture *m_CarTexture;
		aie::Texture *m_CarExplosion;
		aie::Texture *m_CarRed;


public:
	SpaceCar();
	~SpaceCar();
	bool Update(float);


	float GetCarX();
	float GetCarY();
	float GetCarR();
	float GetSpeed();
	float GetAccel();
	bool  GetFacingNorth();
	bool  GetFacingEast();
	bool  GetFacingSouth();
	int GetRoundsWon();
	aie::Texture* GetTexture();
	void SetSpeed(float a);
	void SetTextureExplosion();
	void SetTextureRed();
	void SetX();
	void SetY();

	glm::vec2 m_TopLeft;
	glm::vec2 m_BtmRight;
	//float GetCameraX();
	//float GetCameraY();
	//float GetTimer();
};