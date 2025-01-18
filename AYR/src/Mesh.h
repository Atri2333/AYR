#pragma once

#include "vector.h"
#include "Triangle.h"
#include "Texture.h"
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
		Texture* tex;

		static void Resize(Mesh& mesh, float scale);
		static void ReadObj(const std::string& path, Mesh& mesh);
		static void ReadTexture(const std::string& path, Mesh& mesh);
		static void Translate(Mesh& mesh, Vector3f trans);
		static void normalizeModel(Mesh& mesh);
	};
}
