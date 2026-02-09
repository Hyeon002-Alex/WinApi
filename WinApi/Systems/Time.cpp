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
}
