#pragma once

#include"Texture.h"
#include"vector.h"
#include<vector>
namespace AYR
{
	// inspired by games101
	struct AYR_API light
	{
		Vector3f position;
		Vector3f intensity;
	};


	// fragment shader
	class AYR_API Shader
	{
	public:
		Vector3f eye_pos;
		Vector3f view_pos;
		Color color;
		Vector3f normal;
		Vector2f tex_coords;

		Texture* tex;

		

	public:
		Shader() { tex = nullptr; }
		Shader(Vector3f eye_pos, Vector3f view_pos, Color color, Vector3f normal, Vector2f tex_coords, Texture* tex)
			: eye_pos(eye_pos), view_pos(view_pos), color(color), normal(normal), tex_coords(tex_coords), tex(tex) {}

		virtual Color shade(std::vector<light> lights) = 0;
	};

	class AYR_API TextureShader : public Shader
	{
	public:
		TextureShader() = default;
		TextureShader(Vector3f eye_pos, Vector3f view_pos, Color color, Vector3f normal, Vector2f tex_coords, Texture* tex)
			: Shader(eye_pos, view_pos, color, normal, tex_coords, tex) {}
		virtual Color shade(std::vector<light> lights) override;
	};

	class AYR_API PureShader : public Shader
	{
	public:
		PureShader() = default;
		PureShader(Vector3f eye_pos, Vector3f view_pos, Color color, Vector3f normal, Vector2f tex_coords, Texture* tex)
			: Shader(eye_pos, view_pos, color, normal, tex_coords, tex) {}
		virtual Color shade(std::vector<light> lights) override;
	};
}