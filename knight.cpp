#include "stdafx.h"
#include "knight.h"


knight::knight()
{
}


knight::~knight()
{
}

HRESULT knight::init()
{
	_image = IMAGE_M->addFrameImage("knight", "knight.bmp", 0, 0, 612, 312, 9, 4, true, RGB(255, 0, 255));

	_knightDirection = KNIGHTDIRECTION_RIGHT_STOP;

	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(),
		_image->getFrameHeight());

	int rightStop[] = { 0 };
	KEYANI_M->addArrayFrameAnimation("knightRightStop", "knight", rightStop, 1, 6, true);

	int leftStop[] = { 9 };
	KEYANI_M->addArrayFrameAnimation("knightLeftStop", "knight", leftStop, 1, 6, true);

	int rightMove[] = { 1,2,3,4,5,6 };
	KEYANI_M->addArrayFrameAnimation("knightRightMove", "knight", rightMove, 6, 10, true);

	int leftMove[] = { 10, 11, 12, 13, 14, 15 };
	KEYANI_M->addArrayFrameAnimation("knightLeftMove", "knight", leftMove, 6, 10, true);

	int arrRightAttack[] = { 7, 8 };
	KEYANI_M->addArrayFrameAnimation("knightRightAttack", "knight", arrRightAttack, 2, 10, false, rightFire, this);

	int arrLeftAttack[] = { 16, 17 };
	KEYANI_M->addArrayFrameAnimation("knightLeftAttack", "knight", arrLeftAttack, 2, 10, false, leftFire, this);

	int arrRightJump[] = { 22, 24, 25 };
	KEYANI_M->addArrayFrameAnimation("knightRightJump", "knight", arrRightJump, 3, 4, false, rightJump, this);

	int arrLeftJump[] = { 31, 33, 34 };
	KEYANI_M->addArrayFrameAnimation("knightLeftJump", "knight", arrLeftJump, 3, 4, false, leftJump, this);

	int arrRightMoveJump[] = { 21, 23 };
	KEYANI_M->addArrayFrameAnimation("knightRightMoveJump", "knight", arrRightMoveJump, 2, 3, false, rightMoveJump, this);

	int arrLeftMoveJump[] = { 30, 32 };
	KEYANI_M->addArrayFrameAnimation("knightLeftMoveJump", "knight", arrLeftMoveJump, 2, 3, false, leftMoveJump, this);


	_knightMotion = KEYANI_M->findAnimation("knightRightStop");

	_jump = new jump;
	_jump->init();

	return S_OK;
}

void knight::release()
{
}

void knight::update()
{
	if (KEY_M->isOnceKeyDown(VK_RIGHT))
	{
		_knightDirection = KNIGHTDIRECTION_RIGHT_MOVE;
		_knightMotion = KEYANI_M->findAnimation("knightRightMove");
		_knightMotion->start();
	}
	if (KEY_M->isOnceKeyUp(VK_RIGHT))
	{
		_knightDirection = KNIGHTDIRECTION_RIGHT_STOP;
		_knightMotion = KEYANI_M->findAnimation("knightRightStop");
		_knightMotion->start();
	}
	if (KEY_M->isOnceKeyDown(VK_LEFT))
	{
		_knightDirection = KNIGHTDIRECTION_LEFT_MOVE;
		_knightMotion = KEYANI_M->findAnimation("knightLeftMove");
		_knightMotion->start();
	}
	if (KEY_M->isOnceKeyUp(VK_LEFT))
	{
		_knightDirection = KNIGHTDIRECTION_LEFT_STOP;
		_knightMotion = KEYANI_M->findAnimation("knightLeftStop");
		_knightMotion->start();
	}

	if (KEY_M->isOnceKeyDown('Z'))
	{
		if (_knightDirection == KNIGHTDIRECTION_RIGHT_STOP ||
			_knightDirection == KNIGHTDIRECTION_RIGHT_MOVE)
		{
			_knightDirection = KNIGHTDIRECTION_RIGHT_ATTACK;
			_knightMotion = KEYANI_M->findAnimation("knightRightAttack");
			_knightMotion->start();
		}

		if (_knightDirection == KNIGHTDIRECTION_LEFT_STOP ||
			_knightDirection == KNIGHTDIRECTION_LEFT_MOVE)
		{
			_knightDirection = KNIGHTDIRECTION_LEFT_ATTACK;
			_knightMotion = KEYANI_M->findAnimation("knightLeftAttack");
			_knightMotion->start();
		}
	}

	if (KEY_M->isOnceKeyDown(VK_UP))
	{
		_jump->jumping(&_x, &_y, 8.0f, 0.4f);

		if (_knightDirection == KNIGHTDIRECTION_RIGHT_STOP)
		{
			_knightDirection = KNIGHTDIRECTION_RIGHT_JUMP;
			_knightMotion = KEYANI_M->findAnimation("knightRightJump");
			_knightMotion->start();
		}
		if (_knightDirection == KNIGHTDIRECTION_RIGHT_MOVE)
		{
			_knightDirection = KNIGHTDIRECTION_RIGHT_MOVE_JUMP;
			_knightMotion = KEYANI_M->findAnimation("knightRightMoveJump");
			_knightMotion->start();
		}
	}

	switch (_knightDirection)
	{
		case KNIGHTDIRECTION_RIGHT_MOVE: case KNIGHTDIRECTION_RIGHT_MOVE_JUMP:
			_x += KNIGHTSPEED;
		break;

		case KNIGHTDIRECTION_LEFT_MOVE: case KNIGHTDIRECTION_LEFT_MOVE_JUMP:
			_x -= KNIGHTSPEED;
		break;
	}

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	KEYANI_M->update();
	_jump->update();

}

void knight::render()
{
	_image->aniRender(getMemDC(), _rc.left, _rc.top, _knightMotion);
}

void knight::rightFire(void * obj)
{
	knight* k = (knight*)obj;

	k->setKnightDirection(KNIGHTDIRECTION_RIGHT_STOP);
	k->setKnightMotion(KEYANI_M->findAnimation("knightRightStop"));
	k->getKnightMotion()->start();
}

void knight::leftFire(void * obj)
{
	knight* k = (knight*)obj;

	k->setKnightDirection(KNIGHTDIRECTION_RIGHT_STOP);
	k->setKnightMotion(KEYANI_M->findAnimation("knightRightStop"));
	k->getKnightMotion()->start();
}

void knight::rightJump(void * obj)
{
	knight* k = (knight*)obj;

	k->setKnightDirection(KNIGHTDIRECTION_RIGHT_STOP);
	k->setKnightMotion(KEYANI_M->findAnimation("knightRightStop"));
	k->getKnightMotion()->start();
}

void knight::leftJump(void * obj)
{
}

void knight::rightMoveJump(void * obj)
{
	knight* k = (knight*)obj;

	k->setKnightDirection(KNIGHTDIRECTION_RIGHT_MOVE);
	k->setKnightMotion(KEYANI_M->findAnimation("knightRightMove"));
	k->getKnightMotion()->start();
}

void knight::leftMoveJump(void * obj)
{
}
