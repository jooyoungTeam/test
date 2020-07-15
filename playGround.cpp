#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ �Լ�
HRESULT playGround::init()
{
	gameNode::init(true);

	INIDATA->addData("����", "����", "99");
	INIDATA->addData("����", "����", "78");
	INIDATA->addData("����", "�γ���", "200");

	INIDATA->addData("�ǿ�", "����", "95");
	INIDATA->addData("�ǿ�", "���߷�", "999");
	INIDATA->addData("�ǿ�", "����", "100");

	INIDATA->iniSave("�����ΰ�");

	_strength = INIDATA->loadDataInteger("�����ΰ�","�ǿ�", "����");
	_intel = INIDATA->loadDataString("�����ΰ�", "����", "�γ���");

	return S_OK;
}

//�޸� ����
void playGround::release()
{
	
}

//����
void playGround::update()
{
	gameNode::update();

	
}

//�׸��� ����
void playGround::render()
{	
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================

	

	TIMEMANAGER->render(getMemDC());
	
	//=============================================
	_backBuffer->render(getHDC(), 0, 0);
}
