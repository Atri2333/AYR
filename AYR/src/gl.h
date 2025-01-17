#pragma once

#include"vector.h"
#include"img.h"
#include"Mesh.h"
#include"Triangle.h"
#include"Matrix.h"
#include"Shader.h"
#include<vector>
namespace AYR
{
	class AYR_API Renderer
	{
	public:
		std::vector<light> lights;
		std::vector<light> trans_lights;
		Renderer(int width, int height);
		void draw(Mesh& mesh, Shader* shader);

		void setModel(const Matrix4x4& model);
		void setView(const Matrix4x4& view);
		void setProjection(const Matrix4x4& projection);

		void setEyePos(const Vector3f& eye_pos);
		void setLookAt(const Vector3f& look_at);
		void setUp(const Vector3f& up);

		void addLight(const light& light);
		void clearLight();

		void toImage(img* image);

	private:
		void drawLine(const Vector2i& p1, const Vector2i& p2, const Vector3f& col, img *image);
		void drawTriangle(const Triangle& tri, const std::vector<Vector3f>& view_poses,const Color& col, Shader* shader);

	private:
		int width, height;
		Matrix4x4 model;
		Matrix4x4 view;
		Matrix4x4 projection;

		Vector3f eye_pos;
		Vector3f LookAt;
		Vector3f Up;

		std::vector<Vector3f> frame_buffer;
		std::vector<float> z_buffer;
	};

	// AYR_API void drawLine(const Vector2i& p1, const Vector2i& p2, const Vector3f& col, img *image);
	// AYR_API void drawTriangle(const Triangle& tri, const Vector3f& col, img* image, float* zbuffer);
}