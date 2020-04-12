// listvw01.cpp

#define STRICT
#define ID_LISTVIEW         100

#include <windows.h>
#include <commctrl.h>


#pragma comment(lib,"comctl32.lib")


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

char szClassName[] = "listvw01";        //ウィンドウクラス
HINSTANCE hInst;

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst, LPSTR lpsCmdLine, int nCmdShow)
{
    MSG msg;

    if (!InitApp(hCurInst))
    {
        return FALSE;
    }
    
    if (!InitInstance(hCurInst, nCmdShow))
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
BOOL InitApp(HINSTANCE hInst)
{
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;                               // プロシージャ名
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;                                   // インスタンス
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;                                 // メニュー名
    wc.lpszClassName = (LPCSTR)szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    return (RegisterClassEx(&wc));
}


// ウィンドウの生成
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND hWnd;
    hInst = hInstance;
    hWnd = CreateWindow(szClassName,
        "猫でもわかるリストビュー",     // タイトルバーにこの名前が表示されます
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


//ウィンドウプロシージャ

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    int id;
    static HWND         hList;
    LV_COLUMN           lvcol;
    LV_ITEM             item;

    switch (msg) {
    case WM_CREATE:
        InitCommonControls();
        hList = CreateWindowEx(0,
            WC_LISTVIEW, "",
            WS_CHILD | WS_VISIBLE | LVS_REPORT,
            0, 0, 0, 0,
            hWnd,
            (HMENU)ID_LISTVIEW,
            hInst,
            NULL);

        lvcol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
        lvcol.fmt = LVCFMT_LEFT;
        lvcol.cx = 100;
        lvcol.pszText = (LPSTR)"名前";
        lvcol.iSubItem = 0;
        ListView_InsertColumn(hList, 0, &lvcol);

        lvcol.cx = 200;
        lvcol.pszText = (LPSTR)"住所";
        lvcol.iSubItem = 1;
        ListView_InsertColumn(hList, 1, &lvcol);

        item.mask = LVIF_TEXT;
        item.pszText = (LPSTR)"粂井康孝";
        item.iItem = 0;
        item.iSubItem = 0;
        ListView_InsertItem(hList, &item);

        item.pszText = (LPSTR)"北海道旭川市";
        item.iItem = 0;
        item.iSubItem = 1;
        ListView_SetItem(hList, &item);

        item.pszText = (LPSTR)"粂井ひとみ";
        item.iItem = 1;
        item.iSubItem = 0;
        ListView_InsertItem(hList, &item);

        item.pszText = (LPSTR)"東京都千代田区";
        item.iItem = 1;
        item.iSubItem = 1;
        ListView_SetItem(hList, &item);

        item.pszText = (LPSTR)"粂井志麻";
        item.iItem = 2;
        item.iSubItem = 0;
        ListView_InsertItem(hList, &item);

        item.pszText = (LPSTR)"北海道中富良野町";
        item.iItem = 2;
        item.iSubItem = 1;
        ListView_SetItem(hList, &item);

        break;
    case WM_SIZE:
        MoveWindow(hList, 0, 0, LOWORD(lp), HIWORD(lp), TRUE);
        break;
    case WM_CLOSE:
        id = MessageBox(hWnd,
            "終了してもよいですか",
            "終了確認",
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

