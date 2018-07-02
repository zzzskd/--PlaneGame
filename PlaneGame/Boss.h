#pragma once
#include "GameObject.h"
//#include "PlaneGameView.h"

class CBoss :public CGameObject
{
public:
	CBoss(void);
	~CBoss(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + BOSS_WIDTH, m_ptPos.y + BOSS_HEIGHT));
	}
	//�Ƿ���Կ������ӵ�
	BOOL Fired();
public:
	void LossLife()
	{
		life -= 1;
		if (life < 0)
			life = 0;
	}
	void SetLife()
	{
		life = 100;
	}
	int GetLife()const
	{
		return life;
	}
private:
	static CImageList m_Images;
	//ͼ������
	int m_nImgIndex;
	//�ٶ�
	int m_Vy;
	int m_Vx;
	int    m_nWait;//������ʱ
	int life;
};