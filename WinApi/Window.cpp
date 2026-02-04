#include "stdafx.h"
#include "Window.h"

Window::Window(const WinDesc& initDesc) : desc(initDesc)
{
	// 윈도우 클래스 등록
	ATOM classId = MyRegisterClass();	// ATOM은 WORD와 같음. unsigned short. 2바이트
	assert(classId != 0);	// 등록 실패
	// WORD는 과거 cpu가 한 번에 처리할 수 있는 데이터 크기 단위. cpu 레지스터가 16비트였던 시절. 온갖 데이터를 담음
	// ATOM은 더 이상 쪼갤 수 없는 단위를 나타냈었음. 윈도우 운영체제가 관리하는 문자열 해시맵에 대한 검색키

	hWnd = CreateWindowExW
	(
		WS_EX_APPWINDOW,
		desc.appName.c_str(),
		desc.appName.c_str(),
		WS_OVERLAPPEDWINDOW,	// 최상위창 옵션
		CW_USEDEFAULT,	// 게임에서 위치나 사이즈는 그래픽으로 그리면 해결
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		nullptr,
		(HMENU)nullptr,
		desc.hInstance,	// 창의 핸들을 통해 작동하는 방식. 이렇게 하면 창 안에서 웬만한 거는 추가 핸들 입력 없이 해결 가능
		nullptr
	);
	assert(hWnd != nullptr);

	RECT rect = { 0, 0, LONG(desc.width), LONG(desc.height)};

	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, 0);

	//GetSystemMetrics(SM_CXSCREEN);	// 화면 해상도의 x좌표
	//GetSystemMetrics(SM_CYSCREEN);	// 화면 해상도의 y좌표

	const int winWidth = int(rect.right - rect.left);
	const int winHeight = int(rect.bottom - rect.top);

	const int x = (GetSystemMetrics(SM_CXSCREEN) - winWidth) / 2;
	const int y = (GetSystemMetrics(SM_CYSCREEN) - winHeight) / 2;

	MoveWindow(
		hWnd,
		x,
		y,
		winWidth,
		winHeight,
		true	// 윈도우 페인트라는 메시지를 발생시킬지 여부
	);

	ShowWindow(hWnd, SW_SHOWNORMAL);	// 활성화시키고 끝
	UpdateWindow(hWnd);

	ShowCursor(true);
}

Window::~Window()
{
	// 윈도우 파괴
	DestroyWindow(hWnd);
	// 윈도우 클래스 등록 해제
	UnregisterClassW(desc.appName.c_str(), desc.hInstance);

	// 어떤 상황에서도 스택 프레임은 해제가 되는 것이 보장되기 때문에
	// 윈도우의 파괴와 윈도우 클래스 등록 해제가 보장
	// 유니크 포인터로 윈도우를 관리하는 것이 안전
}

ATOM Window::MyRegisterClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;	// 수평, 수직 방향으로 크기 변경 시 다시 그리기
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = desc.hInstance;
	wcex.hIcon = LoadIcon(nullptr, IDI_WINLOGO);	// nullptr이면 기본이 들어감. 아이콘은 작업표시줄에 보이는 아이콘
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);	// 프로그램 내부에서 보일 마우스 커서. 게임에서는 그래픽으로 그려서 사용
	wcex.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);	// 윈도우 창의 기본 색상. 클라이언트 영역의 배경색
																// os의 gdi를 사용해 그리는 방식.
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = desc.appName.c_str();	// wstring에 대한 c스타일의 롱포인터 요구. .c_str()으로 변환 .data()의 방식과 비슷
	wcex.hIconSm = wcex.hIcon;	// 윈도우 창 좌측 상단에 보이는 아이콘. 작업표시줄 아이콘과 동일하게 설정

	return RegisterClassExW(&wcex);
}

WPARAM Window::Run()
{
	MSG msg;
	
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)	// WM_QUIT을 활용한 무한루프 탈출
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}
	}

	return msg.wParam;	// 루프가 끝났다는 의미
}

LRESULT Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:	// 기본적으로 있어야 하는 그리기 메시지
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		EndPaint(hWnd, &ps);
	}
	return 0;
	case WM_CLOSE:
		if (MessageBox(hWnd, L"정말 종료하시겠습니까?", L"WindowAPI 종료", MB_OKCANCEL) == IDOK)
		{
			PostQuitMessage(0);	// wParam이 0인 WM_QUIT 메시지를 발생시킴
			// 유니크 포인터로 윈도우를 저장했기 때문에, 스택이 해제될 때 메모리를 해제
			// Run() 함수에서 QUIT이 발생해 루프가 종료되고 소멸자가 발생해 DESTROY 메시지 발생
			// 따라서 QUIT이 DESTROY보다 먼저 발생
			return 0;
		}
		return 0;
	}

	// 처리하고 있지 않는 모든 메시지는 기본 윈도우 프로시저에 전달
	return DefWindowProc(hWnd, message, wParam, lParam);
}

