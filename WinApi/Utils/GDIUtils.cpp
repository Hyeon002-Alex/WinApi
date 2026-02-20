#include "stdafx.h"
#include "GDIUtils.h"

namespace GDIUtils
{
	void SetRectCentered(Vector2 position, Vector2 scale, RECT& rect)
	{
		rect = { LONG(position.x - scale.x * 0.5f), LONG(position.y - scale.y * 0.5f),
				LONG(position.x + scale.x * 0.5f), LONG(position.y + scale.y * 0.5f), };
	}

	void DrawRect(HDC hdc, const RECT& r)
	{
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));	// 칠할 때 잠깐 다른 브러시로 갈아 끼움. NULL_BRUSH는 투명 브러시

		Rectangle(hdc, r.left, r.top, r.right, r.bottom);	// dc에서 선택한 펜과 프러시로 사각형을 그림

		SelectObject(hdc, hOldBrush);
	}

	void DrawLine(HDC hdc, const RECT& r)
	{
		// 선을 그리기 위해서는, 가상의 점을 이동시킨 후에 그려야 함
		MoveToEx(hdc, r.left, r.top, nullptr);	// lppt는 이전 좌표를 저장하는 용도. 필요 없으면 nullptr
		LineTo(hdc, r.right, r.bottom);		// MoveToEx로 이동시킨 좌표부터 그리기
	}

	void DrawCircle(HDC hdc, const RECT& r)
	{
		// 온전한 원은 그릴 수 없고, 타원만 그릴 수 있음
		// 타원이 원을 포함하는 개념
		Ellipse(hdc, r.left, r.top, r.right, r.bottom);
	}
}
