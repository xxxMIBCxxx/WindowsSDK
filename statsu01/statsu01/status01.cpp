// status.cpp
#define STRICT
#include <windows.h>
#include <commctrl.h>    //�R�����R���g���[���̂��ߕK�v
#include "resource.h"    //���͂Ń��\�[�X�X�N���v�g�������l�͎����̃w�b�_�[�t�@�C��

#define ID_STATUS       100
#define ID_MYTIMER      32767

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
HWND CreateMyStatus(HWND, HINSTANCE);    //�X�e�[�^�X�o�[�쐬�֐�

char szClassName[] = "status01";        //�E�B���h�E�N���X

HWND hStatus;    //�X�e�[�^�X�o�[�̃E�B���h�E�n���h��

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


// �E�B���h�E�E�N���X�̓o�^
BOOL InitApp(HINSTANCE hInst)
{
    WNDCLASS wc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;           // �v���V�[�W����
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;               // �C���X�^���X
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = "MYMENU";         // ���j���[��
    wc.lpszClassName = (LPCSTR)szClassName;
    return (RegisterClass(&wc));
}


// �E�B���h�E�̐���
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
    HWND hWnd;

    hWnd = CreateWindow(szClassName,
        "�L�ł��킩��X�e�[�^�X�p�[",   // �^�C�g���o�[�ɂ��̖��O���\������܂�
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


// �E�B���h�E�v���V�[�W��

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    int id;
    char str[256];
    const char* str_org = "������%2d��%2d��%2d�b�ł�";
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
            (LPCSTR)"�I�����Ă��悢�ł���",
            (LPCSTR)"�I���m�F",
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
    // �R�����R���g���[����dll��������
    InitCommonControls();

    // �X�e�[�^�X�o�[���쐬
    hStatus = CreateWindowEx(
        0,                                                          // �g���X�^�C��
        STATUSCLASSNAME,                                            // �E�B���h�E�N���X(���X�e�[�^�X�o�[���쐬����ꍇ�́A�E�B���h�E�N���X�����uSTATUSCLASSNAME�v�ɂ���)
        NULL,                                                       // �^�C�g��
        WS_CHILD | SBARS_SIZEGRIP | CCS_BOTTOM | WS_VISIBLE,        // �E�B���h�E�X�^�C���iSBS_SIZEGRIP�F�E�B���h�E�̉E���ɂ���΂߂̂R�{�̐��j
                                                                    // ��WS_VISIBLE���w�肵�Ȃ��Ƃ��͕K��ShowWindow�֐����Ă�
        0,                                                          // �w���W
        0,                                                          // �x���W
        0,                                                          // �E�B���h�E��
        0,                                                          // ����
        hWnd,                                                       // �e�E�B���h�E
        (HMENU)ID_STATUS,                                           // �X�e�[�^�X�o�[�̂h�c
        hInst,                                                      // �C���X�^���X�n���h��
        NULL);

    // �X�e�[�^�X�o�[�ɍׂ����w�����o��
    SendMessage(hStatus, SB_SIMPLE, TRUE, 0L);
    
    return hStatus;
}

