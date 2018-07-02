#include "StdAfx.h"
#include "Bomb.h"
#include "resource.h"
CImageList CBomb::m_Images;
CBomb::CBomb(int x, int y, int id) :CGameObject(x, y), ID(id)
{

}

CBomb::~CBomb(void)
{
}
BOOL CBomb::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BOMB, RGB(0, 0, 0), 28, 99, 4);
}
BOOL CBomb::Draw(CDC* pDC, BOOL bPause)
{
	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y - 8;
	}
	if (m_ptPos.y < -BOMB_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, ID, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}