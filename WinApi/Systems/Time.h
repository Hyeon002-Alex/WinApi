#pragma once

class Time
{
	DECLARE_SINGLETON(Time)

public:
	void Update();
	// deltaTime은 일반적으로 float을 사용. 게임에서는 float 정도의 정밀도여도 괜찮음
	float GetDeltaTime() const { return static_cast<float>(deltaTime); }
	double GetWorldTime() const { return worldTime; }
	UINT GetFPS() const { return fps; }
	void CheckTime() const { cout << "FPS : " << fps << ", DeltaTime : " << deltaTime << ", WorldTime : " << worldTime << '\n'; }

private:
	chrono::steady_clock::time_point currentTime;
	chrono::steady_clock::time_point lastTime;
	double deltaTime = 0.0;

	double worldTime = 0.0;	// 누적 시간

	UINT fps = 0;
	UINT frameCount = 0;	// 프레임 측정용 카운트. fps와는 따로 세주어야 함. 이걸 갱신하고 fps를 출력
	double fpsTimeElapsed = 0.0;
};