#pragma once

#include"vector.h"
#include"img.h"
namespace AYR
{
	AYR_API class Renderer
	{
	public:
		
	};

	AYR_API void drawLine(const Vector2f& p1, const Vector2f& p2, const Vector3f& col, img *image);
	AYR_API void drawTriangle(const Vector2f& p1, const Vector2f& p2, const Vector2f& p3, const Vector3f& col, img* image);
}