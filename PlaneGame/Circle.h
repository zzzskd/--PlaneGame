#pragma once
#include "Gameobject.h"

class CCircle :public CGameObject
{
public:
	CCircle(int x, int y);
	~CCircle(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + CIRCLE_WIDTH, m_ptPos.y + CIRCLE_HEIGHT));
	}
	void UpdateCirclePos(int x, int y)
	{
		m_ptPos.x = x;
		m_ptPos.y = y;
	}
private:
	//环的的图片列表
	static CImageList m_Images;
	int time;
};



