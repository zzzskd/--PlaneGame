#include "stdafx.h"
#include "Gift.h"
#include "resource.h"

CImageList CGift::m_Images;


CGift::CGift(int id) : ID(id)
{
	//随机确定X位置
	m_ptPos.x = rand() % (GAME_WIDTH - Gift_HEIGHT) + 1;
	m_ptPos.y = -Gift_HEIGHT + 1;
	m_Vy = rand() % 3 + 2;
	m_Vx = rand() % 3 - 5;
}

CGift::CGift(int x, int y, int id) : CGameObject(x, y), ID(id)
{
	m_Vy = rand() % 6 - 2;
	m_Vx = rand() % 6 - 1;
	if (m_Vx == 0)
		m_Vx = 2;
	if (m_Vy == 0)
		m_Vy = 2;
}
CGift::~CGift(void)
{
}
BOOL CGift::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_GIFT, RGB(0, 0, 0), 75, 52, 4);
}
BOOL CGift::Draw(CDC* pDC, BOOL bPause)
{
	if (m_ptPos.y > GAME_HEIGHT )
		return FALSE;
	if (m_ptPos.y < -Gift_HEIGHT)
		return FALSE;
	if (m_ptPos.x > GAME_WIDTH + 3)
	{
		//有一定几率反弹；
		if (rand() % 3 == 0)
		{
			m_Vx = -m_Vx;
		}
		else
			return FALSE;
	}
	if (m_ptPos.x < -3)
	{
		if (rand() % 3 == 0)
		{
			m_Vx = -m_Vx;
		}
		else
			return FALSE;
	}
	m_ptPos.x += m_Vx;
	m_ptPos.y += m_Vy;
	m_Images.Draw(pDC, ID, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}