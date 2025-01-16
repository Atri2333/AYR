#pragma once

#include"color.h"
#include<iostream>
#include<cmath>
#include<algorithm>

namespace AYR
{
    template<typename T>
    class Vector4;
    template<typename T>
    class Vector3
    {
    public:
        T x, y, z;
        Vector3() : x(0), y(0), z(0) {}
        Vector3(T xx) : x(xx), y(xx), z(xx) {}
        Vector3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}
        template<typename U>
        Vector3(const Vector3<U>& v) : x((T)v.x), y((T)v.y), z((T)v.z) {}
        
        // maybe v.w==0, but this is used for homogeneous coordinates, not vectors.
        // I'll check it soon.
        template<typename U>
        Vector3(const Vector4<U>& v) : x((T)v.x / v.w), y((T)v.y / v.w), z((T)v.z / v.w) {}
        Vector3(const Color& c) : x(c.r * 255), y(c.g * 255), z(c.b * 255) {}

        Vector3 operator *(const T& r) const
        {
            return Vector3(x * r, y * r, z * r);
        }

        Vector3 operator /(const T& r) const
        {
            return Vector3(x / r, y / r, z / r);
        }

        float norm() const
        {
            return std::sqrt(x * x + y * y + z * z);
        }

        Vector3 normalized()
        {
            float n = norm();
            return Vector3f(x / n, y / n, z / n);
        }

        Vector3 normalize()
        {
            float n = norm();
            return *this = Vector3(x / n, y / n, z / n);
        }

        Vector3 operator +(const Vector3& v)const
        {
            return Vector3(x + v.x, y + v.y, z + v.z);
        }

        Vector3 operator -(const Vector3& v)const
        {
            return Vector3(x - v.x, y - v.y, z - v.z);
        }

        Vector3 operator *(const Vector3& v)const
        {
            return Vector3(x * v.x, y * v.y, z * v.z);
        }

        Vector3 operator -()const
        {
            return Vector3(-x, -y, -z);
        }

        Vector3& operator +=(const Vector3& v)
        {
            x += v.x; y += v.y; z += v.z;
            return *this;
        }

        friend Vector3 operator *(const float& r, const Vector3& v)
        {
            return Vector3(v.x * r, v.y * r, v.z * r);
        }

        friend std::ostream& operator <<(std::ostream& o, const Vector3& v)
        {
            return o << v.x << ',' << v.y << ',' << v.z;
        }

        T operator [](int idx) const
        {
            if (idx < 0 || idx >= 3)
                throw std::out_of_range("Index out of range");
            return idx == 0 ? x : (idx == 1 ? y : z);
        }

        T& operator [](int idx)
        {
            if (idx < 0 || idx >= 3)
                throw std::out_of_range("Index out of range");
            return idx == 0 ? x : (idx == 1 ? y : z);
        }

        static Vector3 Min(const Vector3& a, const Vector3& b)
        {
            return Vector3(std::min(a.x, b.x), std::min(a.y, b.y),
                std::min(a.z, b.z));
        }

        static Vector3 Max(const Vector3& a, const Vector3& b)
        {
            return Vector3(std::max(a.x, b.x), std::max(a.y, b.y),
                std::max(a.z, b.z));
        }
    };

    using Vector3f = Vector3<float>;
    using Vector3i = Vector3<int>;

    template<typename T>
    class Vector2
    {
    public:
        Vector2() : x(0), y(0) {}
        Vector2(T xx) : x(xx), y(xx) {}
        Vector2(T xx, T yy) : x(xx), y(yy) {}

        template<typename U>
        Vector2(const Vector2<U>& v) : x((T)v.x), y((T)v.y) {}
        template<typename U>
        Vector2(const Vector3<U>& v) : x((T)v.x), y((T)v.y) {}
        
        Vector2 operator * (const T& r) const { return Vector2(x * r, y * r); }
        Vector2 operator / (const T& r) const { return Vector2(x / r, y / r); }
        Vector2 operator + (const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
        Vector2 operator - (const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
        T x, y;
    };

    using Vector2f = Vector2<float>;
    using Vector2i = Vector2<int>;

    // Mention(1/15): this class is mainly used for homogeneous coordinates
    template<typename T>
    class Vector4
    {
    public:
        T x, y, z, w;
        Vector4() : x(0), y(0), z(0), w(0) {}
        Vector4(T xx) : x(xx), y(xx), z(xx), w(1) {}
        Vector4(T xx, T yy, T zz) : x(xx), y(yy), z(zz), w(1) {}
        
        Vector4(T xx, T yy, T zz, T ww) : x(xx), y(yy), z(zz), w(ww) {}
        template<typename U>
        Vector4(const Vector4<U>& v) : x((T)v.x), y((T)v.y), z((T)v.z), w((T)v.w) {}
        template<typename U>
        Vector4(const Vector3<U>& v) : x((T)v.x), y((T)v.y), z((T)v.z), w(1) {}
        template<typename U>
        Vector4(const Vector3<U>& v, T ww) : x((T)v.x), y((T)v.y), z((T)v.z), w(ww) {}


    };

    using Vector4f = Vector4<float>;
    using Vector4i = Vector4<int>;

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