#include "stdafx.h"
#include "Rect.h"

Rect::Rect(Vector2 position, Vector2 scale)
	: position(position), scale(scale)
{
	GDIUtils::SetRectCentered(position, scale, rect);
}

void Rect::Update()
{
	GDIUtils::SetRectCentered(position, scale, rect);
}

void Rect::Render()
{
	GDIUtils::DrawRect(gHDC, rect);
}