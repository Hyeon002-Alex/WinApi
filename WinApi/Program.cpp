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

	if (input.GetKeyPress('W')) { dir.y -= 1.0f; }
	if (input.GetKeyPress('S')) { dir.y += 1.0f; }
	if (input.GetKeyPress('A')) { dir.x -= 1.0f; }
	if (input.GetKeyPress('D')) { dir.x += 1.0f; }

	dir.Normalize();
	rect1->Move(dir, speed, dt);

	rect1->Update();
	rect2->Update();
}

void Program::Render()
{
	rect1->Render();
	rect2->Render();
}
