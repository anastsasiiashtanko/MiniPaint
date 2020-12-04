// WindowsProject2.cpp : Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "WindowsProject2.h"
#include <Windowsx.h>
#include <vector>
#include <cstdio>
#include "Shape.h"
#include "Rect.h"
#include "Circle.h"
#include <commdlg.h>
#include "ColorRect.h"
#include "ColorCircle.h"
#include <CommCtrl.h>

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Settings(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF);
	MSG msg;
	{
		UNREFERENCED_PARAMETER(hPrevInstance);
		UNREFERENCED_PARAMETER(lpCmdLine);

		// TODO: Разместите код здесь.

		// Инициализация глобальных строк
		LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
		LoadStringW(hInstance, IDC_WINDOWSPROJECT2, szWindowClass, MAX_LOADSTRING);
		MyRegisterClass(hInstance);

		// Выполнить инициализацию приложения:
		if (!InitInstance(hInstance, nCmdShow))
		{
			return FALSE;
		}

		HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));


		// Цикл основного сообщения:
		while (GetMessage(&msg, nullptr, 0, 0))
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
	if (_CrtDumpMemoryLeaks())
	{
		MessageBoxA(NULL, "MEMORY LEAKS.", "text leaks", MB_OK);
	}
    return (int) msg.wParam;
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

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
enum Shapes { RECTANGLE, CIRCLE };
struct settings
{
	int m_brushSize;
	HBRUSH m_brush;
	HPEN m_pen;
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static std::vector<Shape*> shapes;
	int length = shapes.size();
	static Shapes shape(RECTANGLE);

	static settings set = { 10 };

	switch (message)
	{
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	{//MK_LBUTTON
		if (wParam&WM_LBUTTONDOWN)
		{

			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);

			/*char buff[256];
			sprintf_s(buff, "x = %d y = %d", xPos, yPos);
			MessageBoxA(hWnd,buff, "test", MB_OK);*/

			HDC hDC = GetDC(hWnd);
			if (set.m_brush != 0)
			{
				HBRUSH oldBr = SelectBrush(hDC, set.m_brush);
				DeleteBrush(oldBr);
			}
			if (set.m_pen != 0)
			{
				HPEN oldPen = SelectPen(hDC, set.m_pen);
				DeletePen(oldPen);
			}
			switch (shape) {
			case RECTANGLE:
			{
				
				Rectangle(hDC, xPos - set.m_brushSize, yPos - set.m_brushSize, xPos + set.m_brushSize, yPos + set.m_brushSize);
				if(set.m_brush==0)
				{
					shapes.push_back(new Rect(xPos - set.m_brushSize, yPos - set.m_brushSize, xPos + set.m_brushSize, yPos + set.m_brushSize));
				}
				else
					shapes.push_back(new ColorRect(xPos - set.m_brushSize, yPos - set.m_brushSize, xPos + set.m_brushSize, yPos + set.m_brushSize, set.m_brush,set.m_pen));
	
			} 
			break;
			case CIRCLE:
			{
					Ellipse(hDC, xPos - set.m_brushSize, yPos - set.m_brushSize, xPos + set.m_brushSize, yPos + set.m_brushSize);
					if (set.m_brush == 0)
					{
						shapes.push_back(new Circle(xPos - set.m_brushSize, yPos - set.m_brushSize, xPos + set.m_brushSize, yPos + set.m_brushSize));
					}
					else
						shapes.push_back(new ColorCircle(xPos - set.m_brushSize, yPos - set.m_brushSize, xPos + set.m_brushSize, yPos + set.m_brushSize,set.m_brush,set.m_pen));
			}break;
			}
			ReleaseDC(hWnd, hDC);
		}
	}
	break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case ID_TOOLS_RECTANGLE:
				//MessageBoxA(hWnd, "this is rectangle...", "test", MB_OK);
				shape = RECTANGLE;
				break;
			case ID_TOOLS_CIRCLE:
				shape = CIRCLE;
				break;
			case ID_TOOLS_SETTINGS:
				//MessageBoxA(hWnd, "settings...", "test", MB_OK);
				DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_DIALOGSETTINGS), hWnd, Settings,(LPARAM)&set);
				break;
			case ID_TOOLS_CLEAR:
				for (int i = 0; i < length; ++i)
				{
					delete shapes[i];
				}
				shapes.clear();
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_FILE_SAVE:
			{
				OPENFILENAMEA ofn;       // common dialog box structure
				char szFile[260];       // buffer for file name
				HANDLE hf;              // file handle

				// Initialize OPENFILENAME
				ZeroMemory(&ofn, sizeof(ofn));
				ofn.lStructSize = sizeof(ofn);
				ofn.hwndOwner = hWnd;
				ofn.lpstrFile = szFile;
				// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
				// use the contents of szFile to initialize itself.
				ofn.lpstrFile[0] = '\0';
				ofn.nMaxFile = sizeof(szFile);
				ofn.lpstrFilter =  "All\0*.*\0Text\0*.TXT\0";
				ofn.nFilterIndex = 1;
				ofn.lpstrFileTitle = NULL;
				ofn.nMaxFileTitle = 0;
				ofn.lpstrInitialDir = NULL;
				ofn.Flags = OFN_PATHMUSTEXIST;           //| OFN_FILEMUSTEXIST; kogda otkryt existing file

				// Display the Open dialog box. 

				if (GetSaveFileNameA(&ofn) == TRUE)
				{
					//save data file with path and name
					MessageBoxA(NULL,ofn.lpstrFile, "path to file", MB_OK);
				}
			}
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
			
			for (int i = 0; i < length; ++i)
			{
				shapes[i]->draw(hdc);
			}

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
		for (int i = 0; i < length; ++i)
		{
			delete shapes[i];
		}
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
INT_PTR CALLBACK Settings(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static settings *pdata=nullptr;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		pdata = (settings*)lParam;
		SendDlgItemMessageA(hDlg, IDC_SLIDERBRUSHSSIZE, TBM_SETRANGEMIN, TRUE, 1);
		SendDlgItemMessageA(hDlg, IDC_SLIDERBRUSHSSIZE, TBM_SETRANGEMAX, TRUE, 200);
		SendDlgItemMessageA(hDlg, IDC_SLIDERBRUSHSSIZE, TBM_SETPOS, TRUE, pdata->m_brushSize);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			pdata->m_brushSize = SendDlgItemMessageA(hDlg, IDC_SLIDERBRUSHSSIZE, TBM_GETPOS, 0, 0);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (IDC_BUTTONCOLOR == LOWORD(wParam))
		{
			CHOOSECOLOR cc;                 // common dialog box structure 
			static COLORREF acrCustClr[16]; // array of custom colors 
			HBRUSH hbrush;                  // brush handle
			static DWORD rgbCurrent;        // initial color selection

			// Initialize CHOOSECOLOR 
			ZeroMemory(&cc, sizeof(cc));
			cc.lStructSize = sizeof(cc);
			cc.hwndOwner = hDlg;
			cc.lpCustColors = (LPDWORD)acrCustClr;
			cc.rgbResult = rgbCurrent;
			cc.Flags = CC_FULLOPEN | CC_RGBINIT;

			if (ChooseColor(&cc) == TRUE)
			{
				hbrush = CreateSolidBrush(cc.rgbResult);
				if (nullptr != pdata)
				{
					pdata->m_brush = hbrush;
				}
				
				rgbCurrent = cc.rgbResult;
			}
		}
		else if (IDC_BUTTON_PENCOLOR== LOWORD(wParam))
		{
			CHOOSECOLOR cc;                 // common dialog box structure 
			static COLORREF acrCustClr[16]; // array of custom colors 
			HPEN hpen;                  // brush handle
			static DWORD rgbCurrent;        // initial color selection

			// Initialize CHOOSECOLOR 
			ZeroMemory(&cc, sizeof(cc));
			cc.lStructSize = sizeof(cc);
			cc.hwndOwner = hDlg;
			cc.lpCustColors = (LPDWORD)acrCustClr;
			cc.rgbResult = rgbCurrent;
			cc.Flags = CC_FULLOPEN | CC_RGBINIT;

			if (ChooseColor(&cc) == TRUE)
			{
				hpen = CreatePen(PS_SOLID,1,cc.rgbResult);
				if (nullptr != pdata)
				{
					pdata->m_pen = hpen;
				}

				rgbCurrent = cc.rgbResult;
			}
		}
		break;
	}
	return (INT_PTR)FALSE;
}
