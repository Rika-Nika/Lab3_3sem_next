// Lab_4_1_Sort.cpp : Определяет точку входа для приложения.
//
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <io.h>
#include <stdio.h>
#include "framework.h"
#include "Lab3_3sem_next.hpp"
#include"WindowHelper.hpp"
constexpr auto MAX_LOADSTRING = 100;

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

LPCWSTR SMALL_FILE = L"Matrix1";
LPCWSTR MEDIUM_FILE = L"Matrix2";
LPCWSTR LARGE_FILE = L"Matrix3";

Alg alg = Alg::Alg1;
Matrix matrix = Matrix::Matrix1;

HWND hStartButton = nullptr;

//ИД
HWND hGrpButtonsID = nullptr;
HWND hLoadButton = nullptr;
HWND hLoadPathButton = nullptr;
HWND hGeneratorButton = nullptr;

HWND hGrpButtonsLength = nullptr;
HWND hFile1Button = nullptr;
HWND hFile2Button = nullptr;
HWND hFile3Button = nullptr;

HWND hStartVertButton = nullptr;
HWND hEndVertButton = nullptr;



//Алгоритм 1
HWND hGrpButtonsAlg1 = nullptr;
HWND hAlg1Button = nullptr;
HWND hAlg2Button = nullptr;
HWND hAlg3Button = nullptr;

HWND hOutputButton0 = nullptr;
HWND hOutputButton1 = nullptr;
HWND hOutputButton2 = nullptr;


// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB41SORT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB41SORT));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return static_cast<int>(msg.wParam);
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB41SORT));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 0);
    wcex.lpszMenuName = nullptr;// (IDC_LAB41SORT);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

    HWND hWnd = CreateWindowW(szWindowClass, L"Лабораторная работа 2", WS_OVERLAPPEDWINDOW,
        250, 250, 1100, 650, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}
//BOOL CreateConsole(void)
//{
//    FreeConsole(); //на всякий случай
//    if (AllocConsole())
//    {
//        int hCrt = _open_osfhandle((long)
//            GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
//        *stdout = *(::_fdopen(hCrt, "w"));
//        ::setvbuf(stdout, NULL, _IONBF, 0);
//        *stderr = *(::_fdopen(hCrt, "w"));
//        ::setvbuf(stderr, NULL, _IONBF, 0);
//        return TRUE;
//    }
//    return FALSE;
//}
//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
    {
        hStartButton = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"Начать тест",      // Button text , 
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 530, 220, 50, hWnd, (HMENU)9999, NULL, NULL);

    		//Длина последовательности
        CreateWindowEx(WS_EX_WINDOWEDGE,
            L"BUTTON",
            L"Матрица смежности:",
            WS_VISIBLE | WS_CHILD | BS_GROUPBOX,// <----BS_GROUPBOX does nothing on the grouping 
            10, 10,
            320, 180,
            hWnd,
            NULL,
            hInst, NULL);
        hFile1Button = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"BUTTON",
            L"Matrix1",
            WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP,  // <---- WS_GROUP group the following radio buttons 1st,2nd button 
            20, 30,
            300, 20,
            hWnd, //<----- Use main window handle
            (HMENU)10001,
            hInst, NULL);

        hFile2Button = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"BUTTON",
            L"Matrix2",
            WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,  // Styles 
            20, 50,
            300, 20,
            hWnd,
            (HMENU)10002,
            hInst, NULL);
        hFile3Button = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"BUTTON",
            L"Matrix3",
            WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,  // Styles 
            20, 70,
            300, 20,
            hWnd,
            (HMENU)10003,
            hInst, NULL);
        SendMessage(hFile1Button, BM_SETCHECK, BST_CHECKED, 0);

        CreateWindowEx(WS_EX_WINDOWEDGE,
            L"Static",
            L"Файл:",
            WS_CHILD | WS_VISIBLE | ES_LEFT | ES_READONLY,
            20, 90,
            40, 20,
            hWnd,
            NULL,
            hInst, NULL);
        hLoadPathButton = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"edit",
            L"Matrix1",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,  // <---- WS_GROUP group the following radio buttons 1st,2nd button 
            80, 90,
            215, 20,
            hWnd, //<----- Use main window handle
            (HMENU)10004,
            hInst, NULL);

        CreateWindowEx(WS_EX_WINDOWEDGE,
            L"Static",
            L"Начальная вершина",
            WS_CHILD | WS_VISIBLE | ES_LEFT | ES_READONLY,
            20, 115,
            200, 20,
            hWnd,
            NULL,
            hInst, NULL);
        hStartVertButton = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"edit",
            L"1",
            WS_VSCROLL | WS_BORDER | WS_VISIBLE | WS_CHILD | ES_MULTILINE,
            205, 115,
            50, 20,
            hWnd, //<----- Use main window handle
            NULL,
            hInst, NULL);
        CreateWindowEx(WS_EX_WINDOWEDGE,
            L"Static",
            L"Начальная вершина",
            WS_CHILD | WS_VISIBLE | ES_LEFT | ES_READONLY,
            20, 140,
            200, 20,
            hWnd,
            NULL,
            hInst, NULL);
        hEndVertButton = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"edit",
            L"5",
            WS_VSCROLL | WS_BORDER | WS_VISIBLE | WS_CHILD | ES_MULTILINE,
            205, 140,
            50, 20,
            hWnd, //<----- Use main window handle
            NULL,
            hInst, NULL);

    		
       	

        //Алгоритм 1
        hGrpButtonsAlg1 = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"BUTTON",
            L"Алгоритм:",
            WS_VISIBLE | WS_CHILD | BS_GROUPBOX,// <----BS_GROUPBOX does nothing on the grouping 
            340, 10,
            320, 110,
            hWnd,
            NULL,
            hInst, NULL);
        hAlg1Button = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"BUTTON",
            L"Дейкстра vs Флойда-Уоршелла",
            WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP,  // <---- WS_GROUP group the following radio buttons 1st,2nd button 
            350, 30,
            300, 20,
            hWnd, //<----- Use main window handle
            (HMENU)10005,
            hInst, NULL);

        //hAlg2Button = CreateWindowEx(WS_EX_WINDOWEDGE,
        //    L"BUTTON",
        //    L"Флойда-Уоршелла",
        //    WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,  // Styles 
        //    350, 50,
        //    305, 20,
        //    hWnd,
        //    (HMENU)10006,
        //    hInst, NULL);
        SendMessage(hAlg1Button, BM_SETCHECK, BST_CHECKED, 0);
        
        
        CreateWindowEx(WS_EX_WINDOWEDGE,
            L"Static",
            L"Консоль 1",
            WS_CHILD | WS_VISIBLE | ES_LEFT | ES_READONLY,
            10, 205,
            220, 30,
            hWnd,
            (HMENU)10007,
            hInst, NULL);
        hOutputButton0 = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"edit",
            L"Нет данных",
            WS_VSCROLL | WS_BORDER | WS_VISIBLE | WS_CHILD | ES_MULTILINE,
            10, 225,
            440, 300,
            hWnd, //<----- Use main window handle
            (HMENU)1008,
            hInst, NULL);
        CreateWindowEx(WS_EX_WINDOWEDGE,
            L"Static",
            L"Консоль 2",
            WS_CHILD | WS_VISIBLE | ES_LEFT | ES_READONLY,
            460, 205,
            300, 30,
            hWnd,
            (HMENU)1009,
            hInst, NULL);
        hOutputButton1 = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"edit",
            L"Нет данных",
            WS_VSCROLL | WS_BORDER | WS_VISIBLE | WS_CHILD | ES_MULTILINE,
            460, 225,
            300, 300,
            hWnd, //<----- Use main window handle
            (HMENU)10010,
            hInst, NULL);

        CreateWindowEx(WS_EX_WINDOWEDGE,
            L"Static",
            L"Консоль 3",
            WS_CHILD | WS_VISIBLE | ES_LEFT | ES_READONLY,
            770, 205,
            300, 30,
            hWnd,
            (HMENU)10011,
            hInst, NULL);
        hOutputButton2 = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"edit",
            L"Нет данных",
            WS_VSCROLL | WS_BORDER | WS_VISIBLE | WS_CHILD | ES_MULTILINE,
            770, 225,
            300, 300,
            hWnd, //<----- Use main window handle
            (HMENU)10012,
            hInst, NULL);
    }
    break;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        int len = 0;
        // Разобрать выбор в меню:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case 10001:
            matrix = Matrix::Matrix1;
            SetWindowText(hLoadPathButton, SMALL_FILE);
            break;
        case 10002:
            matrix = Matrix::Matrix2;
            SetWindowText(hLoadPathButton, MEDIUM_FILE);
            break;
        case 10003:
            matrix = Matrix::Matrix3;
            SetWindowText(hLoadPathButton, LARGE_FILE);
            break;
        case 10005:
            alg = Alg::Alg1;
            break;
        case 10006:
            alg = Alg::Alg2;
            break;
        case 9999:
            testAlg(hOutputButton0, hOutputButton1, hOutputButton2, hLoadPathButton, 
                alg, hStartVertButton, hEndVertButton, matrix);
            break;
              
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:

        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

