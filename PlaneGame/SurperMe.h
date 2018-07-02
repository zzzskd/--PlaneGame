#pragma once
#include "GameObject.h"


class CSurperMe :public CGameObject
{
public:
	CSurperMe(void);
	CSurperMe(int ptx, int pty);
	~CSurperMe(void);
public:
	BOOL Draw(CDC* pDC, BOOL bPause);
	static BOOL LoadImage();
public:
	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + SurperMyPlane_WIDTH, m_ptPos.y + SurperMyPlane_HEIGHT));
	}
	void UpdatePos(int x, int y);
public:
	//�Ƿ���Կ����䵼��
	BOOL Fired();
public:
	static const int SurperMyPlane_WIDTH = 71;//zzz�޸� ������Ҫ��С
	static const int SurperMyPlane_HEIGHT = 46;
public:
	void SetPos(int ptx, int pty)
	{
		m_ptPos.x = ptx;
		m_ptPos.y = pty;
	}
private:
	static CImageList m_Images;
	int    m_nWait;//������ʱ
};
