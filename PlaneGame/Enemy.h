#pragma once
#include "Gameobject.h"

class CEnemy :public CGameObject
{
public:
	CEnemy(int id);
	CEnemy(int x, int y, int id);
	~CEnemy(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + ENEMY_WIDTH, m_ptPos.y + ENEMY_HEIGHT));
	}

	int GetID()const
	{
		return ID;
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
	//是否可以开火发射子弹
	BOOL Fired();
private:
	static CImageList m_Images;
	//速度
	int m_Vx;
	int m_Vy;
	int    m_nWait;//发射延时
	int ID;
};
