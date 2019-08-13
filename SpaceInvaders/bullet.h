#pragma once
#include "gameObject.h"
class bullet :
	public gameObject
{
public:
	bullet(int positionX, int positionY, int width, int height);
	~bullet();
	virtual void Update();
	virtual void Render(sf::RenderWindow* win);
	sf::IntRect* GiveCollider();

private:
	sf::RectangleShape m_Hitbox;
};

