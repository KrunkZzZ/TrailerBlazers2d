#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "SpaceCar.h"
#include "Obstacle.h"
#include <random>
#include <iostream>

Application2D::Application2D() 
{

}

Application2D::~Application2D() 
{

}

bool Application2D::startup() 
{
	
	m_2dRenderer = new aie::Renderer2D();

	m_texture = new aie::Texture("./textures/numbered_grid.tga");
	m_CarTexture = new aie::Texture("./textures/Car.png");
	m_ObstacleTexture = new aie::Texture("./textures/rock_small.png");
	m_audio = new aie::Audio("./audio/powerup.wav");
	m_font = new aie::Font("./font/consolas.ttf", 32);

	Plane = new SpaceCar();
	//Debri = new Obstacle();
	for (int i = 0; i < 20; ++i)
	{
		SpawnObstacle();
	}
	
	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;
	
	m_bFacingNorth = true;
	m_bFacingEast = false;
	m_bFacingSouth = false;

	m_fCarX = 500;
	m_fCarY = 250;
	m_fCarR = 0;
	m_fSpeed = 0;
	m_fAccel = m_fSpeed + 5;
	//getWindowHeight;
	//getWindowWidth;
	return true;
}

void Application2D::shutdown() 
{
	
	delete m_audio;
	delete m_font;
	delete m_texture;
	delete m_CarTexture;
	delete m_2dRenderer;
}

void Application2D::update(float deltaTime) 
{

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();


	// use arrow keys to move ship
	/*if (input->isKeyDown(aie::INPUT_KEY_UP))
	{
		m_fShipY += 500.0f * deltaTime;
		m_fShipR = 0;
	}

	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
	{
		m_fShipY -= 500.0f * deltaTime;
		m_fShipR = glm::pi<float>();
	}

	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
	{
		m_fShipX -= 500.0f * deltaTime;
		m_fShipR = glm::pi<float>() * 0.5;
	}


	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
	{
		m_fShipX += 500.0f * deltaTime;
		m_fShipR = glm::pi<float>() * 1.5;
	}*/
	

	Plane->Update(deltaTime);
	

	CheckCollision();
	IsCollided();

	m_cameraY = m_fCarY - (getWindowHeight() * 0.5f);
	m_cameraX = m_fCarX - (getWindowWidth() * 0.5f);

	// example of audio
	

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

bool Application2D::CheckCollision()
{
	for (auto it = m_ObstacleList.begin(); it != m_ObstacleList.end(); ++it)
	{
		Obstacle* obstacle = *it;
		if (obstacle->m_v2TopLeft.x > Plane->m_BtmRight.x) return false;
		if (obstacle->m_v2BtmRight.x < Plane->m_TopLeft.x) return false;
		if (obstacle->m_v2TopLeft.y < obstacle->m_v2BtmRight.y) return false;
		if (obstacle->m_v2BtmRight.y > obstacle->m_v2TopLeft.y) return false;

		return true;
	}
}

bool Application2D::IsCollided()
{
	if (CheckCollision())
	{	
		//quit(); 
		std::cout << "collided";
		return false;
	}
	
}

void Application2D::GameUpdate(float deltaTime)
{
	
}

void Application2D::draw() 
{

	// wipe the screen to the background colour
	clearScreen();

	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(Plane->GetCarX() - (getWindowWidth() * 0.5f), Plane->GetCarY() - (getWindowHeight() * 0.5f));

	// begin drawing sprites
	m_2dRenderer->begin();

	// demonstrate animation   // A1 box changes text and colour (unneccessary)
	m_2dRenderer->setUVRect(int(m_timer) % 8 / 8.0f, 0, 1.f / 8, 1.f / 8);
	m_2dRenderer->drawSprite(m_texture, 200, 200, 100, 100);
	
	for (auto i = m_ObstacleList.begin(); i != m_ObstacleList.end(); ++i)
	{
		Obstacle* obsticle = *i;
		m_2dRenderer->setUVRect(0, 0, 1, 1);
		m_2dRenderer->drawSprite(m_ObstacleTexture, obsticle->GetPosition().x, obsticle->GetPosition().y, 0, 0, 0, 1);
		//m_2dRenderer->setUVRect(0, 0, 1, 1);
		//m_2dRenderer->drawSprite(m_ObstacleTexture, Debri->GetObstacleX(), Debri->GetObstacleY(), 0, 0, 0, 1);
	}

	// demonstrate spinning sprite
	m_2dRenderer->setUVRect(0,0,1,1);
	m_2dRenderer->drawSprite(Plane->GetTexture(), Plane->GetCarX(), Plane->GetCarY(), 0, 0, Plane->GetCarR(), 1);

	// draw a thin line
	m_2dRenderer->drawLine(300, 300, 600, 400, 2, 1);

	// draw a moving purple circle
	m_2dRenderer->setRenderColour(1, 0, 1, 1);
	m_2dRenderer->drawCircle(sin(m_timer) * 100 + 600, 150, 50);

	// draw a rotating red rectangle
	m_2dRenderer->setRenderColour(1, 0, 0, 1);
	m_2dRenderer->drawBox(600, 500, 60, 20, m_timer);

	// draw a slightly rotated sprite with no texture, coloured yellow
	m_2dRenderer->setRenderColour(1, 1, 0, 1);
	m_2dRenderer->drawSprite(nullptr, 400, 400, 50, 50, 3.14159f * 0.25f, 1);
	int a = getWindowHeight();
	char b = a;
	
	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());

	char windowHeight[128];
//	sprintf_s(windowHeight, "Speed: %i", Plane->GetSpeed());

	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, windowHeight , 0, 720 - 64);
	//winheight = 720
	//winwidth 1280
	// done drawing sprites
	m_2dRenderer->end();
}

void Application2D::SpawnObstacle()
{
	auto Debri = new Obstacle();

	static std::random_device rd;
	static std::mt19937 mt(rd());
	std::uniform_real_distribution<float> widthDist(0.0f, (float)getWindowWidth());
	std::uniform_real_distribution<float> heightDist(0.0f, (float)getWindowHeight());
	
	Debri->SetPosition(glm::vec3(widthDist(mt), heightDist(mt), -0.05f));
	m_ObstacleList.push_back(Debri);
}

