#include "StdAfx.h"
#include "Enemy.h"
#include "resource.h"

CImageList CEnemy::m_Images;

CEnemy::CEnemy(int id) :ID(id)
{
	//随机确定X位置
	m_ptPos.x = rand() % (GAME_WIDTH - ENEMY_HEIGHT) + 1;
	if (ID % 2 == 0)
	{
		m_ptPos.y = GAME_HEIGHT - 10;
		//随机确定速度
		m_Vy = rand() % 5 - 5;
	}
	else
	{
		m_ptPos.y = -ENEMY_HEIGHT + 10;
		m_Vy = rand() % 6 + 2;
	}
	m_Vx = rand() % 3 - 4;
	m_nWait = 0;
}
CEnemy::CEnemy(int x, int y, int id)
{
	m_ptPos.x = x;
	m_ptPos.y = y;
	ID = id;
	if (ID % 2 == 0)
	{
		//随机确定速度
		m_Vy = -rand() % 6 + 2;
	}
	else
	{
		m_Vy = rand() % 6 + 2;
	}
	m_Vx = rand() % 3 - 5;
	m_nWait = 0;

}
CEnemy::~CEnemy(void)
{
}
BOOL CEnemy::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_ENEMY, RGB(0, 0, 0), 141, 113, 3);
}
BOOL CEnemy::Draw(CDC* pDC, BOOL bPause)
{
	m_nWait++;
	if (m_nWait>50)
		m_nWait = 0;

	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_Vy;
		m_ptPos.x = m_ptPos.x + m_Vx;
	}

	if (m_ptPos.y > GAME_HEIGHT + ENEMY_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -ENEMY_HEIGHT - ENEMY_HEIGHT)
		return FALSE;
	if (m_ptPos.x >= GAME_WIDTH + ENEMY_WIDTH)
	{
		//有一定几率反弹；
		if (rand() % 2 == 0)
		{
			m_Vx = -m_Vx;
		}
		else
			return FALSE;
	}
	if (m_ptPos.x <= -ENEMY_WIDTH)
	{
		if (rand() % 2 == 0)
		{
			m_Vx = -m_Vx;
		}
		else
			return FALSE;
	}

	m_Images.Draw(pDC, ID, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}
BOOL CEnemy::Fired()
{
	if (m_nWait == 0)
		return TRUE;
	else
		return FALSE;
}