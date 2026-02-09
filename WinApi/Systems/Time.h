#pragma once

class Time
{
	DECLARE_SINGLETON(Time)

public:
	void Update();

private:
	chrono::steady_clock::time_point currentTime;
	chrono::steady_clock::time_point lastTime;
	double deltaTime = 0.0;
};