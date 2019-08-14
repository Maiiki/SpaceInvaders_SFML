#pragma once
#include "gameObject.h"
class bullet :
	public gameObject
{
public:
	bullet(int positionX, int positionY, int width, int height, float direction);
	~bullet();
	virtual void Update();
	virtual void Render(sf::RenderWindow* win);
	void Destroy();
	bool GiveState();
	sf::IntRect* GiveCollider();

private:
	sf::RectangleShape m_Hitbox;
	float m_dir;
};

