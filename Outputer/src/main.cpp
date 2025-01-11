#define _CRT_SECURE_NO_WARNINGS
#include"AYR.h"

int main()
{
    AYR::img *ppm = new AYR::ppm(100, 100);
    freopen("output.ppm", "w", stdout);
    AYR::drawTriangle(AYR::Vector2f(13, 20), AYR::Vector2f(80, 80), AYR::Vector2f(55, 93), AYR::Color::BLUE, ppm);

    ppm->outPut(std::cout);
    delete ppm;
    return 0;
}