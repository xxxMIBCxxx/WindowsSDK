// timer.cpp

#include <windows.h>
#include <time.h>
#include <stdio.h>
#include "timer.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitApp(HINSTANCE, LPCSTR);
BOOL InitInstance(HINSTANCE, LPCSTR, int);

int GetTimeStr(void);
HINSTANCE hInst1;                           // インスタンスハンドル

char time_str[256] = "123";

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst, LPSTR lpsCmdLine, int nCmdShow)
{
    MSG msg;
    char szClassName[] = "timer";           // ウィンドウクラス
    hInst1 = hCurInst;                      // グローバル変数にコピー

    if (!hPrevInst) {
        if (!InitApp(hCurInst, szClassName))
        {
            return FALSE;
        }
    }

    if (!InitInstance(hCurInst, szClassName, nCmdShow)) 
    {
        return FALSE;
    }
    
    while (GetMessage(&msg, NULL, 0, 0)) 
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}


// ウィンドウ・クラスの登録　
BOOL InitApp(HINSTANCE hInst, LPCSTR szClassName)
{
    WNDCLASS wc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;                   // プロシージャ名
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;                       // インスタンス
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL/*"TIMERMENU"*/;      // メニュー名
    wc.lpszClassName = (LPCSTR)szClassName;
    return (RegisterClass(&wc));
}


// ウィンドウの生成
BOOL InitInstance(HINSTANCE hInst, LPCSTR szClassName, int nCmdShow)
{
    HWND hWnd;
    HMENU hMenu;
    int i;

    hWnd = CreateWindow(szClassName,
        NULL,                           // タイトルバーにこの名前が表示されます
        WS_CAPTION | WS_SYSMENU,        // ウィンドウの種類
        9999,                           // Ｘ座標
        9999,                           // Ｙ座標
        0,                              // 幅
        0,                              // 高さ
        NULL,                           // 親ウィンドウのハンドル、親を作るときはNULL
        NULL,                           // メニューハンドル、クラスメニューを使うときはNULL
        hInst,                          // インスタンスハンドル
        NULL);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, SW_SHOW);// SW_MINIMIZE/*nCmdShow*/);
    UpdateWindow(hWnd);

    hMenu = GetSystemMenu(hWnd, FALSE);
    for (i = 0; i <= 5; i++)
    {
        DeleteMenu(hMenu, 0, MF_BYPOSITION);
    }
    AppendMenu(hMenu, MF_STRING, IDM_OPTION, "オプション");
    DrawMenuBar(hWnd);
    
    return TRUE;
}


// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    int id;

    switch (msg) {
    case WM_SYSCOMMAND:
        switch (wp) {
        case IDM_OPTION:
            DialogBox(hInst1, "OPTDLG", hWnd, (DLGPROC)MyDlgProc);
            break;
        default:
            return(DefWindowProc(hWnd, msg, wp, lp));
            break;
        }
        break;
    case WM_CREATE:
        if (SetTimer(hWnd, ID_MYTIMER, 1000, NULL) == 0) {
            MessageBox(hWnd,
                (LPCSTR)"タイマー失敗！",
                (LPCSTR)"失敗",
                MB_OK | MB_ICONEXCLAMATION);
        }
        break;
    case WM_TIMER:
        GetTimeStr();
        SetWindowText(hWnd, (LPCSTR)time_str);
        break;
    case WM_CLOSE:
        id = MessageBox(hWnd,
            (LPCSTR)"終了してもよいですか",
            (LPCSTR)"終了確認",
            MB_YESNO | MB_ICONQUESTION);
        if (id == IDYES) {
            if (KillTimer(hWnd, ID_MYTIMER) == TRUE) {
                MessageBox(hWnd,
                    (LPCSTR)"タイマーを殺しました！",
                    (LPCSTR)"タイマー削除の成功",
                    MB_OK | MB_ICONEXCLAMATION);
            }
            DestroyWindow(hWnd);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return (DefWindowProc(hWnd, msg, wp, lp));
    }

    return 0L;
}


LRESULT CALLBACK MyDlgProc(HWND hDlgWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg) {
    case WM_INITDIALOG:
        return FALSE;
    case WM_COMMAND:
        switch (LOWORD(wp)) {
        case IDOK:
            EndDialog(hDlgWnd, IDOK);
            break;
        case IDCANCEL:
            EndDialog(hDlgWnd, IDCANCEL);
            break;
        default:
            return FALSE;
        }
    default:
        return FALSE;
    }

    return TRUE;
}


int GetTimeStr(void)
{
    const char* str_org = "%2d時%2d分%2d秒";

    time_t long_time;
    struct tm* now_time;
    time(&long_time);
    now_time = localtime(&long_time);
    sprintf(time_str, str_org, now_time->tm_hour, now_time->tm_min, now_time->tm_sec);
    
    return 0;
}