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
bool GameIsRunning = true;

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

	
	for (int i = 0; i < 120; ++i)
	{
		SpawnObstacle();
	}
	
	

	float m_cameraX = 0;
	float m_cameraY = 0;
	float m_timer = 0;
	
	m_bFacingNorth = true;
	m_bFacingEast = false;
	m_bFacingSouth = false;

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
	delete Plane;
	delete m_ObstacleTexture;
}

void Application2D::update(float deltaTime) 
{
	
	aie::Input* input = aie::Input::getInstance();
	if (GameIsRunning == true)
	{
		m_timer += deltaTime;

		// input example
		

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


		if (Plane->Update(deltaTime) == true)
		{
			for (int i = 0; i < (Plane->GetRoundsWon() - 1) * 12 + 120; ++i)
			{
				delete m_ObstacleList.front();
				m_ObstacleList.pop_front();
			}
			for (int i = 0; i < (Plane->GetRoundsWon() * 12) + 120; ++i)
			{
				SpawnObstacle();
			}
		}


		IsCollided();

		m_cameraY = Plane->GetCarX() - (getWindowHeight() * 0.5f);
		m_cameraX = Plane->GetCarY() - (getWindowWidth() * 0.5f);

		// example of audio

	
		// exit the application
	
	}
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

bool Application2D::CheckCollision()
{
	for (auto it = m_ObstacleList.begin(); it != m_ObstacleList.end(); ++it)
	{
		Obstacle* obstacle = *it;
		if (Plane->m_BtmRight.x < obstacle->m_v2TopLeft.x)
			continue;
     	if (Plane->m_TopLeft.x > obstacle->m_v2BtmRight.x)
			continue;
 		if (Plane->m_BtmRight.y > obstacle->m_v2TopLeft.y)
			continue;
		if (Plane->m_TopLeft.y < obstacle->m_v2BtmRight.y)  
			continue;

		Plane->SetTextureExplosion();

 		return true;
	}
	return false;
}

bool Application2D::IsCollided()
{
	if (CheckCollision())
	{	
		//quit(); 
		std::cout << "collided";
		return true;

	}
	return false;
	
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
	if (GameIsRunning == true)
	{

		if (CheckCollision() == true)
		{

			char GameOver[32];
			sprintf_s(GameOver, 32, "GameOver, Levels Cleared: %i", Plane->GetRoundsWon());
			m_2dRenderer->drawText(m_font, GameOver, 0, 0, 0);
			Plane->SetX();
			Plane->SetY();
			
			char a;
			GameIsRunning = false;
			for (int i = 0; i < 120; ++i)
			{
				delete m_ObstacleList.front();
				m_ObstacleList.pop_front();
			}

		}
		else
		{

			for (auto i = m_ObstacleList.begin(); i != m_ObstacleList.end(); ++i)
			{
				Obstacle* obsticle = *i;
				m_2dRenderer->setUVRect(0, 0, 1, 1);
				m_2dRenderer->drawSprite(m_ObstacleTexture, obsticle->GetPosition().x, obsticle->GetPosition().y, 0, 0, 0, 1);
				//m_2dRenderer->setUVRect(0, 0, 1, 1);
				//m_2dRenderer->drawSprite(m_ObstacleTexture, Debri->GetObstacleX(), Debri->GetObstacleY(), 0, 0, 0, 1);
			}

			// demonstrate spinning sprite
			m_2dRenderer->setUVRect(0, 0, 1, 1);
			m_2dRenderer->drawSprite(Plane->GetTexture(), Plane->GetCarX(), Plane->GetCarY(), 0, 0, Plane->GetCarR(), 1);

			// draw a thin line
			m_2dRenderer->drawLine(-2000, -2000, -2000, 2000, 2, 1);
			m_2dRenderer->drawLine(-2000, 2000, 2000, 2000, 2, 1);
			m_2dRenderer->drawLine(2000, 2000, 2000, -2000, 2, 1);
			m_2dRenderer->drawLine(2000, -2000, -2000, -2000, 2, 1);

			// output some text, uses the last used colour
			char fps[32];
			sprintf_s(fps, 32, "FPS: %i", getFPS());

			char LevelsCleared[32];
			sprintf_s(LevelsCleared, 32, "LevelsCleared: %i", Plane->GetRoundsWon());

			char windowHeight[128];
			//	sprintf_s(windowHeight, "Speed: %i", Plane->GetSpeed());

			m_2dRenderer->drawText(m_font, LevelsCleared, 50, 50 - 32);

			//winheight = 720
			//winwidth 1280
			// done drawing sprites

		}
	}
	else 
	{
		char GameOver[32];
		sprintf_s(GameOver, 32, "GameOver, Levels Cleared: %i", Plane->GetRoundsWon());
		m_2dRenderer->drawText(m_font, GameOver, 0, 0, 0);
		m_2dRenderer->drawSprite(Plane->GetTexture(), Plane->GetCarX(), Plane->GetCarY(), 0, 0, Plane->GetCarR(), 1);
	}
		m_2dRenderer->end();
	
}

void Application2D::SpawnObstacle()
{
	auto Debri = new Obstacle();

	static std::random_device rd;
	static std::mt19937 mt(rd());
	std::uniform_real_distribution<float> widthDist(-1999, 1999);
	std::uniform_real_distribution<float> heightDist(-1999, 1999);
	
	



	Debri->SetPosition(glm::vec3(widthDist(mt), heightDist(mt), -0.05f));
	while (Debri->GetPosition().x >= -350 && Debri->GetPosition().x <= 350 && Debri->GetPosition().y >= -350 && Debri->GetPosition().y <= 350)
	{
		std::uniform_real_distribution<float> widthDist(-1999, 1999);
		std::uniform_real_distribution<float> heightDist(-1999, 1999);
		Debri->SetPosition(glm::vec3(widthDist(mt), heightDist(mt), -0.05f));
	}
	m_ObstacleList.push_back(Debri);
}

