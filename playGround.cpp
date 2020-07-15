#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화 함수
HRESULT playGround::init()
{
	gameNode::init(true);

	INIDATA->addData("관우", "무력", "99");
	INIDATA->addData("관우", "지력", "78");
	INIDATA->addData("관우", "인내력", "200");

	INIDATA->addData("건우", "무력", "95");
	INIDATA->addData("건우", "도발력", "999");
	INIDATA->addData("건우", "포텐", "100");

	INIDATA->iniSave("도발인가");

	_strength = INIDATA->loadDataInteger("도발인가","건우", "무력");
	_intel = INIDATA->loadDataString("도발인가", "관우", "인내력");

	return S_OK;
}

//메모리 해제
void playGround::release()
{
	
}

//연산
void playGround::update()
{
	gameNode::update();

	
}

//그리기 전용
void playGround::render()
{	
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================

	

	TIMEMANAGER->render(getMemDC());
	
	//=============================================
	_backBuffer->render(getHDC(), 0, 0);
}
