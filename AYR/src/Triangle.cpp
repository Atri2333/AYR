#include "Triangle.h"

namespace AYR
{
	Triangle::Triangle()
	{
		for (int i = 0; i < 3; ++i)
		{
			v[i] = Vector3f(0);
			color[i] = Color{};
			tex_coords[i] = Vector2f(0);
		}
	}

	void Triangle::setVertex(int index, Vector3f ver)
	{
		v[index] = ver;
	}

	void Triangle::setNormal(int index, Vector3f n)
	{
		normal[index] = n;
	}

	void Triangle::setColor(int index, Color col)
	{
		color[index] = col;
	}

	void Triangle::setTexCoord(int index, Vector2f uv)
	{
		tex_coords[index] = uv;
	}
}