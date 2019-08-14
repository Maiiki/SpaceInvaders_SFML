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
	m_Speed = 1; //9 
	m_MaxSteps = 25;
	m_Direction = 1;
	m_Points = points;
	m_isActive = true;
	m_isGoingDown = false;
	m_Body.setSize(sf::Vector2f(m_Width, m_Height));
	m_Body.setPosition(sf::Vector2f((float)m_PosX, (float)m_PosY));
}

alienShip::~alienShip()
{

}

void alienShip::SetSpeed(float acceleration)
{
	m_Speed = acceleration;
}

void alienShip::ChangeDirection()
{
	m_Direction *= -1;
	m_isGoingDown = true;
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
	if (!m_isGoingDown) //Si no estoy bajando
	{
		m_PosX += (m_Speed * m_Direction);
		m_Body.setPosition(sf::Vector2f((float)m_PosX, (float)m_PosY));
	}
	else
	{
		m_PosY += (m_Height/2);
		m_Body.setPosition(sf::Vector2f((float)m_PosX, (float)m_PosY));
		m_isGoingDown = false;
	}
	
}

void alienShip::Render(sf::RenderWindow* win)
{
	win->draw(m_Body);
}