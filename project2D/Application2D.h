#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Audio.h"
#include "SpaceCar.h"
#include "Obstacle.h"
#include <list>

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	bool CheckCollision();
	bool IsCollided();
	void GameUpdate(float deltaTime);
	virtual void draw();

	void SpawnObstacle();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Texture*		m_texture;
	aie::Texture*		m_CarTexture;
	aie::Texture*		m_ObstacleTexture;
	aie::Font*			m_font;
	aie::Audio*			m_audio;

	std::list<Obstacle*> m_ObstacleList;

	float m_fCarX;
	float m_fCarY;
	float m_fCarR;
	float m_fSpeed;
	float m_fAccel;
	bool m_bFacingNorth;
	bool m_bFacingEast;
	bool m_bFacingSouth;
	SpaceCar *Plane;
	Obstacle *Debri;
	float m_cameraX, m_cameraY;
	float m_timer;
};