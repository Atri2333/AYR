#pragma once

#include"Core.h"

namespace AYR
{
	class AYR_API Color
	{
	public:
		float r, g, b, a;
		Color(float cr, float cg, float cb, float ca);
		Color() {};
		~Color();

		Color operator + (const Color& right) const;
		Color operator+(const float c)
		{
			return Color(r + c, g + c, b + c, a);
		}
		Color operator - (const Color& right) const;
		Color operator * (const Color& right) const;
		Color operator * (float value) const;
		Color operator / (float value) const;
		static Color Lerp(const Color& left, const Color& right, float t);
		static Color RandomColor();

		// Just declare the constants
		static const Color RED;
		static const Color GREEN;
		static const Color BLUE;
		static const Color BLACK;
		static const Color WHITE;
	};

}
