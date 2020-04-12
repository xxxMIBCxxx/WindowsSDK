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
int nFont = 1;                      // �I�����ꂽ�t�H���g 1:�����@2:�S�V�b�N
int nCol = 1;                       // �I������Ă���F�@1:�ԁ@2:�� 

LPCSTR szClassName = "font02";      // �N���X��

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


// �E�B���h�E�E�N���X�̓o�^
BOOL InitApp(HINSTANCE hInst)
{
    WNDCLASS wc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;    // �v���V�[�W����
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;        // �C���X�^���X
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;     // ���j���[��
    wc.lpszClassName = szClassName;
    return (RegisterClass(&wc));
}


// �E�B���h�E�̐���
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
    HWND hWnd;

    hWnd = CreateWindow(szClassName,
        "�L�ł��킩��t�H���g",     // �^�C�g���o�[�ɂ��̖��O���\������܂�
        WS_OVERLAPPEDWINDOW,        // �E�B���h�E�̎��
        CW_USEDEFAULT,              // �w���W
        CW_USEDEFAULT,              // �x���W
        CW_USEDEFAULT,              // ��
        CW_USEDEFAULT,              // ����
        NULL,                       // �e�E�B���h�E�̃n���h���A�e�����Ƃ���NULL
        NULL,                       // ���j���[�n���h���A�N���X���j���[���g���Ƃ���NULL
        hInst,                      // �C���X�^���X�n���h��
        NULL);
    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);
    
    return TRUE;
}


// �E�B���h�E�v���V�[�W��
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
            "BUTTON", "����",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            20, 20, 100, 30, hWnd, (HMENU)ID_MI, hInst, NULL);
        hButtonWnd2 = CreateWindow(
            "BUTTON", "�S�V�b�N",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            130, 20, 100, 30, hWnd, (HMENU)ID_GO, hInst, NULL);
        hButtonWnd3 = CreateWindow(
            "BUTTON", "�I��",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            240, 20, 100, 30, hWnd, (HMENU)ID_END, hInst, NULL);
        hButtonWnd5 = CreateWindow(
            "BUTTON", "��",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            20, 60, 100, 30, hWnd, (HMENU)ID_RED, hInst, NULL);
        hButtonWnd6 = CreateWindow(
            "BUTTON", "��",
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
            hFont = SetMyFont(hdc, (LPCTSTR)"�l�r ����");
            hFontOld = (HFONT)SelectObject(hdc, hFont);
            break;
        case 2:
            hFont = SetMyFont(hdc, (LPCTSTR)"�l�r �S�V�b�N");
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
        TextOut(hdc, 10, 120, (LPCTSTR)"�L�ł��킩��t�H���g", 20);
        SelectObject(hdc, hFontOld);
        DeleteObject(hFont);
        EndPaint(hWnd, &ps);
        break;
    case WM_CLOSE:
        id = MessageBox(hWnd,
            (LPCSTR)"�I�����Ă��悢�ł���",
            (LPCSTR)"�I���m�F",
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
    hFont = CreateFont(40,          // �t�H���g����
        0,                          // ������
        0,                          // �e�L�X�g�̊p�x
        0,                          // �x�[�X���C���Ƃ����Ƃ̊p�x
        FW_REGULAR,                 // �t�H���g�̏d���i�����j
        FALSE,                      // �C�^���b�N��
        FALSE,                      // �A���_�[���C��
        FALSE,                      // �ł�������
        SHIFTJIS_CHARSET,           // �����Z�b�g
        OUT_DEFAULT_PRECIS,         // �o�͐��x
        CLIP_DEFAULT_PRECIS,        // �N���b�s���O���x
        PROOF_QUALITY,              // �o�͕i��
        FIXED_PITCH | FF_MODERN,    // �s�b�`�ƃt�@�~���[
        face);                      // ���̖�

    return hFont;
}