#pragma once
#include "gameNode.h"
#include "ghostNGoblinScene.h"


class playGround : public gameNode
{
private:
	int _strength;
	char* _intel;
	
public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	

};

