
#pragma once
#include "Gameobject.h"

class CGift :public CGameObject
{
public:
	CGift(int id);
	CGift(int x, int y, int id);
	~CGift(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + Gift_WIDTH, m_ptPos.y + Gift_HEIGHT));
	}

	int GetID()const
	{
		return ID;
	}
private:
	static CImageList m_Images;
	//ËÙ¶È
	int m_Vx;
	int m_Vy;
	int ID;
};


