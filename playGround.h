#pragma once
#include "gameNode.h"
#include "ghostNGoblinScene.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")


class playGround : public gameNode
{
private:
	int _strength;
	char* _intel;

	RECT _player;
	RECT _enemy[5];

	//vector<pair<string, int>> _temp;
	RECT _tempY[6];

	vector<RECT> _vRect;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void quickSort(int i, int j);

};

