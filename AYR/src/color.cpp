#include "color.h"
#include <random>
namespace AYR
{
	Color::Color(float cr, float cg, float cb, float ca)
		: r(cr), g(cg), b(cb), a(ca)
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

	Color Color::RandomColor()
	{
		// 使用随机设备作为种子
		static std::random_device rd;
		// 使用 Mersenne Twister 引擎
		static std::mt19937 gen(rd());
		// 定义分布范围 [0, 1]
		static std::uniform_real_distribution<float> dis(0.0f, 1.0f);

		return Color(dis(gen), dis(gen), dis(gen), 1.0f);
	}

	const Color Color::RED(1.0f, 0.0f, 0.0f, 1.0f);
	const Color Color::GREEN(0.0f, 1.0f, 0.0f, 1.0f);
	const Color Color::BLUE(0.0f, 0.0f, 1.0f, 1.0f);
	const Color Color::BLACK(0.0f, 0.0f, 0.0f, 1.0f);
	const Color Color::WHITE(1.0f, 1.0f, 1.0f, 1.0f);
}