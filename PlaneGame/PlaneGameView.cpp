// PlaneGameView.cpp : CPlaneGameView ���ʵ��
//

#include "stdafx.h"
#include "PlaneGame.h"

#include "PlaneGameDoc.h"
#include "PlaneGameView.h"
#include "MyPlane.h"
#include "Enemy.h"
#include "Bomb.h"
#include "Ball.h"
#include "Explosion.h"
#include "Gift.h"
#include "Circle.h"
#include "Boss.h"
#include "BossBall.h"
#include "DrawLifeMagic.h"
#include <atlimage.h>
#include "DirectSound.h"
 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlaneGameView

IMPLEMENT_DYNCREATE(CPlaneGameView, CView)

BEGIN_MESSAGE_MAP(CPlaneGameView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()

END_MESSAGE_MAP()

// CPlaneGameView ����/����

CPlaneGameView::CPlaneGameView() :m_pMe(NULL),m_Circle(NULL), LifeMagic(NULL),score(0), isPause(0), invincible(0)
{
	// TODO: �ڴ˴���ӹ������
	
}

CPlaneGameView::~CPlaneGameView()
{
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CPlaneGameView ����

void CPlaneGameView::OnDraw(CDC* /*pDC*/)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CPlaneGameView ��ӡ

BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CPlaneGameView ���

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneGameView ��Ϣ�������
void CPlaneGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: �ڴ����ר�ô����/����û���
	//��ʼ����Ϸ
	InitGame();
}
void CPlaneGameView::StopGame()
{
	delete m_pMe;
	delete m_pMemDC;
	delete m_pDC;
	delete m_pMemBitmap;
	delete LifeMagic;
}

BOOL CPlaneGameView::InitGame()
{
	CRect rc;
	GetClientRect(rc);

	VERIFY(soundback.Create(IDR_SOUND));

	//�������������
	srand( (unsigned)time( NULL ) );

	//�����豸DC
	m_pDC = new CClientDC(this);

	//�����ڴ�DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);

	//�����ڴ�λͼ
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC,GAME_WIDTH,GAME_HEIGHT);

	//��λͼѡ���ڴ�DC
	m_pMemDC->SelectObject(m_pMemBitmap);

	CMyPlane::LoadImage();
	CEnemy::LoadImage();
	CBomb::LoadImage();
	CBall::LoadImage();
	CExplosion::LoadImage();
	CGift::LoadImage();
	CCircle::LoadImage();
	CBoss::LoadImage();
	CBossBall::LoadImage();

	//��������(ս��)
	m_pMe = new CMyPlane;
	LifeMagic = new CDrawLifeMagic;
	//������Ϸ
	SetTimer(1,30,NULL);
	soundback.Play();
	return TRUE;
}

void CPlaneGameView::UpdateFrame(CDC* pMemDC)
{
	//�������
	if (m_pMe == NULL)
	{
		for (int i = 0; i < 6; i++)
		{
			m_ObjList[i].RemoveAll();
		}
		CBitmap bitmap;// ����λͼ����
		bitmap.LoadBitmapW(IDB_INTRODUCTION);
		CBrush brush;
		brush.CreatePatternBrush(&bitmap);
		CBrush* pOldBrush = pMemDC->SelectObject(&brush);
		pMemDC->FillRect(CRect(0, 0, GAME_WIDTH, GAME_HEIGHT), pOldBrush);
		//Game Over
		CString str = _T("���ź�����Ϸ����������F5���¿�ʼŶ!");
		pMemDC->SetBkMode(TRANSPARENT);
		pMemDC->SetTextAlign(TA_CENTER);
		pMemDC->SetTextColor(RGB(255, 0, 0));
		pMemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2, str);
	}
	else
	{
		if (GameNumber.GetID() == 0)
		{
			CBitmap bitmap;// ����λͼ����
			bitmap.LoadBitmapW(IDB_BEGIN);
			CBrush brush;
			brush.CreatePatternBrush(&bitmap);
			CBrush* pOldBrush = pMemDC->SelectObject(&brush);
			pMemDC->FillRect(CRect(0, 0, GAME_WIDTH, GAME_HEIGHT), pOldBrush);
		}
	    else if (GameNumber.GetID() == -1)
		{
			CBitmap bitmap;// ����λͼ����
			bitmap.LoadBitmapW(IDB_INTRODUCTION);
			CBrush brush;
			brush.CreatePatternBrush(&bitmap);
			CBrush* pOldBrush = pMemDC->SelectObject(&brush);
			pMemDC->FillRect(CRect(0, 0, GAME_WIDTH, GAME_HEIGHT), pOldBrush);
			CString st = _T("�ܹ��Ĺأ����޵�ģʽ����ͨģʽ���ڵ��Ĺس�boss");
			CString sst = _T("����������ƶ����ո�������ӵ���Q��W�ͷŴ���");
			CString st1 = _T("��P����ͣ��Ϸ����S��������Ϸ����F5������Ϸ");
			CString st2 = _T("--------�����ķָ���---------");
			CString st3 = _T("��ENTER������������");
			pMemDC->SetBkMode(TRANSPARENT);
			pMemDC->SetTextAlign(TA_CENTER);
			pMemDC->SetTextColor(RGB(255, 255, 255));
			pMemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2 - 40, st1);
			pMemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2 - 10, sst);
			pMemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2 + 20, st1);
			pMemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2 + 70, st2);
			pMemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2 + 140, st3);
		}
		else if (GameNumber.GetID() == 5)
		{
			CBitmap bitmap;// ����λͼ����
			bitmap.LoadBitmapW(IDB_INTRODUCTION);
			CBrush brush;
			brush.CreatePatternBrush(&bitmap);
			CBrush* pOldBrush = pMemDC->SelectObject(&brush);
			pMemDC->FillRect(CRect(0, 0, GAME_WIDTH, GAME_HEIGHT), pOldBrush);
			CString st2 = _T("--------��ϲ��ͨ����---------");
			pMemDC->SetBkMode(TRANSPARENT);
			pMemDC->SetTextAlign(TA_CENTER);
			pMemDC->SetTextColor(RGB(255, 255, 255));
			pMemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2 + 50, st2);
		}
		else
		{

			GameNumber.Draw(pMemDC);
			//�����ҷ�ս��
			m_pMe->Draw(m_pMemDC, FALSE);
			CString str;
			pMemDC->SetBkMode(TRANSPARENT);
			pMemDC->SetTextColor(RGB(255, 0, 0));
			str.Format(_T("Round:%d"), GameNumber.GetID());
			pMemDC->TextOutW(240, 20, str);
			str.Format(_T("��ǰ�÷�:%d"), score);
			pMemDC->TextOutW(10, 20, str);
			str.Format(_T("ʣ������:%d"), m_pMe->GetLife());
			pMemDC->TextOutW(10, 40, str);
			str.Format(_T("ʣ������:%d"), m_pMe->GetMagic());
			pMemDC->TextOutW(10, 60, str);
			if (m_Boss.GetLife() > 0 && GameNumber.GetID() == 4)
			{
				str.Format(_T("BOSS����:%d"), m_Boss.GetLife());
				pMemDC->TextOutW(10, 80, str);
				m_Boss.Draw(pMemDC, FALSE);
			}
			//���� ��������ը���л����ӵ�
			for (int i = 0; i<6; i++)
			{
				POSITION pos1, pos2;
				for (pos1 = m_ObjList[i].GetHeadPosition(); (pos2 = pos1) != NULL;)
				{
					CGameObject* pObj = (CGameObject*)m_ObjList[i].GetNext(pos1);
					if (!pObj->Draw(pMemDC, FALSE))
					{
						m_ObjList[i].RemoveAt(pos2);
						delete pObj;
					}
				}
			}
			CPoint pt = m_pMe->GetPoint();
			if (m_Circle != NULL)
			{
				m_Circle->UpdateCirclePos(pt.x - 58, pt.y - 100);
				if (!m_Circle->Draw(pMemDC, FALSE))
				{
					delete m_Circle;
					m_Circle = NULL;
				}
			}
			//Ѫ��ħ��ֵ�Ļ���
			CRect crec = m_pMe->GetRect();
			LifeMagic->UpDate(crec.left, crec.top, m_pMe->GetLife(), m_pMe->GetMagic());
			LifeMagic->Draw(m_pMemDC);

		}
	}
	//�����ڴ�DC���豸DC
	m_pDC->BitBlt(0,0,GAME_WIDTH,GAME_HEIGHT,m_pMemDC,0,0,SRCCOPY);
}
void CPlaneGameView::AI()
{
	if (m_Boss.GetLife() > 0 && GameNumber.GetID() == 4)
	{
		CPoint ept = m_Boss.GetPoint();
		if (m_Boss.Fired())
		{
			int x = (BOSS_WIDTH - 5 * BOSSBALL_WIDTH) / 4;
			int y = BOSSBALL_HEIGHT / 4;
			//��Ҫ�޸�λ��
			m_ObjList[enBossBall].AddTail(new CBossBall(ept.x, ept.y + BOSS_HEIGHT));
			m_ObjList[enBossBall].AddTail(new CBossBall(ept.x + x + BOSSBALL_WIDTH, ept.y + BOSS_HEIGHT + y));
			m_ObjList[enBossBall].AddTail(new CBossBall(ept.x + (x + BOSSBALL_WIDTH) * 2, ept.y + BOSS_HEIGHT + y * 2));
			m_ObjList[enBossBall].AddTail(new CBossBall(ept.x + (x + BOSSBALL_WIDTH) * 3, ept.y + BOSS_HEIGHT + y));
			m_ObjList[enBossBall].AddTail(new CBossBall(ept.x + (x + BOSSBALL_WIDTH) * 4, ept.y + BOSS_HEIGHT));
		}
	}
	static int nCreator = rand() % 5 + 50;

	//��������л�
	if (nCreator <= 0)
	{
		nCreator = rand() % 5 + 50;
		if (GameNumber.GetID() == 1)
		{
			m_ObjList[enEnemy].AddTail(new CEnemy(0));
			m_ObjList[enEnemy].AddTail(new CEnemy(1));
		}
		if (GameNumber.GetID() == 2)
		{
			m_ObjList[enEnemy].AddTail(new CEnemy(0));
			m_ObjList[enEnemy].AddTail(new CEnemy(1));
					m_ObjList[enEnemy].AddTail(new CEnemy(2));
					m_ObjList[enEnemy].AddTail(new CEnemy(3));
		}
		if (GameNumber.GetID() == 3 || GameNumber.GetID() == 4)
		{
			m_ObjList[enEnemy].AddTail(new CEnemy(0));
			m_ObjList[enEnemy].AddTail(new CEnemy(1));
			if (rand() % 2 == 0)
			{
				if (rand() % 2 == 0)
					m_ObjList[enEnemy].AddTail(new CEnemy(2));
				else
					m_ObjList[enEnemy].AddTail(new CEnemy(3));
			}
			if (rand() % 2 == 0)
			{
				//if (rand() % 2 == 0)
					m_ObjList[enEnemy].AddTail(new CEnemy(4));
				//else
					m_ObjList[enEnemy].AddTail(new CEnemy(5));
			}
		}
	}
	nCreator--;
	static int nCreator1 = rand() % 5 + 100;
	//�����������
	if (nCreator <= 0)
	{
		nCreator1 = rand() % 5 + 100;
		if (GameNumber.GetID() == 1)
		{
			if (rand() % 6 == 0)
				m_ObjList[enGift].AddTail(new CGift(0));
			if (rand() % 6 == 0)
				m_ObjList[enGift].AddTail(new CGift(1));
			if (rand() % 6 == 0)
				m_ObjList[enGift].AddTail(new CGift(2));
			if (rand() % 6 == 0)
				m_ObjList[enGift].AddTail(new CGift(3));
		}
		if (GameNumber.GetID() == 2)
		{
			if (rand() % 5 == 0)
				m_ObjList[enGift].AddTail(new CGift(0));
			if (rand() % 5 == 0)
				m_ObjList[enGift].AddTail(new CGift(1));
			if (rand() % 5 == 0)
				m_ObjList[enGift].AddTail(new CGift(2));
			if (rand() % 5 == 0)
				m_ObjList[enGift].AddTail(new CGift(3));
		}
		if (GameNumber.GetID() == 3 || GameNumber.GetID() == 4)
		{
			if (rand() % 4 == 0)
				m_ObjList[enGift].AddTail(new CGift(0));
			if (rand() % 4 == 0)
				m_ObjList[enGift].AddTail(new CGift(1));
			if (rand() % 4 == 0)
				m_ObjList[enGift].AddTail(new CGift(2));
			if (rand() % 4 == 0)
				m_ObjList[enGift].AddTail(new CGift(3));
		}
	}
	nCreator1--;
	if (m_pMe == NULL)
		return;

	//����ĸ���������ƶ�ս��
	for (int i = 0; i < 4; i++)
	{
		int nMeMotion = 0;
		m_pMe->SetVerMotion(0);
		m_pMe->SetHorMotion(0);

		nMeMotion = GetKey(VK_UP);
		if (nMeMotion == 1)
			m_pMe->SetVerMotion(1);

		nMeMotion = GetKey(VK_DOWN);
		if (nMeMotion == 1)
			m_pMe->SetVerMotion(-1);

		nMeMotion = GetKey(VK_RIGHT);
		if (nMeMotion == 1)
			m_pMe->SetHorMotion(1);

		nMeMotion = GetKey(VK_LEFT);
		if (nMeMotion == 1)
			m_pMe->SetHorMotion(-1);
	}
	CPoint pt = m_pMe->GetPoint();
	//����ս������
	if (GetKey(VK_SPACE) == 1)//�����˿ո��
	{
		if (m_pMe != NULL && m_pMe->Fired())
		{
			if (GameNumber.GetID() == 1)
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + PLANE_WIDTH / 2 - BOMB_WIDTH / 2, pt.y - BOMB_HEIGHT - 5, 1));
			else if (GameNumber.GetID() == 2)
			{
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + PLANE_WIDTH / 2 - BOMB_WIDTH / 2 - 20, pt.y - BOMB_HEIGHT, 1));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + PLANE_WIDTH / 2 - BOMB_WIDTH / 2 + 20, pt.y - BOMB_HEIGHT, 1));
			}
			else if (GameNumber.GetID() == 3 || GameNumber.GetID() == 4)
			{
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + PLANE_WIDTH / 2 - BOMB_WIDTH / 2 - 25, pt.y - BOMB_HEIGHT, 1));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + PLANE_WIDTH / 2 - BOMB_WIDTH / 2, pt.y - BOMB_HEIGHT - 20, 1));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + PLANE_WIDTH / 2 - BOMB_WIDTH / 2 + 25, pt.y - BOMB_HEIGHT, 1));
			}
		}
	}

	//����q�� �ͷ������ͨ�ӵ�
	if (GetKeyState('Q') < 0)
	{
		if (m_pMe != NULL && m_pMe->Fired() && m_pMe->GetMagic() >= 20)
		{
			int x = (PLANE_WIDTH - 5 * BOMB_WIDTH) / 4;
			int y = PLANE_HEIGHT / 4;
			//ħ��ֵ��20��
			m_pMe->LossMagic(20);
			m_ObjList[enBomb].AddTail(new CBomb(pt.x, pt.y - PLANE_HEIGHT, 2));
			m_ObjList[enBomb].AddTail(new CBomb(pt.x + x + BOMB_WIDTH, pt.y - PLANE_HEIGHT - y, 2));
			m_ObjList[enBomb].AddTail(new CBomb(pt.x + (x + BOMB_WIDTH) * 2, pt.y - PLANE_HEIGHT - y * 2, 2));
			m_ObjList[enBomb].AddTail(new CBomb(pt.x + (x + BOMB_WIDTH) * 3, pt.y - BOMB_HEIGHT - y, 2));
			m_ObjList[enBomb].AddTail(new CBomb(pt.x + (x + BOMB_WIDTH) * 4, pt.y - PLANE_HEIGHT, 2));
		}
	}
	//����w�� �ͷ���������
	if (GetKeyState('W') < 0)
	{
		if (m_pMe != NULL && m_pMe->Fired() && m_pMe->GetMagic() >= 40)
		{
			//ħ��ֵ��40��
			int x = (PLANE_WIDTH - 5 * BOMB_WIDTH) / 4;
			int y = PLANE_HEIGHT / 4;
			m_pMe->LossMagic(40);
			m_ObjList[enBomb].AddTail(new CBomb(pt.x, pt.y - PLANE_HEIGHT, 3));
			m_ObjList[enBomb].AddTail(new CBomb(pt.x + x + BOMB_WIDTH, pt.y - PLANE_HEIGHT - y, 3));
			m_ObjList[enBomb].AddTail(new CBomb(pt.x + (x + BOMB_WIDTH) * 2, pt.y - PLANE_HEIGHT - y * 2, 3));
			m_ObjList[enBomb].AddTail(new CBomb(pt.x + (x + BOMB_WIDTH) * 3, pt.y - BOMB_HEIGHT - y, 3));
			m_ObjList[enBomb].AddTail(new CBomb(pt.x + (x + BOMB_WIDTH) * 4, pt.y - PLANE_HEIGHT, 3));
			if (m_Circle == NULL)
				m_Circle = new CCircle(pt.x, pt.y);
		}
	}
	//�л������ӵ�

	CPoint PlanePt = m_pMe->GetPoint();
	for (POSITION ePos = m_ObjList[enEnemy].GetHeadPosition(); ePos != NULL;)
	{
		CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos);
		if (!pEnemy->Fired())
			continue;
		CPoint  ePt = pEnemy->GetPoint();
		if (pEnemy->GetID() % 2 == 0 && ePt.y < GAME_HEIGHT - ENEMY_HEIGHT)
			m_ObjList[enBall].AddTail(new CBall(ePt.x, ePt.y, pEnemy->GetID()));
		if (pEnemy->GetID() % 2 == 1 && ePt.y > ENEMY_HEIGHT)
			m_ObjList[enBall].AddTail(new CBall(ePt.x, ePt.y, pEnemy->GetID()));

	}
	if (m_Circle != NULL)
	{
		POSITION bPos11 = NULL, bPos22 = NULL;
		CRect mRect = m_Circle->GetRect();
		for (bPos11 = m_ObjList[enBall].GetHeadPosition(); (bPos22 = bPos11) != NULL;)
		{
			CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(bPos11);
			CRect bRect = pBall->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(bRect.left, bRect.top)
					);

				//ɾ���ӵ�
				m_ObjList[enBall].RemoveAt(bPos22);
				delete pBall;
			}
		}
		bPos11 = NULL, bPos22 = NULL;
		for (bPos11 = m_ObjList[enEnemy].GetHeadPosition(); (bPos22 = bPos11) != NULL;)
		{
			CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(bPos11);
			CRect bRect = pEnemy->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(bRect.left, bRect.top)
					);

				//ɾ���ӵ�
				m_ObjList[enEnemy].RemoveAt(bPos22);
				delete pEnemy;
			}
		}
		bPos11 = NULL, bPos22 = NULL;
		for (bPos11 = m_ObjList[enBossBall].GetHeadPosition(); (bPos22 = bPos11) != NULL;)
		{
			CBossBall* pBossBall = (CBossBall*)m_ObjList[enBossBall].GetNext(bPos11);
			CRect bRect = pBossBall->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(bRect.left, bRect.top)
					);

				//ɾ���ӵ�
				m_ObjList[enBossBall].RemoveAt(bPos22);
				delete pBossBall;
			}
		}
		if (m_Boss.GetLife() > 0 && GameNumber.GetID() == 4)
		{
			CRect bRect = m_Boss.GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(bRect.left, bRect.top)
					);
				m_Boss.LossLife();
				if (m_Boss.GetLife() <= 0 && m_pMe != NULL)
				{
					//m_ObjList[enExplosion].AddTail(
						////new CBossExplosion(bRect.left, bRect.top)
						//);
					//GameNumber.UpdateID(5);
				}
			}
		}

	}

	//�л��ӵ�ը��ս��
	POSITION bPos1 = NULL, bPos2 = NULL;
	CRect mRect = m_pMe->GetRect();
	for (bPos1 = m_ObjList[enBall].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(bPos1);
		CRect bRect = pBall->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left, mRect.top)
				);

			//ɾ���ӵ�
			m_ObjList[enBall].RemoveAt(bPos2);
			delete pBall;
			if (invincible == 0)
				m_pMe->LossLife();
			if (m_pMe->GetLife() <= 0)
			{
				//ɾ��ս��
				delete m_pMe;
				m_pMe = NULL;
				break;
			}
		}
	}

	//bossball
	bPos1 = NULL, bPos2 = NULL;
	for (bPos1 = m_ObjList[enBossBall].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CBossBall* pBossBall = (CBossBall*)m_ObjList[enBossBall].GetNext(bPos1);
		CRect bRect = pBossBall->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left, mRect.top)
				);

			//ɾ���ӵ�
			m_ObjList[enBossBall].RemoveAt(bPos2);
			delete pBossBall;
			if (invincible == 0)
				m_pMe->LossLife();
			if (m_pMe->GetLife() <= 0)
			{
				//ɾ��ս��
				delete m_pMe;
				m_pMe = NULL;
				break;
			}
		}
	}


	//ս������ը���л�
	POSITION mPos1 = NULL, mPos2 = NULL;
	for (mPos1 = m_ObjList[enBomb].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
		CRect bRect = pBomb->GetRect();

		POSITION ePos1 = NULL, ePos2 = NULL;
		for (ePos1 = m_ObjList[enEnemy].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
		{
			CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
			CRect mRect = pEnemy->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				score += 10;
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
					);
				//ɾ������
				m_ObjList[enBomb].RemoveAt(mPos2);
				if (pEnemy->GetID() >= 2)
				{
					//�������1-4������
					if (rand() % 6 == 0)
					{
						m_ObjList[enGift].AddTail(
							new CGift(mRect.left, mRect.top,0)
							);
					}
					else if (rand() % 6 == 1)
					{
						m_ObjList[enGift].AddTail(
							new CGift(mRect.left , mRect.top , 0)
							);
						m_ObjList[enGift].AddTail(
							new CGift(mRect.left + 5, mRect.top + 5, 1)
							);
					}
					else if (rand() % 6 == 2)
					{
						m_ObjList[enGift].AddTail(
							new CGift(mRect.left, mRect.top, 0)
							);
						m_ObjList[enGift].AddTail(
							new CGift(mRect.left+5, mRect.top+5, 1)
							);
						m_ObjList[enGift].AddTail(
							new CGift(mRect.left+9, mRect.top+9, 2)
							);
					}
					else if (rand() % 6 == 3)
					{
						m_ObjList[enGift].AddTail(
							new CGift(mRect.left, mRect.top, 0)
							);
						m_ObjList[enGift].AddTail(
							new CGift(mRect.left + 5, mRect.top + 5, 1)
							);
						m_ObjList[enGift].AddTail(
							new CGift(mRect.left + 9, mRect.top + 9, 2)
							);
						m_ObjList[enGift].AddTail(
							new CGift(mRect.left + 15, mRect.top + 15, 3)
							);
					}
				}
				delete pBomb;

				//ɾ���л�
				m_ObjList[enEnemy].RemoveAt(ePos2);
				delete pEnemy;
				break;
			}
		}
	}
	//ը��boss
	if (m_Boss.GetLife() > 0 && GameNumber.GetID() == 4)
	{
		mPos1 = NULL, mPos2 = NULL;
		for (mPos1 = m_ObjList[enBomb].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
		{
			CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
			CRect bRect = pBomb->GetRect();
			CRect mRect = m_Boss.GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
					);
				m_Boss.LossLife();
				//ɾ������
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;
				if (m_Boss.GetLife() <= 0)
				{
					//m_ObjList[enExplosion].AddTail(
						//new CBossExplosion(bRect.left, bRect.top)
						//);
					break;
				}
			}
		}
	}
	//ս�������л�
	bPos1 = NULL; bPos2 = NULL;
	for (bPos1 = m_ObjList[enEnemy].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(bPos1);
		CRect bRect = pEnemy->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			//ɾ���ӵ�
			m_ObjList[enEnemy].RemoveAt(bPos2);
			//ս����ը����--------------------------------��ͼƬ������
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left, mRect.top)
				);
			m_ObjList[enExplosion].AddTail(
				new CExplosion(bRect.left, bRect.top)
				);
			if (pEnemy->GetID() >= 2)
			{
				//�������1-4������
				if (rand() % 6 == 0)
				{
					m_ObjList[enGift].AddTail(
						new CGift(mRect.left, mRect.top, 0)
						);
				}
				else if (rand() % 6 == 1)
				{
					m_ObjList[enGift].AddTail(
						new CGift(mRect.left, mRect.top, 0)
						);
					m_ObjList[enGift].AddTail(
						new CGift(mRect.left + 5, mRect.top + 5, 1)
						);
				}
				else if (rand() % 6 == 2)
				{
					m_ObjList[enGift].AddTail(
						new CGift(mRect.left, mRect.top, 0)
						);
					m_ObjList[enGift].AddTail(
						new CGift(mRect.left + 5, mRect.top + 5, 1)
						);
					m_ObjList[enGift].AddTail(
						new CGift(mRect.left + 9, mRect.top + 9, 2)
						);
				}
				else if (rand() % 6 == 3)
				{
					m_ObjList[enGift].AddTail(
						new CGift(mRect.left, mRect.top, 0)
						);
					m_ObjList[enGift].AddTail(
						new CGift(mRect.left + 5, mRect.top + 5, 1)
						);
					m_ObjList[enGift].AddTail(
						new CGift(mRect.left + 9, mRect.top + 9, 2)
						);
					m_ObjList[enGift].AddTail(
						new CGift(mRect.left + 15, mRect.top + 15, 3)
						);
				}
			}
			if (invincible == 0)
			{
				m_pMe->LossLife();
				delete pEnemy;
				if (m_pMe->GetLife() <= 0)
				{
					//ɾ��ս��
					delete m_pMe;
					m_pMe = NULL;
					break;
				}
			}
			else
			{
				delete pEnemy;
			}
		}
	}
	//ս������Gift
	bPos1 = NULL; bPos2 = NULL;
	for (bPos1 = m_ObjList[enGift].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CGift* pGift = (CGift*)m_ObjList[enGift].GetNext(bPos1);
		CRect bRect = pGift->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			//ɾ���ӵ�
			m_ObjList[enGift].RemoveAt(bPos2);
			if (pGift->GetID() == 0)
				m_pMe->AddMagic();
			if (pGift->GetID() == 1)
				m_pMe->AddLife();
			if (pGift->GetID() == 2)
			{
				CPoint pt = m_pMe->GetPoint();
				if (m_Circle == NULL)
					m_Circle = new CCircle(pt.x, pt.y);
			}
			if (pGift->GetID() == 3)
			{
				m_ObjList[enExplosion].AddTail(
					new CExplosion(bRect.left, bRect.top)
					);
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
					);
				if (invincible == 0)
				{
					m_pMe->LossLife();
					if (m_pMe->GetLife() <= 0)
					{
						delete m_pMe;
						m_pMe = NULL;
						delete pGift;
						break;
					}
				}
			}
			delete pGift;
		}
	}
	//ս������boss
	if (m_Boss.GetLife() > 0 && GameNumber.GetID() == 4 && m_pMe != NULL)
	{
		CRect mRect = m_pMe->GetRect();
		CRect bRect = m_Boss.GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			if (invincible == 0)
			{
				m_pMe->LossLife();
				if (m_pMe->GetLife() <= 0)
				{
					//ɾ��ս��
					delete m_pMe;
					m_pMe = NULL;
				}
			}
			m_Boss.LossLife();
			if (m_Boss.GetLife() <= 0 && m_pMe != NULL)
			{
				///m_ObjList[enExplosion].AddTail(
					//new CBossExplosion(bRect.left, bRect.top)
					//);
				//GameNumber.UpdateID(5);
			}

		}
	}
	//�жϹؿ�
	if (m_pMe != NULL)
	{
		if (score > 150 && GameNumber.GetID() == 1)
		{
			KillTimer(1);
			for (int i = 0; i < 6; i++)
			{
				m_ObjList[i].RemoveAll();
			}
			GameNumber.UpdateID(2);
			SetTimer(1, 30, NULL);
		}
		else if (score > 300 && GameNumber.GetID() == 2)
		{
			KillTimer(1);
			for (int i = 0; i < 6; i++)
			{
				m_ObjList[i].RemoveAll();
			}
			GameNumber.UpdateID(3);
			SetTimer(1, 30, NULL);
		}
		else if (score >  450 && GameNumber.GetID() == 3)
		{
			KillTimer(1);
			for (int i = 0; i < 6; i++)
			{
				m_ObjList[i].RemoveAll();
			}
			GameNumber.UpdateID(4);
			SetTimer(1, 30, NULL);
		}
		else if (GameNumber.GetID() == 4 && m_Boss.GetLife() <= 0)
		{
			//KillTimer(1);
			for (int i = 0; i < 6; i++)
			{
				m_ObjList[i].RemoveAll();
		   }
			GameNumber.UpdateID(5);
		//SetTimer(1, 30, NULL);
		}

	}

	
}
void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{
	if (GetKeyState('P') < 0){//��ͣ
		isPause = 1;
	}
	if (GetKeyState('S') < 0){//��ʼ
		isPause = 0;
	}
	//��ʼ��Ϸ
	if (GetKey(VK_F1) == 1 && GameNumber.GetID() == 0)
	{
		//m_pMe = new CMyPlane;
		GameNumber.UpdateID(1);
	}
	//��ʱ���Խ����޵�ģʽ
	if (GetKey(VK_F2) == 1 && m_pMe != NULL){
		invincible = 1;
		while (m_pMe->GetLife() != 100)
		{
			m_pMe->AddLife();
		}
		while (m_pMe->GetMagic() != 100)
		{
			m_pMe->AddMagic();
		}
		if (GameNumber.GetID() == 0)
			GameNumber.UpdateID(1);
	}
	//�쿴��Ϸ����
	if (GetKey(VK_F3) == 1 && GameNumber.GetID() == 0)
	{
		GameNumber.UpdateID(-1);
	}
	//��ENTER������ҳ��
	if (GetKey(VK_RETURN) == 1 && GameNumber.GetID() == -1)
	{
		GameNumber.UpdateID(0);
	}
	if (GetKey(VK_F5) == 1)
	{
		GameNumber.UpdateID(1);
		if (m_pMe == NULL)
			m_pMe = new CMyPlane;
		m_Boss.SetLife();
		m_pMe->Recover();
		score = 0;
		invincible = 0;
		isPause = 0;
	}
	//�˳���Ϸ
	if (GetKey(VK_F4) == 1)
	{
		exit(1);

	}
	//������Ϸ
	if (GetKey(VK_F5) == 1)
	{
		GameNumber.UpdateID(0);

	}
	//ˢ����Ϸ֡����: ���ڴ�DC�ϻ�ͼ
	if (!isPause)
	{
		UpdateFrame(m_pMemDC);
		AI();
	}
	CView::OnTimer(nIDEvent);
}


