#pragma once
#include <SFML/Graphics.hpp>

class gameObject
{
public:
	gameObject();
	~gameObject();
	virtual void Update() = 0;
	virtual void Render(sf::RenderWindow* win) = 0;

protected:
	int m_Width, m_Height, m_PosX, m_PosY, m_Speed;
	bool m_isActive;
};

