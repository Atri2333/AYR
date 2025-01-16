#pragma once

#include"vector.h"
namespace AYR
{
	class Matrix4x4
	{
	public:
		Matrix4x4();
		Matrix4x4(const float _mat[4][4]);

		Matrix4x4 operator*(const Matrix4x4& other) const;

		Vector4f operator*(const Vector4f& other) const;

		Matrix4x4 operator*(const float& other) const;

		Matrix4x4 operator+(const Matrix4x4& other) const;

		Matrix4x4 operator-(const Matrix4x4& other) const;

		Matrix4x4 operator-() const;

		Matrix4x4 transpose() const;

		Matrix4x4 inverse() const;

		static Matrix4x4 get_view_matrix(const Vector3f& eye);

		static Matrix4x4 get_model_matrix(float angle);

		static Matrix4x4 get_projection_matrix(float fov, float aspect, float zNear, float zFar);

	private:
		float mat[4][4];
	};
}