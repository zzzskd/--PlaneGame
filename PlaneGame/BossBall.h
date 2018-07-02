#pragma once
#include "GameObject.h"

class CBossBall :public CGameObject
{
public:
	CBossBall(int x, int y);
	~CBossBall(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + BOSSBALL_WIDTH, m_ptPos.y + BOSSBALL_HEIGHT));
	}
	void SetPos(int y)
	{

			m_ptPos.y = y + CIRCLE_HEIGHT;
	}
public:
	int GetDamageValue()const
	{
		return 15;
	}
private:
	static CImageList m_Images;
};




