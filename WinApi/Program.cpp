#include "stdafx.h"
#include "Program.h"
#include "Rect.h"

Program::Program()
{
	rect1 = make_unique<Rect>(CENTER, Vector2(100, 100), RGB(0, 0, 255));
	rect2 = make_unique<Rect>(CENTER + Vector2(200, -200), Vector2(100, 100), RGB(255, 0, 0));
}

Program::~Program()
{
}

void Program::Update()
{
	const float dt = DELTA;

	Vector2 dir {};
	float speed = 200.0f;

	const auto& input = INPUT;

	// 마우스의 좌표
	Vector2 mousePos;

	if (input.GetKeyPress('W')) { dir.y -= 1.0f; }
	if (input.GetKeyPress('S')) { dir.y += 1.0f; }
	if (input.GetKeyPress('A')) { dir.x -= 1.0f; }
	if (input.GetKeyPress('D')) { dir.x += 1.0f; }
	if (input.GetKeyPress(1)) { mousePos = input.GetMousePos(); }

	dir.Normalize();
	rect1->Move(dir, speed, dt);

	rect1->Update();
	rect2->Update();

	if (rect1->CheckIntersect(*rect2))
	{
		rect1->SetColor(RGB(0, 255, 255));
		rect2->SetColor(RGB(255, 255, 0));
	}
	else
	{
		rect1->SetColor(RGB(0, 0, 255));
		rect2->SetColor(RGB(255, 0, 0));
	}

	if (rect2->CheckIntersect(mousePos))
	{
		rect2->SetPosition(mousePos);
		rect2->SetColor(RGB(255, 0, 255));
	}
}

void Program::Render()
{
	rect1->Render();
	rect2->Render();
}
