#pragma once

#include "color.h"

namespace AYR
{
	class Texture // 1/14: not tested yet
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
