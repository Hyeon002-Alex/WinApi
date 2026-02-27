#pragma once

#define NOMINMAX	// window.h의 min, max를 사용하지 않음. 표준만 사용

// 간단한 디버깅용 콘솔창. 릴리즈에서는 빼야함
#ifdef _DEBUG	// 디버그 모드일 때만 하라는 의미. 릴리즈일때는 비활성(NDEBUG)
#pragma comment(linker, "/subsystem:console /entry:wWinMainCRTStartup")	// 전처리문 명령
#endif 

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
#include <windowsx.h>

// C 런타임 헤더 파일입니다.
#include <cassert>
#include <string>
#include <memory>
#include <chrono>
#include <iostream>
#include <array>
#include <functional>

constexpr UINT WIN_DEFAULT_WIDTH = 1280;
constexpr UINT WIN_DEFAULT_HEIGHT = 720;


constexpr float WIN_CENTER_X = WIN_DEFAULT_WIDTH * 0.5f;
constexpr float WIN_CENTER_Y = WIN_DEFAULT_HEIGHT * 0.5f;