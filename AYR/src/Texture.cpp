#include "Texture.h"
#include"utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

namespace AYR
{
	Texture::Texture(){}
	Texture::~Texture(){
        if (textureData != nullptr)
        {
            for (int i = 0; i < height; i++)
                delete[] textureData[i];
            delete[] textureData;
        }
    }

	bool Texture::LoadTexture(const char* path)
	{
        if (textureData != nullptr)
        {
            for (int i = 0; i < height; i++)
                delete[] textureData[i];
            delete[] textureData;
            textureData = nullptr;
        }

        int channels;
        unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
        if (data)
        {
            textureData = new Color*[height];
            for (int i = 0; i < height; i++)
            {
                textureData[i] = new Color[width];
            }

            // 将图片数据转换为Color格式
            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    int flipped_y = height - 1 - y;
                    int index = (y * width + x) * channels;
                    if (channels == 4)
                    {
                        textureData[flipped_y][x] = Color(
                            data[index] / 255.0f,     // R
                            data[index + 1] / 255.0f, // G
                            data[index + 2] / 255.0f, // B
                            data[index + 3] / 255.0f  // A
                        );
                    }
                    else // channels == 3
                    {
                        textureData[flipped_y][x] = Color(
                            data[index] / 255.0f,     // R
                            data[index + 1] / 255.0f, // G
                            data[index + 2] / 255.0f,  // B
                            1.0f
                        );
                    }
                }
            }

            // 释放原始图片数据
            stbi_image_free(data);
            
            return true;
        }
        else
        {
            std::cerr << "Failed to load texture: " << path << std::endl;

            return false;
        }
	}

    Color Texture::Sample(float u, float v)
    {
        // return solid purple if texture is not loaded
        if (textureData == nullptr)
            return Color(1, 0, 1, 1);
            
        u = Clamp(0.0f, 1.0f, u);
        v = Clamp(0.0f, 1.0f, v);
        int x = static_cast<int>(u * width);
        int y = static_cast<int>(v * height);
        return textureData[y][x];
    }
}
