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
HINSTANCE hInst1;                           // �C���X�^���X�n���h��

char time_str[256] = "123";

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst, LPSTR lpsCmdLine, int nCmdShow)
{
    MSG msg;
    char szClassName[] = "timer";           // �E�B���h�E�N���X
    hInst1 = hCurInst;                      // �O���[�o���ϐ��ɃR�s�[

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


// �E�B���h�E�E�N���X�̓o�^�@
BOOL InitApp(HINSTANCE hInst, LPCSTR szClassName)
{
    WNDCLASS wc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;                   // �v���V�[�W����
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;                       // �C���X�^���X
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL/*"TIMERMENU"*/;      // ���j���[��
    wc.lpszClassName = (LPCSTR)szClassName;
    return (RegisterClass(&wc));
}


// �E�B���h�E�̐���
BOOL InitInstance(HINSTANCE hInst, LPCSTR szClassName, int nCmdShow)
{
    HWND hWnd;
    HMENU hMenu;
    int i;

    hWnd = CreateWindow(szClassName,
        NULL,                           // �^�C�g���o�[�ɂ��̖��O���\������܂�
        WS_CAPTION | WS_SYSMENU,        // �E�B���h�E�̎��
        9999,                           // �w���W
        9999,                           // �x���W
        0,                              // ��
        0,                              // ����
        NULL,                           // �e�E�B���h�E�̃n���h���A�e�����Ƃ���NULL
        NULL,                           // ���j���[�n���h���A�N���X���j���[���g���Ƃ���NULL
        hInst,                          // �C���X�^���X�n���h��
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
    AppendMenu(hMenu, MF_STRING, IDM_OPTION, "�I�v�V����");
    DrawMenuBar(hWnd);
    
    return TRUE;
}


// �E�B���h�E�v���V�[�W��
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
                (LPCSTR)"�^�C�}�[���s�I",
                (LPCSTR)"���s",
                MB_OK | MB_ICONEXCLAMATION);
        }
        break;
    case WM_TIMER:
        GetTimeStr();
        SetWindowText(hWnd, (LPCSTR)time_str);
        break;
    case WM_CLOSE:
        id = MessageBox(hWnd,
            (LPCSTR)"�I�����Ă��悢�ł���",
            (LPCSTR)"�I���m�F",
            MB_YESNO | MB_ICONQUESTION);
        if (id == IDYES) {
            if (KillTimer(hWnd, ID_MYTIMER) == TRUE) {
                MessageBox(hWnd,
                    (LPCSTR)"�^�C�}�[���E���܂����I",
                    (LPCSTR)"�^�C�}�[�폜�̐���",
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
    const char* str_org = "%2d��%2d��%2d�b";

    time_t long_time;
    struct tm* now_time;
    time(&long_time);
    now_time = localtime(&long_time);
    sprintf(time_str, str_org, now_time->tm_hour, now_time->tm_min, now_time->tm_sec);
    
    return 0;
}