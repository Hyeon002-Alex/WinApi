#pragma once

class Rect;	// 전방선언

class Program
{
public:
	Program();
	~Program();

	void Update();
	void Render();

private:
	unique_ptr<Rect> rect1;
	unique_ptr<Rect> rect2;

	bool isDragging = false;
};