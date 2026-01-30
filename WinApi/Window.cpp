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
}

Window::~Window()
{
	// 윈도우 클래스 해제
	UnregisterClassW(desc.appName.c_str(), desc.hInstance);
}

ATOM Window::MyRegisterClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
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
	return WPARAM();
}
