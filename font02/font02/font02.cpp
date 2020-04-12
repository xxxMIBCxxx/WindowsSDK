// font02.cpp

#include <windows.h>

#define ID_MI       1000
#define ID_GO       1100
#define ID_END      1200
#define ID_RED      1300
#define ID_BLUE     1400

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

HFONT SetMyFont(HDC, LPCTSTR);
int nFont = 1;                      // 選択されたフォント 1:明朝　2:ゴシック
int nCol = 1;                       // 選択されている色　1:赤　2:青 

LPCSTR szClassName = "font02";      // クラス名

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
    LPSTR lpsCmdLine, int nCmdShow)
{
    MSG msg;

    if (!hPrevInst) {
        if (!InitApp(hCurInst))
            return FALSE;
    }
    if (!InitInstance(hCurInst, nCmdShow)) 
    {
        return FALSE;
    }
    
    while (GetMessage(&msg, NULL, NULL, NULL)) 
    {
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
    wc.lpfnWndProc = WndProc;    // プロシージャ名
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;        // インスタンス
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;     // メニュー名
    wc.lpszClassName = szClassName;
    return (RegisterClass(&wc));
}


// ウィンドウの生成
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
    HWND hWnd;

    hWnd = CreateWindow(szClassName,
        "猫でもわかるフォント",     // タイトルバーにこの名前が表示されます
        WS_OVERLAPPEDWINDOW,        // ウィンドウの種類
        CW_USEDEFAULT,              // Ｘ座標
        CW_USEDEFAULT,              // Ｙ座標
        CW_USEDEFAULT,              // 幅
        CW_USEDEFAULT,              // 高さ
        NULL,                       // 親ウィンドウのハンドル、親を作るときはNULL
        NULL,                       // メニューハンドル、クラスメニューを使うときはNULL
        hInst,                      // インスタンスハンドル
        NULL);
    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);
    
    return TRUE;
}


// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    int id;
    HDC hdc;
    HFONT hFont = NULL;
    HFONT hFontOld = NULL;
    PAINTSTRUCT ps;
    HWND hButtonWnd1, hButtonWnd2, hButtonWnd3, hButtonWnd4, hButtonWnd5, hButtonWnd6;
    HINSTANCE hInst;

    hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
    switch (msg) {
    case WM_CREATE:
        hButtonWnd1 = CreateWindow(
            "BUTTON", "明朝",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            20, 20, 100, 30, hWnd, (HMENU)ID_MI, hInst, NULL);
        hButtonWnd2 = CreateWindow(
            "BUTTON", "ゴシック",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            130, 20, 100, 30, hWnd, (HMENU)ID_GO, hInst, NULL);
        hButtonWnd3 = CreateWindow(
            "BUTTON", "終了",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            240, 20, 100, 30, hWnd, (HMENU)ID_END, hInst, NULL);
        hButtonWnd5 = CreateWindow(
            "BUTTON", "赤",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            20, 60, 100, 30, hWnd, (HMENU)ID_RED, hInst, NULL);
        hButtonWnd6 = CreateWindow(
            "BUTTON", "青",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            130, 60, 100, 30, hWnd, (HMENU)ID_BLUE, hInst, NULL);
        break;
    case WM_COMMAND:
        switch (LOWORD(wp)) {
        case ID_MI:
            nFont = 1;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case ID_GO:
            nFont = 2;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case ID_RED:
            nCol = 1;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case ID_BLUE:
            nCol = 2;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case ID_END:
            SendMessage(hWnd, WM_CLOSE, 0, 0L);
            break;
        }
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        switch (nFont) {
        case 1:
            hFont = SetMyFont(hdc, (LPCTSTR)"ＭＳ 明朝");
            hFontOld = (HFONT)SelectObject(hdc, hFont);
            break;
        case 2:
            hFont = SetMyFont(hdc, (LPCTSTR)"ＭＳ ゴシック");
            hFontOld = (HFONT)SelectObject(hdc, hFont);
            break;
        }
        switch (nCol) {
        case 1:
            SetTextColor(hdc, RGB(255, 0, 0));
            break;
        case 2:
            SetTextColor(hdc, RGB(0, 0, 255));
            break;
        }
        TextOut(hdc, 10, 120, (LPCTSTR)"猫でもわかるフォント", 20);
        SelectObject(hdc, hFontOld);
        DeleteObject(hFont);
        EndPaint(hWnd, &ps);
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
        PostQuitMessage(0);
        break;
    default:
        return (DefWindowProc(hWnd, msg, wp, lp));
    }
    return 0L;
}

HFONT SetMyFont(HDC hdc, LPCTSTR face)
{
    HFONT hFont;
    hFont = CreateFont(40,          // フォント高さ
        0,                          // 文字幅
        0,                          // テキストの角度
        0,                          // ベースラインとｘ軸との角度
        FW_REGULAR,                 // フォントの重さ（太さ）
        FALSE,                      // イタリック体
        FALSE,                      // アンダーライン
        FALSE,                      // 打ち消し線
        SHIFTJIS_CHARSET,           // 文字セット
        OUT_DEFAULT_PRECIS,         // 出力精度
        CLIP_DEFAULT_PRECIS,        // クリッピング精度
        PROOF_QUALITY,              // 出力品質
        FIXED_PITCH | FF_MODERN,    // ピッチとファミリー
        face);                      // 書体名

    return hFont;
}