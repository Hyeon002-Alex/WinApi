#include "stdafx.h"
#include "Input.h"

Input::Input() {}

Input::~Input() {}

void Input::Update()
{
	if (hWnd == nullptr)	return;
	keyOldState = keyState;	// 이전 프레임의 상태 정보를 넣어 놓음

	// data() : 시작점의 주소 반환
	// 가상 키의 값들을 keyState에 받아옴
	if (GetKeyboardState(keyState.data()))	// 키 상태 값을 받아옴. 실패할 경우 0
	{
		// 최상위 비트가 1이면 눌려있다 판단. 0이면 눌리지 않음
		// 토글키의 경우 최하위 비트가 1이면 눌림, 0이면 눌리지 않음
		// keyState, keyOldState, keyMap 3개에 대해서 반복해야 하기 때문에 범위기반 for는 적절하지 않음
		// 공통의 인덱스가 필요하기에 인덱스 기반 for문이 적절
		for (UINT i = 0; i < MAX_INPUT_KEY; ++i)
		{
			// 비트 & 연산으로 최상위 비트 값만 남길 수 있음
			// 참이면 1, 거짓이면 0
			keyState[i] = keyState[i] & 0x80 ? 1 : 0;

			const auto oldState = keyOldState[i];
			const auto state = keyState[i];
			auto& map = keyMap[i];

			if (oldState == 0 && state == 1)
				map = KEY_INPUT_STATUS_DOWN;
			else if (oldState == 1 && state == 0)
				map = KEY_INPUT_STATUS_UP;
			else if (oldState == 1 && state == 1)
				map = KEY_INPUT_STATUS_PRESS;
			else
				map = KEY_INPUT_STATUS_NONE;
		}
	}

	POINT pt;
	GetCursorPos(&pt);	// 화면 전체 기준에서의 마우스 좌표계
	ScreenToClient(hWnd, &pt);

	mousePos = Vector2(pt);
}