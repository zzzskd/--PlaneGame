#include "stdafx.h"
#include "BackGround.h"
#include "resource.h"

CBackGround::CBackGround() :ID(0), speed(0)
{
}
CBackGround::~CBackGround()
{
}
void CBackGround::Draw(CDC* pDC)
{

	speed += 1;
	if (speed>GAME_HEIGHT)
		speed = 0;
	CBitmap bmp;
	if (ID == 1)
		bmp.LoadBitmapW(IDB_BACKGROUND1);
	else if (ID == 2)
		bmp.LoadBitmapW(IDB_BACKGROUND2);
	else if (ID == 3)
		bmp.LoadBitmapW(IDB_BACKGROUND3);
	else if (ID == 4)
		bmp.LoadBitmapW(IDB_BACKGROUND4);
	CDC mDC;
	mDC.CreateCompatibleDC(pDC);
	mDC.SelectObject(bmp);
	pDC->BitBlt(0, speed, GAME_WIDTH, GAME_HEIGHT - speed, &mDC, 0, 0, SRCCOPY);
	pDC->BitBlt(0, 0, GAME_WIDTH, speed, &mDC, 0, GAME_HEIGHT - speed, SRCCOPY);
	mDC.DeleteDC();

}