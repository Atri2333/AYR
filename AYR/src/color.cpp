#include "color.h"

namespace AYR
{
	Color::Color(float cr, float cg, float cb, float ca)
		: r(cr), g(cg), b(cb), a(ca)
	{

	}


	Color::~Color()
	{
	}

	Color Color::operator + (const Color& right) const
	{
		Color returnValue(r + right.r, g + right.g, b + right.b, a + right.a);
		return returnValue;
	}

	Color Color::operator - (const Color& right) const
	{
		Color returnValue(r - right.r, g - right.g, b - right.b, a - right.a);
		return returnValue;
	}

	Color Color::operator * (const Color& right) const
	{
		Color returnValue(r * right.r, g * right.g, b * right.b, a * right.a);
		return returnValue;
	}

	Color Color::operator * (float value) const
	{
		Color returnValue(r * value, g * value, b * value, a * value);
		return returnValue;
	}

	Color Color::operator / (float value) const
	{
		float rhvalue = 1.0f / value;
		Color returnValue(r * rhvalue, g * rhvalue, b * rhvalue, a * rhvalue);
		return returnValue;
	}

	Color Color::Lerp(const Color& left, const Color& right, float t)
	{
		return left + (right - left) * t;
	}

	const Color Color::RED(1.0f, 0.0f, 0.0f, 1.0f);
	const Color Color::GREEN(0.0f, 1.0f, 0.0f, 1.0f);
	const Color Color::BLUE(0.0f, 0.0f, 1.0f, 1.0f);
	const Color Color::BLACK(0.0f, 0.0f, 0.0f, 1.0f);
	const Color Color::WHITE(1.0f, 1.0f, 1.0f, 1.0f);
}