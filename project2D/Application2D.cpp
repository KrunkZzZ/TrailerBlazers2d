#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>


Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	m_texture = new aie::Texture("./textures/numbered_grid.tga");
	m_shipTexture = new aie::Texture("./textures/ship.png");

	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_audio = new aie::Audio("./audio/powerup.wav");

	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;
	
	m_bFacingNorth = true;
	m_bFacingEast = false;
	m_bFacingSouth = false;

	m_fShipX = 500;
	m_fShipY = 250;
	m_fShipR = 0;
	m_fSpeed = 0;
	m_fAccel = m_fSpeed + 5;
	//getWindowHeight;
	//getWindowWidth;
	return true;
}

void Application2D::shutdown() {
	
	delete m_audio;
	delete m_font;
	delete m_texture;
	delete m_shipTexture;
	delete m_2dRenderer;
}

void Application2D::update(float deltaTime) {

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();


	// use arrow keys to move ship
	if (input->isKeyDown(aie::INPUT_KEY_UP))
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
	}

	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE) == true)
	{
		m_fShipR += glm::pi<float>() * 0.5;
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
		m_fShipY = m_fShipY += m_fSpeed;
	}

	if (m_bFacingEast)
	{
		m_fShipX = m_fShipX -= m_fSpeed;
	}

	if (m_bFacingSouth)
	{
		m_fShipY = m_fShipY -= m_fSpeed;
	}

	if (!m_bFacingNorth && !m_bFacingEast && !m_bFacingSouth)
	{
		m_fShipX = m_fShipX += m_fSpeed;
	}

	m_cameraY = m_fShipY - (getWindowHeight() * 0.5f);
	m_cameraX = m_fShipX - (getWindowWidth() * 0.5f);
	m_fSpeed += m_fAccel * deltaTime;
	
	// example of audio
	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
		m_audio->play();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);

	// begin drawing sprites
	m_2dRenderer->begin();

	// demonstrate animation   // A1 box changes text and colour (unneccessary)
	m_2dRenderer->setUVRect(int(m_timer) % 8 / 8.0f, 0, 1.f / 8, 1.f / 8);
	m_2dRenderer->drawSprite(m_texture, 200, 200, 100, 100);

	// demonstrate spinning sprite
	m_2dRenderer->setUVRect(0,0,1,1);
	m_2dRenderer->drawSprite(m_shipTexture, m_fShipX, m_fShipY, 0, 0, m_fShipR, 1);

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
	sprintf_s(windowHeight, "WindowHeight: %i", getWindowWidth());

	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, windowHeight , 0, 720 - 64);
	//winheight = 720
	//winwidth 1280
	// done drawing sprites
	m_2dRenderer->end();
}