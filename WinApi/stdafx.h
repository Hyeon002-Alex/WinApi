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

using namespace std;

constexpr UINT WIN_DEFAULT_WIDTH = 1280;
constexpr UINT WIN_DEFAULT_HEIGHT = 720;

#define DECLARE_SINGLETON(CLASS_NAME)				\
private:											\
CLASS_NAME();										\
~CLASS_NAME();										\
CLASS_NAME(const CLASS_NAME&) = delete;				\
CLASS_NAME operator=(const CLASS_NAME&) = delete;	\
CLASS_NAME(CLASS_NAME&&) = delete;					\
CLASS_NAME& operator=(CLASS_NAME&&) = delete;		\
public:												\
static CLASS_NAME& Get()							\
{													\
	static CLASS_NAME instance;						\
	return instance;								\
}

extern HDC gHDC;
#include "Utils/Vector.h"
#include "Utils/GDIUtils.h"

#include "Systems/Time.h"
#include "Systems/Input.h"
#define TIME Time::Get()
#define INPUT Input::Get()

constexpr float CENTER_X = WIN_DEFAULT_WIDTH * 0.5f;
constexpr float CENTER_Y = WIN_DEFAULT_HEIGHT * 0.5f;
constexpr Vector2 CENTER = Vector2(CENTER_X, CENTER_Y);