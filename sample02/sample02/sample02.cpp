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

		// ウィンドウの登録
		if (!RegisterClass(&myProg))
		{
			return FALSE;
		}
	}

	// ウィンドウの作成
	hWnd = CreateWindow(szClassName,			// クラス名
		"猫でもわかるプログラミング",			// ウィンドウの名前
		WS_OVERLAPPEDWINDOW,					// ウィンドウスタイル
		CW_USEDEFAULT,							// X座標
		CW_USEDEFAULT,							// Y座標
		CW_USEDEFAULT,							// ウィンドウの横幅
		CW_USEDEFAULT,							// ウィンドウの高さ
		NULL,									// 親ウィンドウハンドル（親ウィンドウを作る時はNULL）
		NULL,									// メニューハンドル（クラスメニューの時はNULL）
		hInstance,								// インスタンスハンドル
		NULL);									// ウィンドウ作成データ

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
	LPCSTR str = "猫でもわかるプログラミング\n粂井康孝 制作\n"
		"わかりやすくてためになる！";

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
