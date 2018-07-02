#pragma once
class CBackGround
{
public:
	CBackGround();
	~CBackGround();
public:
	void Draw(CDC* pDC);
	void UpdateID(int id)
	{
		ID = id;
	}
	int GetID()const
	{
		return ID;
	}

private:
	int ID;
	int speed;
};

