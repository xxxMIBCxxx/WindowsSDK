// custom01.cpp

#ifndef STRICT
#define STRICT
#endif

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
HWND MakeMyList(HWND);
void InsertMyColumn(HWND);

char szClassName[] = "custom01";    //�E�B���h�E�N���X
BOOL bCustom = FALSE;

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
    LPSTR lpsCmdLine, int nCmdShow)
{
    MSG msg;

    if (!InitApp(hCurInst))
        return FALSE;
    if (!InitInstance(hCurInst, nCmdShow))
        return FALSE;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

//�E�B���h�E�E�N���X�̓o�^

ATOM InitApp(HINSTANCE hInst)
{
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;    //�v���V�[�W����
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;//�C���X�^���X
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = "MYMENU";    //���j���[��
    wc.lpszClassName = (LPCSTR)szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    return (RegisterClassEx(&wc));
}


//�E�B���h�E�̐���
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
    HWND hWnd;

    hWnd = CreateWindow(szClassName,
        "�L�ł��킩��J�X�^���h���[",       // �^�C�g���o�[�ɂ��̖��O���\������܂�
        WS_OVERLAPPEDWINDOW,                // �E�B���h�E�̎��
        CW_USEDEFAULT,                      // �w���W
        CW_USEDEFAULT,                      // �x���W
        CW_USEDEFAULT,                      // ��
        CW_USEDEFAULT,                      // ����
        NULL,                               // �e�E�B���h�E�̃n���h���A�e�����Ƃ���NULL
        NULL,                               // ���j���[�n���h���A�N���X���j���[���g���Ƃ���NULL
        hInst,                              // �C���X�^���X�n���h��
        NULL);
    if (!hWnd)
        return FALSE;
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return TRUE;
}


// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    int id;
    static HWND hList;
    HINSTANCE hInst;
    INITCOMMONCONTROLSEX ic;
    LPNMHDR lpnmhdr;
    LPNMLISTVIEW lplv;
    LPNMLVCUSTOMDRAW lplvcd;
    MENUITEMINFO mii;
    static HMENU hMenu;
    static HFONT hCustomFont, hOrgFont;

    switch (msg) {
    case WM_CREATE:
        ic.dwICC = ICC_LISTVIEW_CLASSES;
        ic.dwSize = sizeof(INITCOMMONCONTROLSEX);
        InitCommonControlsEx(&ic);
        hList = MakeMyList(hWnd);
        InsertMyColumn(hList);
        hMenu = GetMenu(hWnd);
        hCustomFont = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, SHIFTJIS_CHARSET,
            OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
            "�c�e������");
        hOrgFont = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, SHIFTJIS_CHARSET,
            OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
            "system");
        SendMessage(hList, WM_SETFONT, (WPARAM)hOrgFont, (LPARAM)MAKELPARAM(FALSE, 0));
        break;
    case WM_COMMAND:
        switch (LOWORD(wp)) {
        case IDM_END:
            SendMessage(hWnd, WM_CLOSE, 0, 0);
            break;
        case IDM_WRITE:
            hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
            DialogBoxParam(hInst, "MYDLG", hWnd, (DLGPROC)MyDlgProc, (LPARAM)hList);
            break;
        case IDM_CUSTOM:
            memset(&mii, 0, sizeof(MENUITEMINFO));
            mii.cbSize = sizeof(MENUITEMINFO);
            mii.fMask = MIIM_STATE;
            if (bCustom == FALSE)
                mii.fState = MFS_CHECKED;
            else
                mii.fState = MFS_UNCHECKED;
            SetMenuItemInfo(hMenu, IDM_CUSTOM, FALSE, &mii);
            bCustom = !bCustom;
            InvalidateRect(hList, NULL, TRUE);
            break;
        }
        break;
    case WM_NOTIFY:
        lpnmhdr = (LPNMHDR)lp;
        if (lpnmhdr->hwndFrom == hList && bCustom) {
            lplv = (LPNMLISTVIEW)lp;
            if (lplv->hdr.code == NM_CUSTOMDRAW) {
                lplvcd = (LPNMLVCUSTOMDRAW)lp;
                if (lplvcd->nmcd.dwDrawStage == CDDS_PREPAINT)
                    return CDRF_NOTIFYITEMDRAW;
                if (lplvcd->nmcd.dwDrawStage == CDDS_ITEMPREPAINT) {
                    if (ListView_GetCheckState(hList, lplvcd->nmcd.dwItemSpec)) {
                        SelectObject(lplvcd->nmcd.hdc, hCustomFont);
                        lplvcd->clrTextBk = RGB(255, 255, 0);
                        lplvcd->clrText = RGB(0, 0, 255);
                        return CDRF_NEWFONT;
                    }
                }
                break;
            }
        }
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
            DeleteObject(hOrgFont);
            DeleteObject(hCustomFont);
            DestroyWindow(hList);
            DestroyWindow(hWnd);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return (DefWindowProc(hWnd, msg, wp, lp));
    }
    return 0;
}


HWND MakeMyList(HWND hWnd)
{
    HWND hList;
    DWORD dwStyle;
    HINSTANCE hInst;

    hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);

    hList = CreateWindowEx(0, WC_LISTVIEW, "",
        WS_CHILD | WS_VISIBLE | LVS_REPORT,
        0, 0, 0, 0, hWnd, (HMENU)100, hInst, NULL);
    dwStyle = ListView_GetExtendedListViewStyle(hList);
    dwStyle |= LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT |
        LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP;
    ListView_SetExtendedListViewStyle(hList, dwStyle);
    return hList;
}

void InsertMyColumn(HWND hList)
{
    LVCOLUMN lvcol;

    lvcol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvcol.fmt = LVCFMT_LEFT;
    lvcol.cx = 100;
    lvcol.pszText = (LPSTR)"���O";
    lvcol.iSubItem = 0;
    ListView_InsertColumn(hList, 0, &lvcol);

    lvcol.cx = 50;
    lvcol.pszText = (LPSTR)"����";
    lvcol.iSubItem = 1;
    ListView_InsertColumn(hList, 1, &lvcol);

    lvcol.cx = 200;
    lvcol.pszText = (LPSTR)"�Z��";
    lvcol.iSubItem = 2;
    ListView_InsertColumn(hList, 2, &lvcol);

    return;
}


LRESULT CALLBACK MyDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    static HWND hList;
    int nCount;
    LVITEM li;
    char szName[32], szAddress[256];

    switch (msg) {
    case WM_INITDIALOG:
        hList = (HWND)lp;
        Button_SetCheck(GetDlgItem(hDlg, IDC_RADIO1), BST_CHECKED);
        return TRUE;
    case WM_COMMAND:
        switch (LOWORD(wp)) {
        case IDOK:
            nCount = ListView_GetItemCount(hList);
            memset(&li, 0, sizeof(LVITEM));
            li.mask = LVIF_TEXT;
            li.iItem = nCount;
            li.iSubItem = 0;
            Edit_GetText(GetDlgItem(hDlg, IDC_EDIT1), szName, sizeof(szName));
            li.pszText = szName;
            ListView_InsertItem(hList, &li);

            li.iSubItem = 1;
            if (Button_GetCheck(GetDlgItem(hDlg, IDC_RADIO1)) == BST_CHECKED)
                li.pszText = (LPSTR)"�j";
            if (Button_GetCheck(GetDlgItem(hDlg, IDC_RADIO2)) == BST_CHECKED)
                li.pszText = (LPSTR)"��";
            ListView_SetItem(hList, &li);

            li.iSubItem = 2;
            Edit_GetText(GetDlgItem(hDlg, IDC_EDIT2), szAddress, sizeof(szAddress));
            li.pszText = szAddress;
            ListView_SetItem(hList, &li);

            Edit_SetText(GetDlgItem(hDlg, IDC_EDIT1), "");
            Edit_SetText(GetDlgItem(hDlg, IDC_EDIT2), "");

            SetFocus(GetDlgItem(hDlg, IDC_EDIT1));
            return TRUE;
        case IDCANCEL:
            EndDialog(hDlg, IDCANCEL);
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}