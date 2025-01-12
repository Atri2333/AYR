#define _CRT_SECURE_NO_WARNINGS
#include"AYR.h"

const int width = 400;
const int height = 500;
int main()
{
    AYR::img *ppm = new AYR::ppm(width, height);
    freopen("output.ppm", "w", stdout);
    AYR::Mesh* model = new AYR::Mesh();
    AYR::ReadObj("african_head.obj", *model);
    AYR::Vector3f light_dir = AYR::Vector3f(0, 0, -1);
    float *zbuffer = new float[width * height];
    for(int i = 0; i < width * height; i++)
        zbuffer[i] = -std::numeric_limits<float>::max();

    for (int i = 0; i < model->indexes.size(); i += 3)
    {
        AYR::Vector3f screen_cords[3];
        AYR::Vector3f world_cords[3];
        for (int j = 0; j < 3; ++j)
        {
            screen_cords[j] = AYR::Vector3f(
                (model->vertices[model->indexes[i + j].x].y + 1) * height / 2,
                (model->vertices[model->indexes[i + j].x].x + 1) * width / 2,
                model->vertices[model->indexes[i + j].x].z
            );
            world_cords[j] = model->vertices[model->indexes[i + j].x];
        }
        AYR::Vector3f n = AYR::crossProduct(world_cords[2] - world_cords[0], world_cords[1] - world_cords[0]);
        n.normalize();
        float intensity = AYR::dotProduct(n, light_dir);

        if(intensity > 0)
        {
            AYR::drawTriangle(screen_cords[0], screen_cords[1], screen_cords[2], AYR::Color::WHITE * intensity, ppm, zbuffer);
        }
    }
    
    ppm->flipVertical();

    

    ppm->outPut(std::cout);
    delete[] zbuffer;
    delete model;
    delete ppm;
    return 0;
}