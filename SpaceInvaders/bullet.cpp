#include "bullet.h"

bullet::bullet(int positionX, int positionY, int width, int height, float direction)
{
	m_PosX = positionX;
	m_PosY = positionY;
	m_Width = width;
	m_Height = height;
	m_Speed = 10;
	m_dir = direction;
	m_isActive = true;
	m_Hitbox.setSize(sf::Vector2f(m_Width, m_Height));
	m_Hitbox.setPosition(sf::Vector2f((float)m_PosX, (float)m_PosY));
}

bullet::~bullet()
{

}

void bullet::Update()
{
	m_PosY += m_Speed * m_dir;
	m_Hitbox.setPosition(sf::Vector2f((float)m_PosX, (float)m_PosY));
}

void bullet::Render(sf::RenderWindow* win)
{
	win->draw(m_Hitbox);
}

void bullet::Destroy() {
	m_isActive = false;
}

bool bullet::GiveState()
{
	return m_isActive;
}

sf::IntRect* bullet::GiveCollider()
{
	return new sf::IntRect(m_PosX, m_PosY, m_Width, m_Height);
}