#pragma once
#include "GameObject.h"

class CBall :public CGameObject
{
public:
	CBall(int x, int y, int id);
	~CBall(void);
	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + BALL_WIDTH, m_ptPos.y + BALL_HEIGHT));

	}
public:
	int GetID()const
	{
		return ID;
	}
	int GetDamageValue()const
	{
		return DamageValue;
	}
	void SetPos(int y)
	{
		if (ID % 2 == 0)
		{
			m_ptPos.y = y - ENEMY_HEIGHT;
		}
		else
			m_ptPos.y = y + CIRCLE_HEIGHT;
	}
private:
	static CImageList m_Images;
	int ID;
	int DamageValue;
};
