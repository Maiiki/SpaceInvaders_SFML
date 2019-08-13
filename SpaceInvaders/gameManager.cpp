#include "gameManager.h"

gameManager::gameManager(std::size_t windowWidth, std::size_t windowHeight)
{
	m_PtWin = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "Space Invaders!", sf::Style::None);
	m_winH = windowHeight;
	m_winW = windowWidth;
	m_HorAlien = 6;
	m_VerAlien = 6;

	m_AlienWidth = m_winW / 20;
	m_AlienHeight = m_winH / 20;
	m_AlienGapX = m_AlienWidth - (m_AlienWidth / 8);
	m_AlienGapY = m_AlienHeight/2;

	m_PlayerWidth = m_AlienWidth / 3 * 2;
	m_PlayerHeight = m_AlienHeight;

	m_BulletWidth = m_PlayerWidth / 10;
	m_BulletHeight = m_PlayerHeight / 2;

	m_GroundHeight = m_AlienHeight;
	m_FrameCount = 0;
	m_Acceleration = 2;

	m_isBullet = false;
	m_PlayerBullet.setSize(sf::Vector2f(m_BulletWidth, m_BulletHeight));
	
	m_Ground.setPosition(0, m_winH - m_GroundHeight);
	m_Ground.setSize(sf::Vector2f(m_winW,m_winH));
	
	m_Player.setSize(sf::Vector2f(m_PlayerWidth, m_PlayerHeight));
	m_Player.setFillColor(sf::Color::Blue);
	m_Player.setPosition((m_winW / 2) - (m_PlayerWidth / 2), m_winH - m_GroundHeight - m_PlayerHeight);
	GameLoop();
}

gameManager::~gameManager() {};

void gameManager::GameLoop()
{
	//Frame = loop
	//Framerate = loops x segundo
	//Delta Time = Tiempo transcurrido entre loops
	CreateEnemies();
	while (m_PtWin->isOpen())
	{
		sf::Event event;
		while (m_PtWin->pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				m_PtWin->close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			if (m_Player.getPosition().x >= 0) {
				m_Player.move(-0.5f, 0.0f);
			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			if (m_Player.getPosition().x <= m_winW-m_PlayerWidth) {
				m_Player.move(0.5f, 0.0f);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			if (!m_isBullet)
			{
				m_PlayerBullet.setPosition(sf::Vector2f(
					m_Player.getPosition().x + ((m_PlayerWidth / 2) - m_BulletWidth / 2),
					m_Player.getPosition().y));
				m_isBullet = true;
			}
		}
		
		m_PtWin->clear();
		UpdateGame();
		RenderGame(m_PtWin);
		m_PtWin->display();
		m_FrameCount++;
	}
}

void gameManager::UpdateGame()
{
	if (m_FrameCount == 100)
	{
		for (size_t i = 0; i < m_Aliens.size(); ++i)
		{
			for (size_t j = 0; j < m_Aliens[i].size(); j++)
			{
				m_Aliens[i][j]->Update();
			}
		}
		m_FrameCount = 0;
	}

	if (m_isBullet)
	{
		if (m_PlayerBullet.getPosition().y > 0)
		{
			m_PlayerBullet.move(0.0f, -1);
			CheckHit();
		}
		else
		{
			m_isBullet = false;
		}
	}
}

void gameManager::RenderGame(sf::RenderWindow* win)
{
	for (size_t i = 0; i < m_Aliens.size(); ++i)
	{
		for (size_t j = 0; j < m_Aliens[i].size(); j++)
		{
			if (m_Aliens[i][j]->GiveState())
			{
				m_Aliens[i][j]->Render(win);
			}
		}
	}

	if (m_isBullet) {
		win->draw(m_PlayerBullet);
	}

	win->draw(m_Ground);
	win->draw(m_Player);
}

void gameManager::ResetGame()
{

}

void gameManager::CreateEnemies()
{
	for (size_t i = 0; i < m_HorAlien; ++i) {
		m_Aliens.push_back(std::vector<alienShip*>(m_VerAlien, 0));
		for (size_t j = 0; j < m_VerAlien; j++)
		{
			m_Aliens[i][j] = new alienShip (
				m_winW,m_winH,
				(m_AlienWidth*2) + ((m_AlienWidth + m_AlienGapX) * i), //Posición en X.
				(m_AlienHeight * 2) + ((m_AlienHeight + m_AlienGapY) * j), //Posición en Y.
				m_AlienWidth, m_AlienHeight, 5); // Ancho y Alto.
		}
	}
}

void gameManager::CheckHit()
{
	for (size_t i = 0; i < m_Aliens.size(); ++i)
	{
		for (size_t j = 0; j < m_Aliens[i].size(); j++)
		{
			if ((m_Aliens[i][j]->GiveCollider().top
				< m_PlayerBullet.getPosition().y + m_BulletHeight)
				&& 
				(m_Aliens[i][j]->GiveCollider().top + m_AlienHeight
				> m_PlayerBullet.getPosition().y)
				&&
				(m_Aliens[i][j]->GiveCollider().left
				< m_PlayerBullet.getPosition().x+m_BulletWidth)
				&&
				(m_Aliens[i][j]->GiveCollider().left + m_AlienWidth
				> m_PlayerBullet.getPosition().x)
				&& m_Aliens[i][j]->GiveState())
			{
				
				m_Aliens[i][j]->Destroy();
				m_isBullet = false;
			}
		}
	}
}

//void gameManager::IncreaseSpeed()
//{
//	for (size_t i = 0; i < m_Aliens.size(); ++i)
//	{
//		for (size_t j = 0; j < m_Aliens[i].size(); j++)
//		{
//			m_Aliens[i][j]->ChangeSpeed(m_Acceleration);
//		}
//	}
//}

//void gameManager::ChangeEnemiesDirection()
//{
//	for (size_t i = 0; i < m_Aliens.size(); ++i)
//	{
//		for (size_t j = 0; j < m_Aliens[i].size(); j++)
//		{
//			m_Aliens[i][j]->ChangeDirection();
//		}
//	}
//}