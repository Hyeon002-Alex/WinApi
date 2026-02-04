#pragma once

// Description : Window 클래스의 객체가 만들어 질 때 생성자로 넘길 수 있음
// dx에서는 객체를 직접 만들수 없음. 인터페이스만 제공. 내부 구현은 상속받는 클래스에서 구현
// 구현 함수에는 Desc를 요청하고, *를 넘겨줌
struct WinDesc
{
	wstring appName = L"DirectX App";
	HINSTANCE hInstance = nullptr;
	UINT width = 0;
	UINT height = 0;
};

class Window
{
public:
	Window(const WinDesc& initDesc);
	~Window();

	WPARAM Run();

private:
	ATOM MyRegisterClass();

	// 멤버 함수이기 때문에 static으로 선언 필수
	// this를 넘기는 방법도 존재
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	WinDesc desc{};
	HWND hWnd = nullptr;
};