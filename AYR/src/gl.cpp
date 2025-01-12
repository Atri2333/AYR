#include"gl.h"
#include"Core.h"
#include"utils.h"
#include<cmath>
#include<vector>
namespace AYR
{
    void drawLine(const Vector2i& p1, const Vector2i& p2, const Vector3f& col, img *image)
    {
        int x1 = p1.x, x2 = p2.x, y1 = p1.y, y2 = p2.y;
        const bool steep = std::abs(y2 - y1) > std::abs(x2 - x1);
        if (steep)
        {
            std::swap(x1, y1);
            std::swap(x2, y2);
        }
        if (x1 > x2)
        {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }

        const int dx = x2 - x1;
        const int dy = std::abs(y2 - y1);


        int error = dx;
        const int ystep = (y1 < y2) ? 1 : -1;
        int y = y1;


        for (int x = x1; x <= x2; x++) {
            if (steep) {
                image->setBuf(y, x, col);
            } else {
                image->setBuf(x, y, col);
            }

            error -= dy * 2;
            if (error < 0) {
                y += ystep;
                error += dx * 2;
            }
        }
    }

    bool isPointInPolygon(const Vector2i& p, const std::vector<Vector2i>& polygon)
    {
        std::vector<int> sgn{};
        for (int i = 0; i < polygon.size(); ++i)
        {
            Vector2i v1 = polygon[i] - p;
            Vector2i v2 = polygon[(i + 1) % polygon.size()] - p;
            sgn.push_back(v1.x * v2.y - v1.y * v2.x);
        }

        // check if all the sign is the same or there is a zero
        return std::any_of(sgn.begin(), sgn.end(), [](int x) { return x == 0; }) || 
               (std::all_of(sgn.begin(), sgn.end(), [](int x) { return x > 0; }) || 
                std::all_of(sgn.begin(), sgn.end(), [](int x) { return x < 0; }));
    }

    void drawTriangle(const Vector3f& p1, const Vector3f& p2, const Vector3f& p3, const Vector3f& col, img* image, float* zbuffer)
    {
        Vector2i aabb_min = Vector2i(std::min(p1.x, std::min(p2.x, p3.x)), std::min(p1.y, std::min(p2.y, p3.y)));
        Vector2i aabb_max = Vector2i(std::max(p1.x, std::max(p2.x, p3.x)), std::max(p1.y, std::max(p2.y, p3.y)));

        for (int x = std::max(0, aabb_min.x); x <= std::min(image->getHeight() - 1, aabb_max.x); ++x)
            for (int y = std::max(0, aabb_min.y); y <= std::min(image->getWidth() - 1, aabb_max.y); ++y)
                {
                    Vector3f bc_coord = BaryCentric(Vector2f(x, y), Vector2f(p1), Vector2f(p2), Vector2f(p3));
                    if(bc_coord.x < 0 || bc_coord.y < 0 || bc_coord.z < 0)
                        continue;
                    float z = bc_coord.x * p1.z + bc_coord.y * p2.z + bc_coord.z * p3.z;
                    if(z > zbuffer[x * image->getWidth() + y])
                    {
                        zbuffer[x * image->getWidth() + y] = z;
                        image->setBuf(x, y, col);
                    }
                }
    }
}

