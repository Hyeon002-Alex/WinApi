#include "stdafx.h"
#include "Window.h"
#include "Game/Program.h"

HDC gHDC = nullptr;

// 외부에서 초기화 필수
// make_unique : 프로그램이 시작할 때부터 program이 동적 할당된다는 것. 생성자에서 다른 객체와 상호작용하는 과정에서 초기화 순서 관련해서 꼬일 수도 있음
// 싱글턴 : 싱글턴은 전역변수 같은 것. 다른 데서 쓰기위해 사용. program은 다른 곳이 아닌 Window.cpp 안에서만 사용되면 됨
// 하지만 일단 초기화는 해야하기 때문에, 일단 nullptr로 초기화하고, make_unique 시기는 뒤로 조절
unique_ptr<Program> Window::program = nullptr;

Window::Window(const WinDesc& initDesc) : m_desc(initDesc)
{
	
}

Window::~Window()
{
	// 윈도우 파괴
	DestroyWindow(m_hWnd);
	// 윈도우 클래스 등록 해제
	UnregisterClassW(m_desc.appName.c_str(), m_desc.hInstance);

	// 어떤 상황에서도 스택 프레임은 해제가 되는 것이 보장되기 때문에
	// 윈도우의 파괴와 윈도우 클래스 등록 해제가 보장
	// 유니크 포인터로 윈도우를 관리하는 것이 안전
}

bool Window::Initialize()
{
	// 윈도우 클래스 등록
	ATOM classId = MyRegisterClass();	// ATOM은 WORD와 같음. unsigned short. 2바이트
	if (classId == 0)
	{
		assert(false && "MyRegisterClass FAILED");
		return false;
	}
	// WORD는 과거 cpu가 한 번에 처리할 수 있는 데이터 크기 단위. cpu 레지스터가 16비트였던 시절. 온갖 데이터를 담음
	// ATOM은 더 이상 쪼갤 수 없는 단위를 나타냈었음. 윈도우 운영체제가 관리하는 문자열 해시맵에 대한 검색키

	m_hWnd = CreateWindowExW
	(
		WS_EX_APPWINDOW,
		m_desc.appName.c_str(),
		m_desc.appName.c_str(),
		WS_OVERLAPPEDWINDOW,	// 최상위창 옵션
		CW_USEDEFAULT,	// 게임에서 위치나 사이즈는 그래픽으로 그리면 해결
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		nullptr,
		(HMENU)nullptr,
		m_desc.hInstance,	// 창의 핸들을 통해 작동하는 방식. 이렇게 하면 창 안에서 웬만한 거는 추가 핸들 입력 없이 해결 가능
		this	// this*를 전달하기 위한 용도. 메시지 처리 과정에서 this*가 lParam으로 전달
	);
	if (m_hWnd == nullptr)
	{
		assert(false && "CreateWindowExW FAILED");
		return false;
	}

	RECT rect = { 0, 0, LONG(m_desc.width), LONG(m_desc.height) };

	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, 0);

	const int winWidth = int(rect.right - rect.left);
	const int winHeight = int(rect.bottom - rect.top);

	const int x = (GetSystemMetrics(SM_CXSCREEN) - winWidth) / 2;
	const int y = (GetSystemMetrics(SM_CYSCREEN) - winHeight) / 2;

	MoveWindow(
		m_hWnd,
		x,
		y,
		winWidth,
		winHeight,
		true	// 윈도우 페인트라는 메시지를 발생시킬지 여부
	);

	ShowWindow(m_hWnd, SW_SHOWNORMAL);	// 활성화시키고 그려짐. WM_PAINT 발생
	UpdateWindow(m_hWnd);					// WM_PAINT를 즉각적으로 처리하라

	ShowCursor(true);

	return true;	// 전부다 초기화되었다는 의미
}

void Window::ClearBackBuffer()
{
}

void Window::Present()
{
}

ATOM Window::MyRegisterClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// 수평, 수직 방향으로 크기 변경 시 다시 그리기
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_desc.hInstance;
	wcex.hIcon = LoadIcon(nullptr, IDI_WINLOGO);	// nullptr이면 기본이 들어감. 아이콘은 작업표시줄에 보이는 아이콘
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);	// 프로그램 내부에서 보일 마우스 커서. 게임에서는 그래픽으로 그려서 사용
	wcex.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);	// 윈도우 창의 기본 색상. 클라이언트 영역의 배경색
																// os의 gdi를 사용해 그리는 방식.
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = m_desc.appName.c_str();	// wstring에 대한 c스타일의 롱포인터 요구. .c_str()으로 변환 .data()의 방식과 비슷
	wcex.hIconSm = wcex.hIcon;	// 윈도우 창 좌측 상단에 보이는 아이콘. 작업표시줄 아이콘과 동일하게 설정

	return RegisterClassExW(&wcex);
}

WPARAM Window::Run()
{
	program = make_unique<Program>();
	INPUT.Init(m_hWnd);

	MSG msg;
	
	SetWindowPos(m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);	// 핸들, z오더, 위치-크기, 플래그
	SetForegroundWindow(m_hWnd);	// 최상단 표시권한. Focus와 비슷. 시각적으로 위로 끌어올리라는 의미
	SetFocus(m_hWnd);				// 포커스를 주라는 의미. 논리적 해결. 보통 둘 중 하나만 해도 해결이 됨

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)	// WM_QUIT을 활용한 무한루프 탈출
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// 프로그램을 돌릴 텐데, 제한이 없기 때문에 성능에 따라 몇천 프레임이 나올 수도 있음
		// dx에서는 알아서 수직 동기화 옵션이 스왑 체인이 들어가 있음
		// 지금은 조금 더 api 기능을 활용해 프레임 제한을 시도해 볼 것
	}

	return msg.wParam;	// 루프가 끝났다는 의미
}

LRESULT CALLBACK Window::WndProc(HWND m_hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Window* window = nullptr;

	switch (message)
	{
	case WM_NCCREATE:	// 윈도우가 생성될 때 가장 먼저 생성되는 메시지 중 하나
		CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		window = reinterpret_cast<Window*>(pCreate->lpCreateParams);	// this*가 전달된 lpCreateParams를 Window*로 변환
	}
	// 처리하고 있지 않는 모든 메시지는 기본 윈도우 프로시저에 전달
	return DefWindowProc(m_hWnd, message, wParam, lParam);
}

LRESULT Window::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return LRESULT();
}
