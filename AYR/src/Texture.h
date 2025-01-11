#pragma once

#include"color.h"
namespace AYR
{
	class Texture
	{
	public:
		Texture();
		~Texture();

		void LoadTexture(const char* path);
		float Clamp(float min, float max, float value);
		Color Sample(float u, float v);
	private:
		int width, height;
		Color** textureData;
	};

}
