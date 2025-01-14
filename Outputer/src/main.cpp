#define _CRT_SECURE_NO_WARNINGS
#include"AYR.h"

const int width = 300;
const int height = 300;
int main()
{
    AYR::img *ppm = new AYR::ppm(width, height);
    freopen("output.ppm", "w", stdout);
    AYR::Mesh* model = new AYR::Mesh();
    AYR::Mesh::ReadObj("spot_triangulated_good.obj", *model);
    AYR::Vector3f light_dir = AYR::Vector3f(0, 0, -1);
    float *zbuffer = new float[width * height];
    for(int i = 0; i < width * height; i++)
        zbuffer[i] = -std::numeric_limits<float>::max();

    AYR::draw(*model, zbuffer, ppm);
    
    ppm->flipVertical();

    

    ppm->outPut(std::cout);
    delete[] zbuffer;
    delete model;
    delete ppm;
    return 0;
}