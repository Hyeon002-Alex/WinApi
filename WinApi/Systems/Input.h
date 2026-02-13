#pragma once

#define MAX_INPUT_KEY 256

class Input
{
	DECLARE_SINGLETON(Input)

	enum
	{
		KEY_INPUT_STATUS_NONE = 0,
		KEY_INPUT_STATUS_DOWN,	// 이전 프레임 x 현재 프레임 o
		KEY_INPUT_STATUS_UP,	// 이전 프레임 o 현재 프레임 x
		KEY_INPUT_STATUS_PRESS,	// 이전 프레임 o 현재 프레임 o
	};

public:
	void Update();

	bool GetKeyDown(unsigned char key) const { return keyMap[key] == KEY_INPUT_STATUS_DOWN; }
	bool GetKeyUP(unsigned char key) const { return keyMap[key] == KEY_INPUT_STATUS_UP; }
	bool GetKeyPress(unsigned char key) const { return keyState[key]; }

private:
	array<unsigned char, MAX_INPUT_KEY> keyState{};
	array<unsigned char, MAX_INPUT_KEY> keyOldState{};
	array<unsigned char, MAX_INPUT_KEY> keyMap{};
};