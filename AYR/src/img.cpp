#include "img.h"

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

namespace AYR
{
	img::img()
	{
		buf = nullptr;
	}
	img::img(int _w, int _h): width(_w), height(_h)
	{
		buf = new Vector3f* [_h];
		for (int i = 0; i < _h; ++i)
			buf[i] = new Vector3f[_w];
	}

	img::~img()
	{
		if (buf != nullptr)
		{
			for (int i = 0; i < getHeight(); ++i)
				delete[] buf[i];
			delete[] buf;
		}
	}

	void img::setBuf(int i, int j, Vector3f value)
	{
		if (buf != nullptr)
			buf[i][j] = value;
	}

	Vector3f img::getBuf(int i, int j)
	{
		if (buf != nullptr)
			return buf[i][j];
		else
			return Vector3f(0, 0, 0);
	}

	void img::outPut(std::ostream& o)
	{

	}

	void ppm::outPut(std::ostream& o)
	{
		o << "P3" << "\n";
		o << getWidth() << " " << getHeight() << "\n";
		o << "255" << "\n";
		for (int i = 0; i < getHeight(); ++i)
		{
			for (int j = 0; j < getWidth(); ++j)
				o << (int)getBuf(i, j).x << ' ' << (int)getBuf(i, j).y << ' ' << (int)getBuf(i, j).z << "\n";
		}
		std::flush(o);
	}

	// void Texture::outPut(std::ostream& o)
	// {

	// }

	// void Texture::LoadTexture(const char* path)
	// {
	// 	// 变量用于存储图像的宽度、高度和通道数
	// 	int width, height, channels;

	// 	// 使用 stb_image 加载图像，强制转换为 RGB 格式（3通道）
	// 	unsigned char* data = stbi_load(path, &width, &height, &channels, 3);
	// 	if (data)
	// 	{
	// 		// 设置纹理尺寸
	// 		resize(width, height);

	// 		// 将图像数据转换为 Vector3f 格式并存储
	// 		for (int i = 0; i < height; ++i)
	// 		{
	// 			for (int j = 0; j < width; ++j)
	// 			{
	// 				// 计算在 data 数组中的位置（每个像素3个通道）
	// 				int index = (i * width + j) * 3;
					
	// 				// 将 RGB 值归一化到 [0,1] 范围
	// 				float r = data[index] / 255.0f;
	// 				float g = data[index + 1] / 255.0f;
	// 				float b = data[index + 2] / 255.0f;

	// 				// 使用 setBuf 设置颜色
	// 				setBuf(i, j, Vector3f(r, g, b));
	// 			}
	// 		}

	// 		// 释放 stb_image 分配的内存
	// 		stbi_image_free(data);
	// 	}
	// 	else
	// 	{
	// 		// 错误处理：无法加载图像
	// 		std::cerr << "Failed to load texture at path: " << path << std::endl;
	// 	}
	// }

	// Vector3f Texture::Sample(float u, float v)
	// {
	// 	u = Clamp(0, 1.0f, u);
	// 	v = Clamp(0, 1.0f, v);
	// 	int uu = u * getWidth();
	// 	int vv = v * getWidth();
	// 	return getBuf(uu, vv);
	// }

	// float Texture::Clamp(float min, float max, float value)
	// {
	// 	if (value > max)
	// 		value = max;
	// 	if (value < min)
	// 		value = min;
	// 	return value;
	// }
}