#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{

	_hdc = GetDC(_hWnd);
	_managerInit = false;


	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (_managerInit)
	{
	//	SetTimer(_hWnd, 1, 10, NULL);
		KEY_M->init();
		IMAGE_M->init();
		TIME_M->init();
		EFFECT_M->init();
		SOUND_M->init();
		SCENE_M->init();
		KEYANI_M->init();
		TXTDATA->init();
		INIDATA->init();
	}


	return S_OK;
}

void gameNode::release()
{
	if (_managerInit)
	{
	//	KillTimer(_hWnd, 1);

		KEY_M->release();
		KEY_M->releaseSingleton();

		IMAGE_M->release();
		IMAGE_M->releaseSingleton();

		TXTDATA->release();
		TXTDATA->releaseSingleton();

		TIME_M->release();
		TIME_M->releaseSingleton();

		EFFECT_M->release();
		EFFECT_M->releaseSingleton();

		SOUND_M->release();
		SOUND_M->releaseSingleton();

		SCENE_M->release();
		SCENE_M->releaseSingleton();

		KEYANI_M->release();
		KEYANI_M->releaseSingleton();

		INIDATA->release();
		INIDATA->releaseSingleton();
	}
	
	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update()
{
	
}

void gameNode::render()
{

}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//HWND - 핸들메시지
	//UINT - 메시지 발생 번호
	//WPARAM - 키보드 입력 및 마우스 클릭 메시지 전달
	//LPARAM - 마우스 좌표 전달

	PAINTSTRUCT ps;
	HDC			hdc;

	switch (iMessage)
	{
	
		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>(LOWORD(lParam));
			_ptMouse.y = static_cast<float>(HIWORD(lParam));
		break;

		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case VK_ESCAPE:
					PostQuitMessage(0);
				break;

			}
		}
		break;

		case WM_DESTROY:
			PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
