#pragma once

#include"color.h"
#include<iostream>
#include<cmath>
#include<algorithm>

namespace AYR
{
    class Vector3f
    {
    public:
        float x, y, z;
        Vector3f() : x(0), y(0), z(0) {}
        Vector3f(float xx) : x(xx), y(xx), z(xx) {}
        Vector3f(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}
        Vector3f(const Vector3f& v) : x(v.x), y(v.y), z(v.z) {}
        Vector3f(const Color& c) : x(c.r * 255), y(c.g * 255), z(c.b * 255) {}

        Vector3f operator *(const float& r) const
        {
            return Vector3f(x * r, y * r, z * r);
        }

        Vector3f operator /(const float& r) const
        {
            return Vector3f(x / r, y / r, z / r);
        }

        float norm()
        {
            return std::sqrt(x * x + y * y + z * z);
        }

        Vector3f normalized()
        {
            float n = norm();
            return Vector3f(x / n, y / n, z / n);
        }

        Vector3f operator +(const Vector3f& v)const
        {
            return Vector3f(x + v.x, y + v.y, z + v.z);
        }

        Vector3f operator -(const Vector3f& v)const
        {
            return Vector3f(x - v.x, y - v.y, z - v.z);
        }

        Vector3f operator *(const Vector3f& v)const
        {
            return Vector3f(x * v.x, y * v.y, z * v.z);
        }

        Vector3f operator -()const
        {
            return Vector3f(-x, -y, -z);
        }

        Vector3f& operator +=(const Vector3f& v)
        {
            x += v.x; y += v.y; z += v.z;
            return *this;
        }

        friend Vector3f operator *(const float& r, const Vector3f& v)
        {
            return Vector3f(v.x * r, v.y * r, v.z * r);
        }

        friend std::ostream& operator <<(std::ostream& o, const Vector3f& v)
        {
            return o << v.x << ',' << v.y << ',' << v.z;
        }

        float operator [](int idx) const
        {
            if (idx < 0 || idx >= 3)
                throw std::out_of_range("Index out of range");
            return idx == 0 ? x : (idx == 1 ? y : z);
        }

        float& operator [](int idx)
        {
            if (idx < 0 || idx >= 3)
                throw std::out_of_range("Index out of range");
            return idx == 0 ? x : (idx == 1 ? y : z);
        }

        static Vector3f Min(const Vector3f& a, const Vector3f& b)
        {
            return Vector3f(std::min(a.x, b.x), std::min(a.y, b.y),
                std::min(a.z, b.z));
        }

        static Vector3f Max(const Vector3f& a, const Vector3f& b)
        {
            return Vector3f(std::max(a.x, b.x), std::max(a.y, b.y),
                std::max(a.z, b.z));
        }
    };

    class Vector2f
    {
    public:
        Vector2f() : x(0), y(0) {}
        Vector2f(float xx) : x(xx), y(xx) {}
        Vector2f(float xx, float yy) : x(xx), y(yy) {}
        Vector2f operator * (const float& r) const { return Vector2f(x * r, y * r); }
        Vector2f operator + (const Vector2f& v) const { return Vector2f(x + v.x, y + v.y); }
        Vector2f operator - (const Vector2f& v) const { return Vector2f(x - v.x, y - v.y); }
        float x, y;
    };

    inline Vector3f lerp(const Vector3f& a, const Vector3f& b, float t)
    {
        return a * (1 - t) + b * t;
    }

    inline Vector3f normalize(const Vector3f& v)
    {
        float n = v.x * v.x + v.y * v.y + v.z * v.z;
        if (n > 0)
        {
            n = 1 / std::sqrt(n);
            return Vector3f(v.x * n, v.y * n, v.z * n);
        }
        return v;
    }

    inline float dotProduct(const Vector3f& a, const Vector3f& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    inline Vector3f crossProduct(const Vector3f& a, const Vector3f& b)
    {
        return Vector3f(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
    }
}