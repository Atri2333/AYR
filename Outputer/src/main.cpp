#define _CRT_SECURE_NO_WARNINGS
#include"AYR.h"

const int width = 600;
const int height = 600;
int main()
{
    AYR::img *ppm = new AYR::ppm(width, height);
    freopen("output.ppm", "w", stdout);

    AYR::Mesh* model = new AYR::Mesh();
    AYR::Mesh::ReadObj("spot_triangulated_good.obj", *model);
    AYR::Mesh::ReadTexture("spot_texture.png", *model);
    AYR::Mesh::Resize(*model, 0.7f);

    AYR::Mesh* floor = new AYR::Mesh();
    
    AYR::Mesh::ReadObj("floor.obj", *floor);
    AYR::Mesh::ReadTexture("floor_diffuse.tga", *floor);
    AYR::Mesh::Resize(*floor, 2.5f);
    AYR::Mesh::Translate(*floor, AYR::Vector3f(0, 2, 0));

    AYR::Renderer renderer(width, height);
    renderer.setEyePos(AYR::Vector3f(7, 0, -7));
    renderer.setLookAt(AYR::Vector3f(-1, 0, 1));
    renderer.setUp(AYR::Vector3f(0, 1, 0));
    AYR::light l1{AYR::Vector3f(15, 15, -15), AYR::Vector3f(1000, 1000, 1000)};
    AYR::light l2{AYR::Vector3f(0, 20, 0), AYR::Vector3f(1000, 1000, 1000)};
    renderer.addLight(l1);
    renderer.addLight(l2);

    AYR::Shader* bpShader = new AYR::TextureShader();
    AYR::Shader* pureShader = new AYR::PureShader();
    renderer.draw(*model, bpShader);
    renderer.draw(*floor, pureShader);
    renderer.toImage(ppm);

    
    ppm->outPut(std::cout);
    delete model; delete floor;
    delete ppm;
    delete bpShader;
    delete pureShader;
    return 0;
}