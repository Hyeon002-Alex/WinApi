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

using namespace std;

constexpr UINT WIN_DEFAULT_WIDTH = 1280;
constexpr UINT WIN_DEFAULT_HEIGHT = 720;