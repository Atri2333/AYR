#pragma once

// file includes picture types and texture declaration
#include "Core.h"
#include "vector.h"
#include<iostream>
namespace AYR
{
	class AYR_API img
	{
	public:
		img();
		img(int _w, int _h);
		virtual ~img();
		int getWidth()
		{
			return width;
		}
		int getHeight()
		{
			return height;
		}

		void clear()
		{
			if(buf != nullptr)
			{
				for (int i = 0; i < getHeight(); ++i)
					delete[] buf[i];
				delete[] buf;
			}
			buf = nullptr;
			width = 0;
			height = 0;
		}

		void resize(int _w, int _h)
		{
			clear();
			width = _w;
			height = _h;
			buf = new Vector3f*[height];
			for (int i = 0; i < height; ++i)
				buf[i] = new Vector3f[width];
		}

		Vector3f getBuf(int i, int j);
		void setBuf(int i, int j, Vector3f value);
		virtual void outPut(std::ostream& o);
	private:
		int width;
		int height;
		Vector3f** buf;
	};

	class AYR_API ppm : public img
	{
	public:
		virtual void outPut(std::ostream& o);

		ppm(int _w, int _h): img(_w, _h) {};
		ppm(): img() {};
	};

	// class AYR_API Texture : public img
	// {
	// public:
	// 	virtual void outPut(std::ostream& o);

	// 	Texture(int _w, int _h) : img(_w, _h) {};
	// 	Texture() : img() {};

	// 	void LoadTexture(const char* path);
	// 	Vector3f Sample(float u, float v);
	// 	float Clamp(float min, float max, float value);
	// private:
	// 	// maybe alpha?
	// };
}
