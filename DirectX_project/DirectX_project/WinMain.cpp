#include <Windows.h>
#include <string>
#include <sstream>
using namespace std;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {

    case WM_CLOSE:
		PostQuitMessage(69);
		break;

    case WM_KEYDOWN:
        if (wParam == 'F')
        {
			SetWindowText(hWnd, "Respects");
        }
		break;

    case WM_CHAR:
        {
		static std::string title;
		title.push_back((char)wParam);
		SetWindowText(hWnd, title.c_str());
        }
        break;

    case WM_LBUTTONDOWN:
        {
		POINTS pt = MAKEPOINTS(lParam);
        std::ostringstream oss;
		oss << "(" << pt.x << "," << pt.y << ")";
		SetWindowText(hWnd, oss.str().c_str());
        }
    }
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow)
{
    const auto pClassName = "DirectX11_JL";
    // Register the window class
    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(wc);
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = NULL;
    wc.hCursor = NULL;
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = pClassName;
    wc.hIconSm = NULL;

    RegisterClassEx(&wc);

    //Create window instance
    HWND hWnd = CreateWindowEx(
        0,
        pClassName,
        "The Window",
        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
        200, 200, 640, 480,
        NULL, NULL, hInstance, NULL
    );
    
    //Show window
    ShowWindow(hWnd, SW_SHOW);
   
    
	//Message pump
	MSG msg;
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
    {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (gResult == -1)
	{
		return -1;
	}
    else
    {
		return msg.wParam;
    }
    
}