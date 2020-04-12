// status.cpp
#define STRICT
#include <windows.h>
#include <commctrl.h>    //コモンコントロールのため必要
#include "resource.h"    //自力でリソーススクリプトを書く人は自分のヘッダーファイル

#define ID_STATUS       100
#define ID_MYTIMER      32767

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
HWND CreateMyStatus(HWND, HINSTANCE);    //ステータスバー作成関数

char szClassName[] = "status01";        //ウィンドウクラス

HWND hStatus;    //ステータスバーのウィンドウハンドル

#pragma comment(lib,"Comctl32.lib")


int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
    LPSTR lpsCmdLine, int nCmdShow)
{
    MSG msg;

    if (!hPrevInst) {
        if (!InitApp(hCurInst))
            return FALSE;
    }
    if (!InitInstance(hCurInst, nCmdShow)) {
        return FALSE;
    }
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}


// ウィンドウ・クラスの登録
BOOL InitApp(HINSTANCE hInst)
{
    WNDCLASS wc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;           // プロシージャ名
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;               // インスタンス
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = "MYMENU";         // メニュー名
    wc.lpszClassName = (LPCSTR)szClassName;
    return (RegisterClass(&wc));
}


// ウィンドウの生成
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
    HWND hWnd;

    hWnd = CreateWindow(szClassName,
        "猫でもわかるステータスパー",   // タイトルバーにこの名前が表示されます
        WS_OVERLAPPEDWINDOW,            // ウィンドウの種類
        CW_USEDEFAULT,                  // Ｘ座標
        CW_USEDEFAULT,                  // Ｙ座標
        CW_USEDEFAULT,                  // 幅
        CW_USEDEFAULT,                  // 高さ
        NULL,                           // 親ウィンドウのハンドル、親を作るときはNULL
        NULL,                           // メニューハンドル、クラスメニューを使うときはNULL
        hInst,                          // インスタンスハンドル
        NULL);
    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return TRUE;
}


// ウィンドウプロシージャ

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    int id;
    char str[256];
    const char* str_org = "ただ今%2d時%2d分%2d秒です";
    SYSTEMTIME STime;
    static HINSTANCE hInst;
    hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
    static HMENU hMenu;
    hMenu = GetMenu(hWnd);

    switch (msg) {
    case WM_CREATE:
        CreateMyStatus(hWnd, hInst);
        SetTimer(hWnd, ID_MYTIMER, 300, NULL);
        EnableMenuItem(hMenu, IDM_ON, MF_GRAYED);
        break;
    case WM_TIMER:
        GetLocalTime(&STime);
        wsprintf(str, str_org, STime.wHour, STime.wMinute, STime.wSecond);
        SendMessage(hStatus, SB_SETTEXT, 255 | 0, (WPARAM)(LPSTR)str);
        break;
    case WM_SIZE:
        SendMessage(hStatus, WM_SIZE, wp, lp);
        break;
    case WM_COMMAND:
        switch (LOWORD(wp)) {
        case IDM_END:
            SendMessage(hWnd, WM_CLOSE, 0L, 0L);
            break;
        case IDM_ON:
            ShowWindow(hStatus, SW_SHOW);
            EnableMenuItem(hMenu, IDM_ON, MF_GRAYED);
            EnableMenuItem(hMenu, IDM_OFF, MF_ENABLED);
            break;
        case IDM_OFF:
            ShowWindow(hStatus, SW_HIDE);
            EnableMenuItem(hMenu, IDM_OFF, MF_GRAYED);
            EnableMenuItem(hMenu, IDM_ON, MF_ENABLED);
        }
        break;
    case WM_CLOSE:
        id = MessageBox(hWnd,
            (LPCSTR)"終了してもよいですか",
            (LPCSTR)"終了確認",
            MB_YESNO | MB_ICONQUESTION);
        if (id == IDYES) {
            DestroyWindow(hWnd);
        }
        break;
    case WM_DESTROY:
        KillTimer(hWnd, ID_MYTIMER);
        PostQuitMessage(0);
        break;
    default:
        return (DefWindowProc(hWnd, msg, wp, lp));
    }
    return 0L;
}


HWND CreateMyStatus(HWND hWnd, HINSTANCE hInst)
{
    // コモンコントロールのdllを初期化
    InitCommonControls();

    // ステータスバーを作成
    hStatus = CreateWindowEx(
        0,                                                          // 拡張スタイル
        STATUSCLASSNAME,                                            // ウィンドウクラス(※ステータスバーを作成する場合は、ウィンドウクラス名を「STATUSCLASSNAME」にする)
        NULL,                                                       // タイトル
        WS_CHILD | SBARS_SIZEGRIP | CCS_BOTTOM | WS_VISIBLE,        // ウィンドウスタイル（SBS_SIZEGRIP：ウィンドウの右下にある斜めの３本の線）
                                                                    // ※WS_VISIBLEを指定しないときは必ずShowWindow関数を呼ぶ
        0,                                                          // Ｘ座標
        0,                                                          // Ｙ座標
        0,                                                          // ウィンドウ幅
        0,                                                          // 高さ
        hWnd,                                                       // 親ウィンドウ
        (HMENU)ID_STATUS,                                           // ステータスバーのＩＤ
        hInst,                                                      // インスタンスハンドル
        NULL);

    // ステータスバーに細かい指示を出す
    SendMessage(hStatus, SB_SIMPLE, TRUE, 0L);
    
    return hStatus;
}

