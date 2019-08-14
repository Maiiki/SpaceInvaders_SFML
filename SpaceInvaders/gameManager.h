#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "gameObject.h"
#include "alienShip.h"
#include "bullet.h"

class gameManager
{
public:
	gameManager(std::size_t windowWidth, std::size_t windowHeight, std::size_t horizantalALiens);
	~gameManager();
	void GameLoop();
	void UpdateGame();
	void RenderGame(sf::RenderWindow* win);
	void ResetGame();
	void CreateAliens();

	void CreatePlayerBullet();
	void UpdatePlayerBullets();
	void CheckPlayerHit();

	void CreateAlienBullet();
	void UpdateAlienBullets();
	void CheckAlienBorders();
	void CheckAlienHit();

	void IncreaseSpeed();
	//void ChangeEnemiesDirection();

private:
	std::size_t
		m_winW, m_winH,
		m_PlayerMaxBullets, m_AlienMaxBullets, m_FrameCount, m_FrameRate,
		m_HorAlien, m_VerAlien, m_AlienGapX, m_AlienGapY, m_AlienWidth, m_AlienHeight,
		m_PlayerWidth, m_PlayerHeight,
		m_BulletWidth, m_BulletHeight,
		m_GroundHeight;
	bool m_isBullet, m_isGoingRight;
	float m_Acceleration, m_PlayerSpeed;
	std::vector<std::vector<alienShip*>> m_Aliens;
	std::vector<bullet*> m_PlayerBullets;
	std::vector<bullet*> m_AlienBullets;
	sf::RenderWindow* m_PtWin;
	sf::RectangleShape m_Ground;
	sf::RectangleShape m_Player;
	sf::RectangleShape m_PlayerBullet;
};

