#include "StdAfx.h"
#include "Boss.h"
#include "resource.h"


CImageList CBoss::m_Images;

CBoss::CBoss(void)
{
	//设置Boss出现的位置
	m_ptPos.x = GAME_HEIGHT/2;
	m_ptPos.y = GAME_WIDTH / 2;

	m_Vx = rand() % 6 + 2;
	m_Vy = rand() % 4 + 2;

	m_nWait = 0;
	life = 500;
}

CBoss::~CBoss(void)
{
}
BOOL CBoss::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BOSS, RGB(0, 0, 0), BOSS_WIDTH, BOSS_HEIGHT, 1);
}
BOOL CBoss::Draw(CDC* pDC, BOOL bPause)
{
	//确定Boss的移动轨迹
	m_nWait++;
	if (m_nWait>30)
		m_nWait = 0;

	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_Vy;
		m_ptPos.x = m_ptPos.x + m_Vx;
	}

	if (m_ptPos.y >= GAME_HEIGHT / 4)
	{
		m_Vy = -(rand() % 4 + 2);
	}
	if (m_ptPos.y <= -BOSS_HEIGHT / 2)
	{
		m_Vy = rand() % 3 + 2;
	}
	if (m_ptPos.x >= GAME_WIDTH - BOSS_WIDTH)
	{
		m_Vx = -(rand() % 4 + 2);
	}
	if (m_ptPos.x <= 0)
	{
		m_Vx = rand() % 4 + 2;
	}
	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}
BOOL CBoss::Fired()
{
	if (m_nWait == 0)
		return TRUE;
	else
		return FALSE;
}

