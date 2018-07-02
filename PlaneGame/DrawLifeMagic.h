#pragma once
class CDrawLifeMagic
{
public:
	CDrawLifeMagic();
	~CDrawLifeMagic();
public:
	void Draw(CDC* pDC);
	void UpDate(int xx, int yy, int xx1, int xx2);
private:
	//¿í¶È
	int x1;
	int x2;
	int x;
	int y;

};

