#pragma once

class Rect
{
public:
	Rect() : Rect(Vector2(), Vector2(100, 100)) {}
	Rect(Vector2 position, Vector2 scale);

	void Update();
	void Render();

private:
	RECT rect{};	// 그려질 영역

	Vector2 position;	// 중심점의 좌표. 외부에서는 가져다 쓸 수 있지만, 실재로 그리기 위해서는 여전히 Rect가 필요함
	Vector2 scale;		// 중심점으로부터 뻗어나가는 거리. position과 scale로 rect의 좌표들을 구할 수 있음
};