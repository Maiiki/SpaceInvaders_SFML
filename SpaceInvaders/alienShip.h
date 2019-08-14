#pragma once
#include "gameObject.h"

class alienShip :
	public gameObject
{
public:
	alienShip(int windowWidth, int windowHeight,int positionX, int positionY, int width, int height, int points);
	~alienShip();
	void ChangeSpeed(float acceleration);
	void ChangeDirection();
	void ChangeColor(sf::Color color);
	bool GiveState();
	void Destroy();
	sf::IntRect GiveCollider();
	virtual void Update();
	virtual void Render(sf::RenderWindow* win);

private:
	int m_Points, m_Direction, m_StepCount, m_MaxSteps, m_winW, m_winH;
	bool m_isGoingDown;
	sf::RectangleShape m_Body;
};

