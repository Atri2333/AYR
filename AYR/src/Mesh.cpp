#include "Mesh.h"

// Mention(1/14): this is a header-only library, you can't directly include it in multiple files,
//                  which will cause symbol redefinition.
#include "OBJ_Loader.h"

namespace AYR
{
	Mesh::Mesh()
	{
        tex = new Texture();
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
        if (tex)
        {
            delete tex;
        }
	}

    // Mention(1/17): Suppose the center is in (0, 0, 0), maybe I will improve it soon.
    void Mesh::Resize(Mesh& mesh, float scale)
    {
        for(auto &tri : mesh.TriangleList)
        {
            for(auto &v : tri->v)
            {
                v = v * scale;
            }
        }
    }

    void Mesh::Translate(Mesh& mesh, Vector3f trans)
    {
        for(auto &tri : mesh.TriangleList)
        {
            for(auto &v : tri->v)
            {
                v = v + trans;
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

    void Mesh::ReadTexture(const std::string& path, Mesh& mesh)
    {
        // Mention(1/15): this kind of API may be naive
        if (!mesh.tex->LoadTexture(path.c_str()))
        {
            std::cerr << "Mesh Read Texture ERROR!" << std::endl;
            return;
        }
    }

    void Mesh::normalizeModel(Mesh& mesh)
    {
        // TODO(1/17): normalize the model
        Vector3f center = Vector3f(0, 0, 0);
        for(auto &tri : mesh.TriangleList)
        {
            for(auto &v : tri->v)
            {
                center = center + v;
            }
        }
        center = center / mesh.TriangleList.size() / 3;
        Translate(mesh, -center);

        float maxSize = 0;
        for(auto &tri : mesh.TriangleList)
        {
            for(auto &v : tri->v)
            {
                maxSize = std::max(maxSize, v.norm());
            }
        }
        Resize(mesh, 1.0f / maxSize);
    }
}
