#include "Mesh.h"

// Mention(1/14): this is a header-only library, you can't directly include it in multiple files,
//                  which will cause symbol redefinition.
#include "OBJ_Loader.h"

namespace AYR
{
	Mesh::Mesh()
	{
	}

	Mesh::~Mesh()
	{
		for(auto tri : TriangleList)
		{
			if(tri)
			{
				delete tri;
				tri = nullptr;
			}
		}
	}

	void Mesh::ReadObj(const std::string& path, Mesh& mesh)
    {
        objl::Loader Loader;
        bool loadout = Loader.LoadFile(path);
        if(!loadout)
        {
            std::cerr << "Failed to open file: " << path << std::endl;
            return;
        }
        // TODO(1/12): adjust objl to Mesh API
        for(auto loadmesh : Loader.LoadedMeshes)
        {
            for(int i = 0; i < loadmesh.Vertices.size(); i += 3)
            {
                Triangle *tri = new Triangle();
                for(int j = 0; j < 3; ++j)
                {
                    tri->setVertex(j, Vector3f(loadmesh.Vertices[i + j].Position.X, loadmesh.Vertices[i + j].Position.Y, loadmesh.Vertices[i + j].Position.Z));
                    tri->setNormal(j, Vector3f(loadmesh.Vertices[i + j].Normal.X, loadmesh.Vertices[i + j].Normal.Y, loadmesh.Vertices[i + j].Normal.Z));
                    tri->setTexCoord(j, Vector2f(loadmesh.Vertices[i + j].TextureCoordinate.X, loadmesh.Vertices[i + j].TextureCoordinate.Y));
                }
                mesh.TriangleList.push_back(tri);
            }
        }
    }
}
