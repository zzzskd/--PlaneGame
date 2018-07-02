#include "stdafx.h"
#include "SurperMe.h"
#include "resource.h"
CImageList CSurperMe::m_Images;
CSurperMe::CSurperMe(void)
{
}
CSurperMe::CSurperMe(int ptx, int pty)
{
	m_ptPos.x = ptx;
	m_ptPos.y = pty;
}
CSurperMe::~CSurperMe(void)
{
}
BOOL CSurperMe::Fired()
{
	if (m_nWait == 0)
		return TRUE;
	else
		return FALSE;

}
void CSurperMe::UpdatePos(int x, int y)
{
	m_ptPos.x = x;
	m_ptPos.y = y;
}
BOOL CSurperMe::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_SURPERME, RGB(0, 0, 0), 71, 46, 1);
}
BOOL CSurperMe::Draw(CDC* pDC, BOOL bPause)
{
	m_nWait++;
	if (m_nWait>10)
		m_nWait = 0;
	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}