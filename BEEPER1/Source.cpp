#include <Windows.h>
#define ID_TIMER 1

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrivInstance, PSTR szCmdLine, int iCmdShow) {
	static TCHAR szAppName[] = TEXT("Hello Win32 API");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIconW(NULL, IDI_WINLOGO);
	wndclass.hCursor = LoadCursorW(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	//register class
	if (!RegisterClass(&wndclass)) {
		MessageBox(NULL, TEXT("This program requires windows!!"), szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(
		//WS_EX_TOOLWINDOW, //use this to hide from taskbar too
		szAppName,
		//TEXT("Timer"),
		NULL,
		//WS_OVERLAPPEDWINDOW,
		WS_POPUP | WS_VISIBLE,
		0,
		0,
		500,
		500,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

//handling window message
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static BOOL fFlipFlop = FALSE;
	HBRUSH hBrush;
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;

	switch (message) {
	case WM_CREATE:
		SetTimer(hwnd, ID_TIMER, 1000, NULL);
		return 0;

	case WM_TIMER:
		MessageBeep(0x00000010L);
		fFlipFlop = !fFlipFlop;
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);
		hBrush = CreateSolidBrush(fFlipFlop ? RGB(255, 0, 0) : RGB(0,255,0));
		FillRect(hdc,&rc, hBrush);
		EndPaint(hwnd, &ps);
		DeleteObject(hBrush);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}