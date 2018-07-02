#include "stdafx.h"
#include "Circle.h"
#include "resource.h"
#include "PlaneGameDoc.h"
CImageList CCircle::m_Images;
CCircle::CCircle(int x, int y) :CGameObject(x, y), time(0)
{

}

CCircle::~CCircle(void)
{
}
BOOL CCircle::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_CIRCLE, RGB(0, 0, 0), 227, 248, 1);
}
BOOL CCircle::Draw(CDC* pDC, BOOL bPause)
{
	//m_ptPos.x = x;
	//m_ptPos.y = y;
	  time++;
	if (time > 100)
	{
		return FALSE;
	}

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}