#pragma once

#include"vector.h"
#include"img.h"
#include"Mesh.h"
#include"Triangle.h"
#include"Matrix.h"
#include<vector>
namespace AYR
{
	AYR_API class Renderer
	{
	public:
		Renderer(int width, int height);
		void draw(Mesh& mesh);

		void setModel(const Matrix4x4& model);
		void setView(const Matrix4x4& view);
		void setProjection(const Matrix4x4& projection);

	private:
		void drawLine(const Vector2i& p1, const Vector2i& p2, const Vector3f& col, img *image);
		void drawTriangle(const Triangle& tri, const Color& col);

	private:
		int width, height;
		Matrix4x4 model;
		Matrix4x4 view;
		Matrix4x4 projection;

		std::vector<Vector3f> frame_buffer;
		std::vector<float> z_buffer;
	};

	// AYR_API void drawLine(const Vector2i& p1, const Vector2i& p2, const Vector3f& col, img *image);
	// AYR_API void drawTriangle(const Triangle& tri, const Vector3f& col, img* image, float* zbuffer);
}