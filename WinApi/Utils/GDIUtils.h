#pragma once

namespace GDIUtils
{
	void SetRectCentered(Vector2 position, Vector2 scale, RECT& rect);

	void DrawRect(HDC hdc, const RECT& r);
	void DrawLine(HDC hdc, const RECT& r);
	void DrawCircle(HDC hdc, const RECT& r);
}