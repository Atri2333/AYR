#include "Matrix.h"
#include<cmath>

namespace AYR
{
    Matrix4x4::Matrix4x4(const float _mat[4][4])
    {
        for(int i = 0; i < 4; ++i)
            for(int j = 0; j < 4; ++j)
                mat[i][j] = _mat[i][j];
    }

    // Identity Matrix
    Matrix4x4::Matrix4x4()
    {
        for(int i = 0; i < 4; ++i)
            for(int j = 0; j < 4; ++j)
                mat[i][j] = (i == j) ? 1.0f : 0;
    }

    Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const
    {
        Matrix4x4 result;
        for(int i = 0; i < 4; ++i)
            for(int j = 0; j < 4; ++j)
                result.mat[i][j] = mat[i][0] * other.mat[0][j] + mat[i][1] * other.mat[1][j] + mat[i][2] * other.mat[2][j] + mat[i][3] * other.mat[3][j];
        return result;
    }

    Vector4f Matrix4x4::operator*(const Vector4f& other) const
    {
        Vector4f result;
        result.x = mat[0][0] * other.x + mat[0][1] * other.y + mat[0][2] * other.z + mat[0][3] * other.w;
        result.y = mat[1][0] * other.x + mat[1][1] * other.y + mat[1][2] * other.z + mat[1][3] * other.w;
        result.z = mat[2][0] * other.x + mat[2][1] * other.y + mat[2][2] * other.z + mat[2][3] * other.w;
        result.w = mat[3][0] * other.x + mat[3][1] * other.y + mat[3][2] * other.z + mat[3][3] * other.w;
        return result;
    }

    Matrix4x4 Matrix4x4::operator*(const float& other) const
    {
        Matrix4x4 result;
        for(int i = 0; i < 4; ++i)
            for(int j = 0; j < 4; ++j)
                result.mat[i][j] = mat[i][j] * other;
        return result;
    }

    Matrix4x4 Matrix4x4::operator+(const Matrix4x4& other) const
    {
        Matrix4x4 result;
        for(int i = 0; i < 4; ++i)
            for(int j = 0; j < 4; ++j)
                result.mat[i][j] = mat[i][j] + other.mat[i][j];
        return result;
    }

    Matrix4x4 Matrix4x4::operator-(const Matrix4x4& other) const
    {
        Matrix4x4 result;
        for(int i = 0; i < 4; ++i)
            for(int j = 0; j < 4; ++j)
                result.mat[i][j] = mat[i][j] - other.mat[i][j];
        return result;
    }

    Matrix4x4 Matrix4x4::operator-() const
    {
        Matrix4x4 result;
        for(int i = 0; i < 4; ++i)
            for(int j = 0; j < 4; ++j)
                result.mat[i][j] = -mat[i][j];
        return result;
    }

    Matrix4x4 Matrix4x4::transpose() const
    {
        Matrix4x4 result;
        for(int i = 0; i < 4; ++i)
            for(int j = 0; j < 4; ++j)
                result.mat[i][j] = mat[j][i];
        return result;
    }

    Matrix4x4 Matrix4x4::inverse() const
    {
        Matrix4x4 result;
        float det = 0.0f;

        // 计算所有3x3子矩阵的行列式
        float A2323 = mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2];
        float A1323 = mat[2][1] * mat[3][3] - mat[2][3] * mat[3][1];
        float A1223 = mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1];
        float A0323 = mat[2][0] * mat[3][3] - mat[2][3] * mat[3][0];
        float A0223 = mat[2][0] * mat[3][2] - mat[2][2] * mat[3][0];
        float A0123 = mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0];
        float A2313 = mat[1][2] * mat[3][3] - mat[1][3] * mat[3][2];
        float A1313 = mat[1][1] * mat[3][3] - mat[1][3] * mat[3][1];
        float A1213 = mat[1][1] * mat[3][2] - mat[1][2] * mat[3][1];
        float A2312 = mat[1][2] * mat[2][3] - mat[1][3] * mat[2][2];
        float A1312 = mat[1][1] * mat[2][3] - mat[1][3] * mat[2][1];
        float A1212 = mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1];
        float A0313 = mat[1][0] * mat[3][3] - mat[1][3] * mat[3][0];
        float A0213 = mat[1][0] * mat[3][2] - mat[1][2] * mat[3][0];
        float A0312 = mat[1][0] * mat[2][3] - mat[1][3] * mat[2][0];
        float A0212 = mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0];
        float A0113 = mat[1][0] * mat[3][1] - mat[1][1] * mat[3][0];
        float A0112 = mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0];

        // 计算行列式
        det = mat[0][0] * (mat[1][1] * A2323 - mat[1][2] * A1323 + mat[1][3] * A1223)
            - mat[0][1] * (mat[1][0] * A2323 - mat[1][2] * A0323 + mat[1][3] * A0223)
            + mat[0][2] * (mat[1][0] * A1323 - mat[1][1] * A0323 + mat[1][3] * A0123)
            - mat[0][3] * (mat[1][0] * A1223 - mat[1][1] * A0223 + mat[1][2] * A0123);

        // 检查行列式是否为0
        if (std::abs(det) < 1e-8) {
            // 矩阵不可逆，返回单位矩阵或抛出异常
            std::cerr << "Matrix is not invertible" << std::endl;
            return Matrix4x4();
        }

        float invDet = 1.0f / det;

        // 计算伴随矩阵并除以行列式
        result.mat[0][0] = invDet * (mat[1][1] * A2323 - mat[1][2] * A1323 + mat[1][3] * A1223);
        result.mat[0][1] = invDet * -(mat[0][1] * A2323 - mat[0][2] * A1323 + mat[0][3] * A1223);
        result.mat[0][2] = invDet * (mat[0][1] * A2313 - mat[0][2] * A1313 + mat[0][3] * A1213);
        result.mat[0][3] = invDet * -(mat[0][1] * A2312 - mat[0][2] * A1312 + mat[0][3] * A1212);
        
        result.mat[1][0] = invDet * -(mat[1][0] * A2323 - mat[1][2] * A0323 + mat[1][3] * A0223);
        result.mat[1][1] = invDet * (mat[0][0] * A2323 - mat[0][2] * A0323 + mat[0][3] * A0223);
        result.mat[1][2] = invDet * -(mat[0][0] * A2313 - mat[0][2] * A0313 + mat[0][3] * A0213);
        result.mat[1][3] = invDet * (mat[0][0] * A2312 - mat[0][2] * A0312 + mat[0][3] * A0212);
        
        result.mat[2][0] = invDet * (mat[1][0] * A1323 - mat[1][1] * A0323 + mat[1][3] * A0123);
        result.mat[2][1] = invDet * -(mat[0][0] * A1323 - mat[0][1] * A0323 + mat[0][3] * A0123);
        result.mat[2][2] = invDet * (mat[0][0] * A1313 - mat[0][1] * A0313 + mat[0][3] * A0113);
        result.mat[2][3] = invDet * -(mat[0][0] * A1312 - mat[0][1] * A0312 + mat[0][3] * A0112);
        
        result.mat[3][0] = invDet * -(mat[1][0] * A1223 - mat[1][1] * A0223 + mat[1][2] * A0123);
        result.mat[3][1] = invDet * (mat[0][0] * A1223 - mat[0][1] * A0223 + mat[0][2] * A0123);
        result.mat[3][2] = invDet * -(mat[0][0] * A1213 - mat[0][1] * A0213 + mat[0][2] * A0113);
        result.mat[3][3] = invDet * (mat[0][0] * A1212 - mat[0][1] * A0212 + mat[0][2] * A0112);

        return result;
    }

    Matrix4x4 Matrix4x4::get_view_matrix(const Vector3f& eye, const Vector3f& lookAt, const Vector3f& up)
    {
        auto g = lookAt; g.normalize();
        auto t = up; t.normalize();
        auto crs = crossProduct(g, t);
        float rotate[4][4] = {
            crs.x, crs.y, crs.z, 0,
            t.x, t.y, t.z, 0,
            -g.x, -g.y, -g.z, 0,
            0, 0, 0, 1
        };

        float translate[4][4] = {
            {1, 0, 0, -eye.x},
            {0, 1, 0, -eye.y},
            {0, 0, 1, -eye.z},
            {0, 0, 0, 1}
        };
        Matrix4x4 result(translate);
        Matrix4x4 R(rotate);
        return R * result;
    }

    Matrix4x4 Matrix4x4::get_model_matrix(float angle)
    {
        float rotate[4][4] = {
            {cos(angle), 0, sin(angle), 0},
            {0, 1, 0, 0},
            {-sin(angle), 0, cos(angle), 0},
            {0, 0, 0, 1}
        };
        constexpr float c = 2.5;
        float scale[4][4] = {
            {c, 0, 0, 0},
            {0, c, 0, 0},
            {0, 0, c, 0},
            {0, 0, 0, 1}
        };
        Matrix4x4 R(rotate), S(scale), T;
        return T * R * S;
    }

    Matrix4x4 Matrix4x4::get_projection_matrix(float fov, float aspect, float zNear, float zFar)
    {
        constexpr float MY_PI = 3.1415926;
        float t{ std::abs(zNear) * std::tan(0.5f * fov * MY_PI / 180) };
        float b{ -t };
        float r{ t * aspect };
        float l{ -r };

        // Mention(1/16): Should I minus the zNear and zFar???

        float ortho1[4][4] = {
            {2 / (r - l), 0, 0, 0},
            {0, 2 / (t - b), 0, 0},
            {0, 0, 2 / (zNear - zFar), 0},
            {0, 0, 0, 1}
        };

        float ortho2[4][4] = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, -(zNear + zFar) / 2},
            {0, 0, 0, 1}
        };

        float projection[4][4] = {
            {zNear, 0, 0, 0},
            {0, zNear, 0, 0},
            {0, 0, zNear + zFar, -zNear * zFar},
            {0, 0, 1, 0}
        };

        Matrix4x4 O(ortho1), R(ortho2), P(projection);
        return O * R * P;
    }
}