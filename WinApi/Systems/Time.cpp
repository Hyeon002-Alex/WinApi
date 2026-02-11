#include "stdafx.h"
#include "time.h"

Time::Time()
{
	currentTime = chrono::steady_clock::now();
	lastTime = currentTime;
}

Time::~Time()
{
}

void Time::Update()
{
	currentTime = chrono::steady_clock::now();
	chrono::duration<double> delta = currentTime - lastTime;	// double로 바로 빼내올 수 없기 때문에 중간에 한 번 거쳐야 함
	deltaTime = delta.count();	// double 형태로 리턴

	lastTime = currentTime;

	worldTime += deltaTime;
	++frameCount;
	fpsTimeElapsed += deltaTime;

	if (fpsTimeElapsed >= 1.0)	// 정확하게 1로 샐 수는 없으므로 오차가 발생하기는 함
	{
		fps = frameCount;
		frameCount = 0;
		fpsTimeElapsed -= 1.0;
		CheckTime();
	}
}
