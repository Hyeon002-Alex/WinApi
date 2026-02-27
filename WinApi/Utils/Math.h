#pragma once
#include <Windows.h>
#include <cassert>
#include <cmath>

constexpr float EPSILON = 0.00001f;

namespace Math
{
	struct Vector2
	{
		float x;
		float y;

		// 생성자
		constexpr Vector2() : Vector2(0.0f, 0.0f) {}	// 위임생성
		constexpr Vector2(float x, float y) : x(x), y(y) {}
		constexpr Vector2(int x, int y) : Vector2(static_cast<float>(x), static_cast<float>(y)) {}
		constexpr Vector2(int x, float y) : Vector2(static_cast<float>(x), y) {}
		constexpr Vector2(float x, int y) : Vector2(x, static_cast<float>(y)) {}
		constexpr Vector2(POINT pt) : Vector2(static_cast<float>(pt.x), static_cast<float>(pt.y)) {}

		// 연산자
		Vector2 operator+(Vector2 other) const
		{
			Vector2 temp(x + other.x, y + other.y);
			return temp;
		}
		Vector2 operator-(Vector2 other) const
		{
			Vector2 temp(x - other.x, y - other.y);
			return temp;
		}
		Vector2 operator*(float scalar) const
		{
			Vector2 temp(x * scalar, y * scalar);
			return temp;
		}
		Vector2 operator/(float scalar) const
		{
			assert(scalar != 0.0f && "Vector2 Division by Zero");
			Vector2 temp(x / scalar, y / scalar);
			return temp;
		}
		//
		Vector2 operator+=(Vector2 other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		Vector2 operator-=(Vector2 other)
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
		Vector2 operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}
		Vector2 operator/=(float scalar)
		{
			assert(scalar != 0.0f && "Vector2 Division by Zero");
			x /= scalar;
			y /= scalar;
			return *this;
		}

		float LengthSq() const
		{
			return (x * x) + (y * y);
		}

		float Length() const
		{
			return sqrtf(LengthSq());
		}

		void Normalize()
		{
			// 부동소수점 때문에 부정확함
			// 0에 가까운 매우 작은 수인 EPSILON은 0으로 간주
			// 연산치고 비교적 무거운 연산이기 때문에 양변을 제곱해서 비교
			const float lengthSq = LengthSq();
			if (lengthSq > EPSILON * EPSILON)
			{
				const float invLength = 1.0f / sqrtf(lengthSq);	// 나눗셈을 두 번하는 것 보다는 역수를 구해서 곱하는 것이 나을 수 있음

				x *= invLength;
				y *= invLength;
			}
			else
			{
				// Length가 한없이 0에 가까워 사실상 0인 경우
				// 안전하게 0으로 바꿔버림
				x = 0.0f;
				y = 0.0f;
			}
		}
	};
}