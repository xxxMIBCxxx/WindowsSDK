// listvw01.cpp

#define STRICT
#define ID_LISTVIEW         100

#include <windows.h>
#include <commctrl.h>


#pragma comment(lib,"comctl32.lib")


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

char szClassName[] = "listvw01";        //�E�B���h�E�N���X
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

// �E�B���h�E�E�N���X�̓o�^
BOOL InitApp(HINSTANCE hInst)
{
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;                               // �v���V�[�W����
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;                                   // �C���X�^���X
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;                                 // ���j���[��
    wc.lpszClassName = (LPCSTR)szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    return (RegisterClassEx(&wc));
}


// �E�B���h�E�̐���
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND hWnd;
    hInst = hInstance;
    hWnd = CreateWindow(szClassName,
        "�L�ł��킩�郊�X�g�r���[",     // �^�C�g���o�[�ɂ��̖��O���\������܂�
        WS_OVERLAPPEDWINDOW,            // �E�B���h�E�̎��
        CW_USEDEFAULT,                  // �w���W
        CW_USEDEFAULT,                  // �x���W
        CW_USEDEFAULT,                  // ��
        CW_USEDEFAULT,                  // ����
        NULL,                           // �e�E�B���h�E�̃n���h���A�e�����Ƃ���NULL
        NULL,                           // ���j���[�n���h���A�N���X���j���[���g���Ƃ���NULL
        hInst,                          // �C���X�^���X�n���h��
        NULL);
    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}


//�E�B���h�E�v���V�[�W��

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
        lvcol.pszText = (LPSTR)"���O";
        lvcol.iSubItem = 0;
        ListView_InsertColumn(hList, 0, &lvcol);

        lvcol.cx = 200;
        lvcol.pszText = (LPSTR)"�Z��";
        lvcol.iSubItem = 1;
        ListView_InsertColumn(hList, 1, &lvcol);

        item.mask = LVIF_TEXT;
        item.pszText = (LPSTR)"�H��N�F";
        item.iItem = 0;
        item.iSubItem = 0;
        ListView_InsertItem(hList, &item);

        item.pszText = (LPSTR)"�k�C������s";
        item.iItem = 0;
        item.iSubItem = 1;
        ListView_SetItem(hList, &item);

        item.pszText = (LPSTR)"�H��ЂƂ�";
        item.iItem = 1;
        item.iSubItem = 0;
        ListView_InsertItem(hList, &item);

        item.pszText = (LPSTR)"�����s���c��";
        item.iItem = 1;
        item.iSubItem = 1;
        ListView_SetItem(hList, &item);

        item.pszText = (LPSTR)"�H��u��";
        item.iItem = 2;
        item.iSubItem = 0;
        ListView_InsertItem(hList, &item);

        item.pszText = (LPSTR)"�k�C�����x�ǖ쒬";
        item.iItem = 2;
        item.iSubItem = 1;
        ListView_SetItem(hList, &item);

        break;
    case WM_SIZE:
        MoveWindow(hList, 0, 0, LOWORD(lp), HIWORD(lp), TRUE);
        break;
    case WM_CLOSE:
        id = MessageBox(hWnd,
            "�I�����Ă��悢�ł���",
            "�I���m�F",
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

