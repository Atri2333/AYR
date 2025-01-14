#pragma once

#include"vector.h"
#include"color.h"
#include"Texture.h"
namespace AYR
{
	class Triangle
	{
	public:
		Vector3f v[3]; // v0 -> v1 -> v2 -> v0 in counter-clockwise order
		Color color[3];
		Vector2f tex_coords[3];
		Vector3f normal[3];

		Texture* tex = nullptr;

		Triangle();
		Vector3f a() const { return v[0]; }
		Vector3f b() const { return v[1]; }
		Vector3f c() const { return v[2]; }

		void setVertex(int ind, Vector3f ver);
		void setNormal(int ind, Vector3f n);
		void setColor(int ind, Color col);
		void setTexCoord(int ind, Vector2f uv);


	};
}