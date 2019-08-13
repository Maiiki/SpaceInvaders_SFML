#include "alienShip.h"

alienShip::alienShip(int windowWidth, int windowHeight, int positionX, int positionY, int width, int height, int points)
{
	m_winW = windowWidth;
	m_winH = windowHeight;
	m_PosX = positionX;
	m_PosY = positionY;
	m_Height = height;
	m_Width = width;
	m_StepCount = 0;
	m_Speed = 9; // 
	m_MaxSteps = 25;
	m_Direction = 1;
	m_Points = points;
	m_isActive = true;
	m_Body.setSize(sf::Vector2f(m_Width, m_Height));
	m_Body.setPosition(sf::Vector2f((float)m_PosX, (float)m_PosY));
}

alienShip::~alienShip()
{

}

void alienShip::ChangeSpeed(float acceleration)
{
	m_Speed += acceleration;
	m_MaxSteps = (450 / m_Speed);
}

void alienShip::ChangeDirection()
{
	m_Direction *= -1;
}

void alienShip::ChangeColor(sf::Color color)
{
	m_Body.setFillColor(color);
}

bool alienShip::GiveState()
{
	return m_isActive;
}

void alienShip::Destroy()
{
	ChangeColor(sf::Color::Black);
	m_isActive = false;
}

sf::IntRect alienShip::GiveCollider()
{
	return sf::IntRect(m_PosX, m_PosY, m_Width, m_Height);
}

void alienShip::Update()
{
	if (m_StepCount < m_MaxSteps)
	{
		m_PosX += (m_Speed * m_Direction);
		m_Body.setPosition(sf::Vector2f((float)m_PosX, (float)m_PosY));
		m_StepCount++;
	}
	else
	{
		m_PosY += (m_Speed * 2);
		ChangeDirection();
		m_Body.setPosition(sf::Vector2f((float)m_PosX, (float)m_PosY));
		m_StepCount = 0;
	}
	
}

void alienShip::Render(sf::RenderWindow* win)
{
	win->draw(m_Body);
}