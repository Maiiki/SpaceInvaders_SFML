#include "gameManager.h"

gameManager::gameManager(std::size_t windowWidth, std::size_t windowHeight, std::size_t horizantalALiens)
{
	m_PtWin = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "Space Invaders!", sf::Style::None);
	m_winH = windowHeight;
	m_winW = windowWidth;
	m_HorAlien = horizantalALiens;
	m_VerAlien = m_HorAlien;
	m_GroundHeight = m_winH / 10;

	m_AlienWidth = (m_winW / m_HorAlien) / 3;
	m_AlienHeight = m_AlienWidth;
	m_AlienGapX = m_AlienWidth;
	m_AlienGapY = m_AlienHeight/2;
	m_AlienMaxBullets = 10;

	m_PlayerWidth = 20;
	m_PlayerHeight = 20;
	m_PlayerSpeed = 1;
	m_PlayerMaxBullets = 1;

	m_BulletWidth = m_PlayerWidth / 10;
	m_BulletHeight = m_PlayerHeight / 2;

	
	m_FrameCount = 0;
	m_FrameRate = 100;
	m_Acceleration = 1;

	m_isBullet = false;
	m_isGoingRight = true;
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
	srand(time(NULL));
	//Frame = loop
	//Framerate = loops x segundo
	//Delta Time = Tiempo transcurrido entre loops
	CreateAliens();
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
				m_Player.move(-m_PlayerSpeed, 0.0f);
			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			if (m_Player.getPosition().x <= m_winW-m_PlayerWidth) {
				m_Player.move(m_PlayerSpeed, 0.0f);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
 			if (m_PlayerBullets.size()<m_PlayerMaxBullets)
			{
				CreatePlayerBullet();
			}
		}
		
		m_PtWin->clear();
		UpdateGame();
		RenderGame(m_PtWin);
		m_PtWin->display();
		//if (m_FrameCount < m_FrameRate) { m_FrameCount++; }
		m_FrameCount++;
	}
}

void gameManager::UpdateGame()
{
	if (m_FrameCount == m_FrameRate)
	{
		CheckAlienBorders();
		for (size_t i = 0; i < m_Aliens.size(); ++i)
		{
			for (size_t j = 0; j < m_Aliens[i].size(); j++)
			{
				m_Aliens[i][j]->Update();
			}
		}
		m_FrameCount = 0;
	}

	if (m_AlienBullets.size() < m_AlienMaxBullets)
	{
		CreateAlienBullet();
	}

	UpdatePlayerBullets();
	UpdateAlienBullets();
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

	for (size_t i = 0; i < m_PlayerBullets.size(); i++)
	{
		m_PlayerBullets[i]->Render(win);
	}

	for (size_t i = 0; i < m_AlienBullets.size(); i++)
	{
		m_AlienBullets[i]->Render(win);
	}

	win->draw(m_Ground);
	win->draw(m_Player);
}

void gameManager::ResetGame()
{

}

void gameManager::CreateAliens()
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

void gameManager::CreatePlayerBullet()
{
	bullet* newBullet = new bullet(m_Player.getPosition().x + ((m_PlayerWidth / 2) - m_BulletWidth / 2), 
		m_Player.getPosition().y, m_BulletWidth, m_BulletHeight, -1);
	m_PlayerBullets.push_back(newBullet);
}

void gameManager::UpdatePlayerBullets()
{
	for (size_t i = 0; i < m_PlayerBullets.size(); i++)
	{
		if (m_PlayerBullets[i]->GiveCollider()->top > 0)
		{
			CheckAlienHit();
		}
		else
		{
			m_PlayerBullets.erase(m_PlayerBullets.begin() + i);
		}
	}

	for (size_t i = 0; i < m_PlayerBullets.size(); i++)
	{
		if (!m_PlayerBullets[i]->GiveState())
		{
			m_PlayerBullets.erase(m_PlayerBullets.begin() + i);
		}
	}

	for (size_t i = 0; i < m_PlayerBullets.size(); i++)
	{
		m_PlayerBullets[i]->Update();
	}
}

void gameManager::CheckPlayerHit()
{
	for (size_t i = 0; i < m_AlienBullets.size(); i++)
	{
		if (m_AlienBullets[i]->GiveCollider()->left<m_Player.getPosition().x + m_PlayerWidth
			&& m_AlienBullets[i]->GiveCollider()->left + m_BulletWidth > m_Player.getPosition().x
			&& m_AlienBullets[i]->GiveCollider()->top<m_Player.getPosition().y + m_PlayerHeight
			&& m_AlienBullets[i]->GiveCollider()->top + m_BulletHeight > m_Player.getPosition().y)
		{
			m_AlienBullets[i]->Destroy();
		}
	}
}

void gameManager::CreateAlienBullet()
{
	int x = rand() % m_HorAlien;
	int y = rand() % m_VerAlien;
	bullet* newBullet = new bullet(m_Aliens[x][y]->GiveCollider().left+m_AlienWidth/2 -m_BulletWidth/2,
		m_Aliens[x][y]->GiveCollider().top+m_AlienHeight,m_BulletWidth, m_BulletHeight, .1f);
	m_AlienBullets.push_back(newBullet);
}

void gameManager::UpdateAlienBullets()
{
	for (size_t i = 0; i < m_AlienBullets.size(); i++)
	{
		if (m_AlienBullets[i]->GiveCollider()->top < m_winH - m_GroundHeight)
		{
			CheckPlayerHit();
		}
		else
		{
			m_AlienBullets.erase(m_AlienBullets.begin() + i);
		}
	}

	for (size_t i = 0; i < m_AlienBullets.size(); i++)
	{
		if (!m_AlienBullets[i]->GiveState())
		{
			m_AlienBullets.erase(m_AlienBullets.begin() + i);
		}
	}

	for (size_t i = 0; i < m_AlienBullets.size(); i++)
	{
		m_AlienBullets[i]->Update();
	}
}

void gameManager::CheckAlienBorders()
{
	if (m_isGoingRight)
	{
		if (m_Aliens[m_HorAlien - 1][m_VerAlien - 1]->GiveCollider().left + m_AlienWidth >= (m_winW - (m_AlienWidth * 3)))
		{
			for (size_t i = 0; i < m_Aliens.size(); ++i)
			{
				for (size_t j = 0; j < m_Aliens[i].size(); j++)
				{
					m_Aliens[i][j]->ChangeDirection();
				}
			}
			m_isGoingRight = false;
		}
	}
	else
	{
		if (m_Aliens[0][0]->GiveCollider().left - m_AlienWidth <= (m_AlienWidth * 2))
		{
			for (size_t i = 0; i < m_Aliens.size(); ++i)
			{
				for (size_t j = 0; j < m_Aliens[i].size(); j++)
				{
					m_Aliens[i][j]->ChangeDirection();
				}
			}
			m_isGoingRight = true;
		}
	}
	
}

void gameManager::CheckAlienHit()
{
	for (size_t k = 0; k < m_PlayerBullets.size(); k++)
	{
		for (size_t i = 0; i < m_Aliens.size(); ++i)
		{
			for (size_t j = 0; j < m_Aliens[i].size(); j++)
			{
				if (m_Aliens[i][j]->GiveState())
				{
					if ((m_Aliens[i][j]->GiveCollider().top
						< m_PlayerBullets[k]->GiveCollider()->top + m_BulletHeight) //m_PlayerBullet.getPosition().y + m_BulletHeight)
						&&
						(m_Aliens[i][j]->GiveCollider().top + m_AlienHeight
						> m_PlayerBullets[k]->GiveCollider()->top)//m_PlayerBullet.getPosition().y)
						&&
						(m_Aliens[i][j]->GiveCollider().left
							< m_PlayerBullets[k]->GiveCollider()->left + m_BulletWidth)//m_PlayerBullet.getPosition().x + m_BulletWidth)
						&&
						(m_Aliens[i][j]->GiveCollider().left + m_AlienWidth
							> m_PlayerBullets[k]->GiveCollider()->left))
					{

						m_Aliens[i][j]->Destroy();
						m_PlayerBullets[k]->Destroy();
						//IncreaseSpeed();
					}
				}
			}
		}
	}

	//for (size_t i = 0; i < m_Aliens.size(); ++i)
	//{
	//	for (size_t j = 0; j < m_Aliens[i].size(); j++)
	//	{
	//		for (size_t k = 0; k < m_PlayerBullets.size(); k++)
	//		{
	//			if (m_Aliens[i][j]->GiveState())
	//			{
	//				if ((m_Aliens[i][j]->GiveCollider().top
	//					< m_PlayerBullets[k]->GiveCollider()->top + m_BulletHeight) //m_PlayerBullet.getPosition().y + m_BulletHeight)
	//					&&
	//					(m_Aliens[i][j]->GiveCollider().top + m_AlienHeight
	//					> m_PlayerBullets[k]->GiveCollider()->top)//m_PlayerBullet.getPosition().y)
	//					&&
	//					(m_Aliens[i][j]->GiveCollider().left
	//						< m_PlayerBullets[k]->GiveCollider()->left + m_BulletWidth)//m_PlayerBullet.getPosition().x + m_BulletWidth)
	//					&&
	//					(m_Aliens[i][j]->GiveCollider().left + m_AlienWidth
	//						> m_PlayerBullets[k]->GiveCollider()->left))
	//				{

	//					m_Aliens[i][j]->Destroy();
	//					m_PlayerBullets[k]->Destroy();
	//				}
	//			}
	//			
	//		}
	//		
	//	}
	//}
}

void gameManager::IncreaseSpeed()
{
	/*m_FrameRate -= 1;*/
	for (size_t i = 0; i < m_Aliens.size(); ++i)
	{
		for (size_t j = 0; j < m_Aliens[i].size(); j++)
		{
			m_Aliens[i][j]->ChangeSpeed(m_Acceleration);
		}
	}
}

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