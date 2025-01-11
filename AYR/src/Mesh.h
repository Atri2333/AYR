#pragma once

#include "vector.h"
#include <vector>

namespace AYR
{
	class AYR_API Mesh
	{
	public:
		Mesh();
		~Mesh();
        std::vector<Vector3f> vertices;
        std::vector<Vector3f> normals;
        std::vector<Vector2f> uvs;

		std::vector<Vector3i> indexes;
	};
}
