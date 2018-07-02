#pragma once
#include "Gameobject.h"

class CBomb :
	public CGameObject
{
public:
	CBomb(int x, int y, int id);
	~CBomb(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + BOMB_WIDTH, m_ptPos.y + BOMB_HEIGHT));
	}
public:
	int GetDamageValue()const
	{
		if (ID <= 1)
			return 5;
		else
			return 10;
	}
private:
	static CImageList m_Images;
	int ID;

};
