#pragma once

#include "vector.h"
#include "Triangle.h"
#include <vector>

namespace AYR
{
	// TODO(1/12): re-implement this class with a new class Triangle
	class AYR_API Mesh
	{
	public:
		Mesh();
		~Mesh();

		std::vector<Triangle *> TriangleList; 

		static void ReadObj(const std::string& path, Mesh& mesh);
	};
}
