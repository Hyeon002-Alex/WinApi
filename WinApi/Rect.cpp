#include "stdafx.h"
#include "Rect.h"

Rect::Rect(Vector2 position, Vector2 scale, COLORREF color)
	: position(position), scale(scale), color(color)
{
	GDIUtils::SetRectCentered(position, scale, rect);
}

void Rect::Update()
{
	GDIUtils::SetRectCentered(position, scale, rect);	// 엄밀히 따지자면 Render에 가까움. 이미 수정된 포지션으로 rect를 수정하기 때문
}

void Rect::Render()
{
	COLORREF oldColor = SetDCBrushColor(gHDC, color);	// 들어온 컬러 값으로 메인 브러시의 색상을 설정. 원래 브러시가 가지고 있던 색상을 리턴
	FillRect(gHDC, &rect, (HBRUSH)GetStockObject(DC_BRUSH));	// 브러시가 들고 있는 색상으로 rect를 채움

	GDIUtils::DrawRect(gHDC, rect);

	SetDCBrushColor(gHDC, oldColor);	// 원래 들고 있던 색으로 다시 돌려놓음. dHDC가 다른 곳에서도 쓰일 수 있기 때문
}

void Rect::Move(Vector2 dir, float speed, float deltaTime)
{
	position += dir * speed * deltaTime;

	// 왜 DELTA를 직접 사용하지 않았는가?
	// 직접 사용한다면, Move가 동시에 여러번 호출되거나 DELTA를 동시에 호출할 경우에
	// DELTA는 TIME.GetDelta()를 호출하면서 오버헤드를 발생시킴
	// 이 구조에서는 여러번 호출시키기 때문에 오버헤드가 불필요하게 발생
	// 아니면 한 프레임에서 프로그램이 시작할 때 한 번만 deltaTime을 가져오는 방법도 있음
}
