#pragma once
#include <assert.h>

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
};