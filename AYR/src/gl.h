#pragma once

#include"vector.h"
#include"img.h"
namespace AYR
{
	AYR_API class Renderer
	{
	public:
		
	};

	AYR_API void drawLine(const Vector2i& p1, const Vector2i& p2, const Vector3f& col, img *image);
	AYR_API void drawTriangle(const Vector3f& p1, const Vector3f& p2, const Vector3f& p3, const Vector3f& col, img* image, float* zbuffer);
}