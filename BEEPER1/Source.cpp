#include <Windows.h>
#define ID_TIMER 1

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
VOID CALLBACK TimerProc(HWND, UINT, UINT_PTR, DWORD);

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
		szAppName,
		TEXT("Timer"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
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
		SetTimer(hwnd, ID_TIMER, 1000, TimerProc);
		return 0;

	case WM_DESTROY:
		KillTimer(hwnd, ID_TIMER);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

VOID CALLBACK TimerProc(HWND hwnd, UINT message, UINT_PTR iTimerID, DWORD dwTime) {
	static BOOL fFlipFlop = FALSE;
	HBRUSH hBrush;
	HDC hdc;
	RECT rect;

	MessageBeep(-1);
	fFlipFlop = !fFlipFlop;
	
	//get client rect to fill with color
	GetClientRect(hwnd, &rect);

	//get device handle
	hdc = GetDC(hwnd);

	//create Brush
	hBrush = CreateSolidBrush(fFlipFlop ? RGB(255, 0, 0) : RGB(0, 0, 255));
	
	//paint/fill rectangle with created brush
	FillRect(hdc, &rect, hBrush);

	//release device handle
	ReleaseDC(hwnd, hdc);

	//delete brush object
	DeleteObject(hBrush);
}