#include "StdAfx.h"
#include "BossBall.h"
#include "resource.h"

CImageList CBossBall::m_Images;

CBossBall::CBossBall(int x, int y) :CGameObject(x, y)
{

}

CBossBall::~CBossBall(void)
{
}
BOOL CBossBall::Draw(CDC* pDC, BOOL bPause)
{
	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + 8;
	}

	if (m_ptPos.y > GAME_HEIGHT + BOSSBALL_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -BOSSBALL_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}

BOOL CBossBall::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BOSSBALL, RGB(0, 0, 0), 25, 79, 1);
}



