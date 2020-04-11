// sample02.cpp

#include <windows.h>
#include <string.h>
#include "sample02.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void ShowMyText(HWND hWnd);
char szClassName[] = "sample02";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND		hWnd;
	MSG			msg;
	WNDCLASS	myProg;

	if (!hPreInst)
	{
		myProg.style = CS_HREDRAW | CS_VREDRAW;
		myProg.lpfnWndProc = WndProc;
		myProg.cbClsExtra = 0;
		myProg.cbWndExtra = 0;
		myProg.hInstance = hInstance;
		myProg.hIcon = NULL;
		myProg.hCursor = LoadCursor(NULL, IDC_ARROW);
		myProg.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
		myProg.lpszMenuName = "SAMPLE02";
		myProg.lpszClassName = szClassName;

		// �E�B���h�E�̓o�^
		if (!RegisterClass(&myProg))
		{
			return FALSE;
		}
	}

	// �E�B���h�E�̍쐬
	hWnd = CreateWindow(szClassName,			// �N���X��
		"�L�ł��킩��v���O���~���O",			// �E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,					// �E�B���h�E�X�^�C��
		CW_USEDEFAULT,							// X���W
		CW_USEDEFAULT,							// Y���W
		CW_USEDEFAULT,							// �E�B���h�E�̉���
		CW_USEDEFAULT,							// �E�B���h�E�̍���
		NULL,									// �e�E�B���h�E�n���h���i�e�E�B���h�E����鎞��NULL�j
		NULL,									// ���j���[�n���h���i�N���X���j���[�̎���NULL�j
		hInstance,								// �C���X�^���X�n���h��
		NULL);									// �E�B���h�E�쐬�f�[�^

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDM_END:
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		ShowMyText(hWnd);
		break;
	default:
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}

	return (0L);
}


void ShowMyText(HWND hWnd)
{
	HDC hdc;
	const char* str_org = "left=%d top=%d right=%d bottom=%d";
	char strx[256];
	PAINTSTRUCT paint;
	RECT rt;
	LPCSTR str = "�L�ł��킩��v���O���~���O\n�H��N�F ����\n"
		"�킩��₷���Ă��߂ɂȂ�I";

	GetClientRect(hWnd, &rt);
	wsprintf((LPSTR)strx, (LPCSTR)str_org, rt.left, rt.top, rt.right, rt.bottom);
	rt.top += 40;
	rt.bottom -= 40;
	rt.right -= 40;
	rt.left += 40;
	hdc = BeginPaint(hWnd, &paint);
	SetBkColor(hdc, RGB(128, 128, 128));
	SetTextColor(hdc, RGB(255, 0, 0));
	TextOut(hdc, 10, 10, (LPSTR)strx, strlen(strx));
	SetTextColor(hdc, RGB(0, 0, 255));
	DrawText(hdc, str, -1, &rt, DT_WORDBREAK);
	EndPaint(hWnd, &paint);
	return;
}
