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

    AYR::Renderer renderer(width, height);
    renderer.draw(*model);
    renderer.toImage(ppm);

    
    ppm->outPut(std::cout);
    delete model;
    delete ppm;
    return 0;
}