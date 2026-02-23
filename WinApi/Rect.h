#pragma once

class Rect
{
public:
	Rect() : Rect(Vector2(), Vector2(100, 100)) {}
	Rect(Vector2 position, Vector2 scale, COLORREF color = RGB(0, 0, 0));

	void Update();
	void Render();

	void Move(Vector2 dir, float speed, float deltaTime);

	void SetColor(COLORREF color) { this->color = color; }

	bool CheckIntersect(const Rect& other) const;	// 단일 책임 원칙 위반. 충돌 체크를 해주는 컴포넌트를 따로 만들어야 함. 이 때는 Rect가 아닌 다른 오브젝트의 콜라이더 사용
	bool CheckIntersect(Vector2 position) const;

	Vector2 GetPosition() const { return position; }
	Vector2 GetScale() const { return scale; }
	void SetPosition(Vector2 position) { this->position = position; }

private:
	RECT rect{};	// 그려질 영역

	Vector2 position;	// 중심점의 좌표. 외부에서는 가져다 쓸 수 있지만, 실재로 그리기 위해서는 여전히 Rect가 필요함
	Vector2 scale;		// 중심점으로부터 뻗어나가는 거리. position과 scale로 rect의 좌표들을 구할 수 있음

	COLORREF color;
};