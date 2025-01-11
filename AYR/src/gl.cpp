#include"gl.h"
#include"Core.h"
#include<cmath>
#include<vector>
namespace AYR
{
    void drawLine(const Vector2f& p1, const Vector2f& p2, const Vector3f& col, img *image)
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

    bool isPointInPolygon(const Vector2f& p, const std::vector<Vector2f>& polygon)
    {
        std::vector<int> sgn{};
        for (int i = 0; i < polygon.size(); ++i)
        {
            Vector2f v1 = polygon[i] - p;
            Vector2f v2 = polygon[(i + 1) % polygon.size()] - p;
            sgn.push_back(v1.x * v2.y - v1.y * v2.x);
        }

        // check if all the sign is the same or there is a zero
        return std::any_of(sgn.begin(), sgn.end(), [](int x) { return x == 0; }) || 
               (std::all_of(sgn.begin(), sgn.end(), [](int x) { return x > 0; }) || 
                std::all_of(sgn.begin(), sgn.end(), [](int x) { return x < 0; }));
    }

    void drawTriangle(const Vector2f& p1, const Vector2f& p2, const Vector2f& p3, const Vector3f& col, img* image)
    {
        Vector2f aabb_min = Vector2f(std::min(p1.x, std::min(p2.x, p3.x)), std::min(p1.y, std::min(p2.y, p3.y)));
        Vector2f aabb_max = Vector2f(std::max(p1.x, std::max(p2.x, p3.x)), std::max(p1.y, std::max(p2.y, p3.y)));

        for (int x = aabb_min.x; x <= (int)aabb_max.x; ++x)
            for (int y = aabb_min.y; y <= (int)aabb_max.y; ++y)
                if (isPointInPolygon(Vector2f(x, y), { p1, p2, p3 }))
                    image->setBuf(x, y, col);
    }
}
