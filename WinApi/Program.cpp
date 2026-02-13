#include "stdafx.h"
#include "Program.h"
#include "Rect.h"

Program::Program()
{
	rect1 = make_unique<Rect>(CENTER, Vector2(100,100));
	rect2 = make_unique<Rect>(CENTER + Vector2(200, -200), Vector2(100, 100));
}

Program::~Program()
{
}

void Program::Update()
{
	rect1->Update();
	rect2->Update();
}

void Program::Render()
{
	rect1->Render();
	rect2->Render();
}