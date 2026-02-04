// WinApi.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Window.h";

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    WinDesc desc;
    desc.appName = L"WinAPI";
    desc.hInstance = hInstance;
    desc.width = WIN_DEFAULT_WIDTH;
	desc.height = WIN_DEFAULT_HEIGHT;

    auto window = make_unique<Window>(desc);    
	WPARAM wParam = window->Run();

    return (int)wParam; // Run() 함수의 반환값인 wParam이 0일 경우 정상 종료
}