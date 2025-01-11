#pragma once

#include "color.h"

namespace AYR
{
	class Texture
	{
	public:
		Texture();
		~Texture();

		void LoadTexture(const char* path);
		Color Sample(float u, float v);
	private:
		int width, height;
		Color** textureData = nullptr;
	};

}
