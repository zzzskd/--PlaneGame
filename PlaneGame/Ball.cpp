#include "StdAfx.h"
#include "Ball.h"
#include "resource.h"

CImageList CBall::m_Images;

CBall::CBall(int x, int y, int id): ID(id)
{
	if (ID <= 1)
		DamageValue = 5;
	else if (ID == 2 || ID == 3)
		DamageValue = 10;
	else
		DamageValue = 15;
	m_ptPos.x = x + ENEMY_WIDTH / 2 - BALL_WIDTH / 2;
	if (ID % 2 == 0)
	{
		m_ptPos.y = y - BALL_HEIGHT;
	}
	else
	{
		m_ptPos.y = y + ENEMY_HEIGHT;
	}
}

CBall::~CBall(void)
{
}
BOOL CBall::Draw(CDC* pDC, BOOL bPause)
{
	if (!bPause)
	{
		//如果id是偶数则是向上的
		if (ID % 2 == 0)
			m_ptPos.y = m_ptPos.y - 8;
		else
			m_ptPos.y = m_ptPos.y + 8;
	}

	if (m_ptPos.y > GAME_HEIGHT + BALL_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -BALL_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, ID, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}

BOOL CBall::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BALL, RGB(0, 0, 0), 28, 113, 6);
}