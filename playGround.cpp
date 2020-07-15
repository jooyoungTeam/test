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

	//INIDATA->addData("관우", "무력", "99");
	//INIDATA->addData("관우", "지력", "78");
	//INIDATA->addData("관우", "인내력", "200");

	//INIDATA->addData("건우", "무력", "95");
	//INIDATA->addData("건우", "도발력", "999");
	//INIDATA->addData("건우", "포텐", "100");

	//INIDATA->iniSave("도발인가");

	//_strength = INIDATA->loadDataInteger("도발인가","건우", "무력");
	//_intel = INIDATA->loadDataString("도발인가", "관우", "인내력");

	_player = RectMakeCenter(100, 100, 100, 100);
	_tempY[0] = _player;

	for (int i = 0; i < 5; i++)
	{
		_enemy[i] = RectMakeCenter(150 + i * 20, 90 + i * 10, 100, 100);
		_tempY[i + 1] = _enemy[i];
	}

	for (int i = 0; i < 6; i++)
	{
		_vRect.push_back(_tempY[i]);
		cout << _vRect[i].bottom << endl;
	}

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
	if (KEY_M->isStayKeyDown(VK_LEFT))
	{
		_player.left -= 3;
		_player.right -= 3;
	}
	if (KEY_M->isStayKeyDown(VK_RIGHT))
	{
		_player.left += 3;
		_player.right += 3;
	}

	if (KEY_M->isStayKeyDown(VK_UP))
	{
		_player.bottom -= 3;
		_player.top -= 3;
	}
	if (KEY_M->isStayKeyDown(VK_DOWN))
	{
		_player.bottom += 3;
		_player.top += 3;
	}


	if (KEY_M->isStayKeyDown('A'))
	{
		_enemy[2].left -= 3;
		_enemy[2].right -= 3;
	}
	if (KEY_M->isStayKeyDown('D'))
	{
		_enemy[2].left += 3;
		_enemy[2].right += 3;
	}

	if (KEY_M->isStayKeyDown('W'))
	{
		_enemy[2].bottom -= 3;
		_enemy[2].top -= 3;
	}
	if (KEY_M->isStayKeyDown('S'))
	{
		_enemy[2].bottom += 3;
		_enemy[2].top += 3;
	}


	_tempY[0] = _player;
	for (int i = 0; i < 5; i++)
	{
		_tempY[i + 1] = _enemy[i];
	}

	quickSort(0, 5);

	_vRect.clear();
	for (int i = 0; i < 6; i++)
	{
		//_vRect[i] = _tempY[i];
		_vRect.push_back(_tempY[i]);
		//cout << "1" << endl;
	}

}

//그리기 전용
void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//=================================================

	for (int i = 0; i < _vRect.size(); i++)
	{
		Rectangle(getMemDC(), _vRect[i]);
	}
	//Rectangle(getMemDC(), _tempY[0]);

	TIME_M->render(getMemDC());

	//=============================================
	_backBuffer->render(getHDC(), 0, 0);
}


void playGround::quickSort(int i, int j)
{
	if (i >= j) return;
	int pivot = _tempY[(i + j) / 2].bottom;
	int left = i;
	int right = j;

	while (left <= right)
	{
		while (_tempY[left].bottom < pivot) left++;
		while (_tempY[right].bottom > pivot) right--;
		if (left <= right)
		{
			swap(_tempY[left], _tempY[right]);
			left++; right--;
		}
	}
	quickSort(i, right);
	quickSort(left, j);
}