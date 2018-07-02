#include "stdafx.h"
#include "DrawLifeMagic.h"


CDrawLifeMagic::CDrawLifeMagic()
{

}
CDrawLifeMagic::~CDrawLifeMagic()
{
}
void CDrawLifeMagic::UpDate(int xx, int yy, int xx1, int xx2)
{
	x = xx; y = yy;
	x1 = xx1; x2 = xx2;
}

void CDrawLifeMagic::Draw(CDC* pDC)
{
	//magicÖµ
	pDC->FillSolidRect(x + 10, y - 3, 100, 4, RGB(255, 255, 255));
	pDC->FillSolidRect(x + 10, y - 3, x2, 4, RGB(0, 255, 255));
	//ÑªÌõ
	pDC->FillSolidRect(x + 10, y - 7, 100, 4, RGB(255, 255, 255));
	pDC->FillSolidRect(x + 10, y - 7, x1, 4, RGB(255, 0, 0));
}