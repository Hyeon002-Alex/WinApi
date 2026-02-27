#pragma once
#include "Singleton.h"

class Window;
class Input;
class Time;
class Program;

// 프로그램의 핵. Program에서 하던 일들의 일부를 가져옴
// 관리자 클래스들을 일일이 싱글턴으로 포함하는 대신, 코어에서 한 번에 소유해서 관리
// 관리자 클래스들도 싱글톤이 되는 효과

// 정석에 가까운 엔진의 진입점
// Run과 Loop도 여기서 돌 것
class Core : public Singleton<Core>
{
	friend class Singleton<Core>;	// 싱글턴 클래스에서 Core의 private 생성자에 접근할 수 있도록 허용. 부분적 캡슐화

public:
	WPARAM Run(HINSTANCE hInstance);

private:
	Core();
	~Core() override;

	//---관리자 클래스들---
	std::unique_ptr<Window> m_window;	// 멤버라는 의미로 m_ 접두사
	std::unique_ptr<Input> m_input;
	std::unique_ptr<Time> m_time;
	std::unique_ptr<Program> m_program;	// 초기화될 순서에 맞게 작성
};