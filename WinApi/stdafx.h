#pragma once

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
static CLASS_NAME& Get()								\
{													\
	static CLASS_NAME instance;						\
	return instance;								\
}