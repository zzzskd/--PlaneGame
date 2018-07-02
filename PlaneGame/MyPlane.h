#pragma once
#include "GameObject.h"

class CMyPlane :public CGameObject
{
public:
	CMyPlane(void);
	~CMyPlane(void);

	BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage();

	void SetHorMotion(int nMotion)
	{
		m_nHorMotion = nMotion;
	}
	int GetHorMotion() const
	{
		return m_nHorMotion;
	}

	void SetVerMotion(int nMotion)
	{
		m_nVerMotion = nMotion;
	}
	int GetVerMotion() const
	{
		return m_nVerMotion;
	}

	CRect GetRect()
	{
		return CRect(m_ptPos,CPoint(m_ptPos.x+PLANE_WIDTH,m_ptPos.y+PLANE_HEIGHT));
	}

	//�Ƿ���Կ����䵼��
	BOOL Fired();
public:
	int GetLife()const
	{
		return m_life;
	}
	void AddLife()
	{
		  m_life += 20;
		  if (m_life >= 100)
			  m_life = 100;
	}
	void LossLife()
	{
		m_life -= 5;
		if (m_life <= 0)
			m_life = 0;
	}
public:
	int GetMagic()const
	{
		return m_magic;
	}
	void AddMagic()
	{
		m_magic += 20;
		if (m_magic >= 100)
			m_magic = 100;
	}
	void LossMagic(int x)
	{
		m_magic -= x;
		if (m_magic <= 0)
			m_magic = 0;
	}
	void Recover()
	{
		m_life = 100;
		m_magic = 100;
	}
private:
	
	static CImageList m_Images;
	int    m_nHorMotion;//�ɻ�ˮƽ���з���0->��ֹ��1->�� -1->��
	int    m_nVerMotion;//�ɻ���ֱ���з���0->��ֹ��1->�� -1->��
	int    m_nWait;//������ʱ
	int    m_life;
	int    m_magic;
};
