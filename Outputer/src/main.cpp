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
    for (int i = 0; i < model->indexes.size(); i += 3)
    {
        AYR::Vector2i screen_cords[3];
        for (int j = 0; j < 3; ++j)
        {
            screen_cords[j] = AYR::Vector2i(
                height - (model->vertices[model->indexes[i + j].x].y + 1) * height / 2,
                (model->vertices[model->indexes[i + j].x].x + 1) * width / 2
            );
        }
        AYR::drawTriangle(screen_cords[0], screen_cords[1], screen_cords[2], AYR::Color::RandomColor(), ppm);
    }

    ppm->outPut(std::cout);
    delete model;
    delete ppm;
    return 0;
}