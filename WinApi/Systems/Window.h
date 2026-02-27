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

class IMessageHandler
{
public:
	virtual ~IMessageHandler() = default;

	// Core에서 메시지를 수행하려면, Window에서 Core로 메시지를 전달해야 함
	// 단 Window가 Core를 알아버리면, 의존성 역전 문제가 생김
	// 가상함수 테이블 만큼의 비용만 발생
	virtual LRESULT WndProcHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
};

class Window
{

public:

	Window(const WinDesc& initDesc);
	~Window();

	// 콜백 타입 정의
	using MessageHandler = std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>;
	
	void SetMessageHandler(IMessageHandler* handler) { m_messageHandler = handler; }

	bool Initialize();

	void ClearBackBuffer();
	void Present();

	WPARAM Run();

private:
	ATOM MyRegisterClass();

	// 멤버 함수이기 때문에 static으로 선언 필수
	// this를 넘기는 방법도 존재
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	// static 방식의 문제점 : this*를 전달할 수 없음. 단순히 전달용으로 사용. 나중에 this*를 추출해서 멤버 함수로 전달
	LRESULT WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	WinDesc m_desc{};
	HWND m_hWnd = nullptr;

	IMessageHandler* m_messageHandler;
};