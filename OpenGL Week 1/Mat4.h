#pragma once
#include "Prerequisites.h"
#include "Vec3.h"
#include "Vec4.h"
#include <math.h>

class Mat4
{
public:
	Mat4()
	{
		setIdentity();
	}

	void setIdentity()
	{
		::memset(mat, 0, sizeof(mat));
		mat[0][0] = 1;
		mat[1][1] = 1;
		mat[2][2] = 1;
		mat[3][3] = 1;
	}

	void setScale(const Vec3& scale)
	{
		mat[0][0] = scale.x;
		mat[1][1] = scale.y;
		mat[2][2] = scale.z;
	}

	void setTranslation(const Vec3& translation)
	{
		mat[3][0] = translation.x;
		mat[3][1] = translation.y;
		mat[3][2] = translation.z;
	}


	void setRotationX(float x)
	{
		mat[1][1] = cos(x);
		mat[1][2] = sin(x);
		mat[2][1] = -sin(x);
		mat[2][2] = cos(x);
	}

	void setRotationY(float y)
	{
		mat[0][0] = cos(y);
		mat[0][2] = -sin(y);
		mat[2][0] = sin(y);
		mat[2][2] = cos(y);
	}

	void setRotationZ(float z)
	{
		mat[0][0] = cos(z);
		mat[0][1] = sin(z);
		mat[1][0] = -sin(z);
		mat[1][1] = cos(z);
	}

	float getDeterminant()
	{
		Vec4 minor, v1, v2, v3;
		float det;

		v1 = Vec4(this->mat[0][0], this->mat[1][0], this->mat[2][0], this->mat[3][0]);
		v2 = Vec4(this->mat[0][1], this->mat[1][1], this->mat[2][1], this->mat[3][1]);
		v3 = Vec4(this->mat[0][2], this->mat[1][2], this->mat[2][2], this->mat[3][2]);


		minor.cross(v1, v2, v3);
		det = -(this->mat[0][3] * minor.x + this->mat[1][3] * minor.y + this->mat[2][3] * minor.z +
			this->mat[3][3] * minor.w);
		return det;
	}

	void inverse()
	{
		int a, i, j;
		Mat4 out;
		Vec4 v, vec[3];
		float det = 0.0f;

		det = this->getDeterminant();
		if (!det) return;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (j != i)
				{
					a = j;
					if (j > i) a = a - 1;
					vec[a].x = (this->mat[j][0]);
					vec[a].y = (this->mat[j][1]);
					vec[a].z = (this->mat[j][2]);
					vec[a].w = (this->mat[j][3]);
				}
			}
			v.cross(vec[0], vec[1], vec[2]);

			out.mat[0][i] = (float)pow(-1.0f, i) * v.x / det;
			out.mat[1][i] = (float)pow(-1.0f, i) * v.y / det;
			out.mat[2][i] = (float)pow(-1.0f, i) * v.z / det;
			out.mat[3][i] = (float)pow(-1.0f, i) * v.w / det;
		}

		this->setMatrix(out);
	}
	void operator *=(const Mat4& matrix)
	{
		Mat4 out;
		for (auto i = 0; i < 4; i++)
		{
			for (auto j = 0; j < 4; j++)
			{
				out.mat[i][j] =
					mat[i][0] * matrix.mat[0][j] +
					mat[i][1] * matrix.mat[1][j] +
					mat[i][2] * matrix.mat[2][j] +
					mat[i][3] * matrix.mat[3][j];
			}
		}
		setMatrix(out);
	}

	void setMatrix(const Mat4& matrix)
	{
		::memcpy(mat, matrix.mat, sizeof(float) * 16);
	}

	Vec3 getTranslation()
	{
		return Vec3(mat[3][0], mat[3][1], mat[3][2]);
	}

	Vec3 getRightwardDirection()
	{
		return Vec3(mat[0][0], mat[0][1], mat[0][2]);
	}
	Vec3 getUpDirection()
	{
		return Vec3(mat[1][0], mat[1][1], mat[1][2]);
	}
	Vec3 getForwardDirection()
	{
		return Vec3(mat[2][0], mat[2][1], mat[2][2]);
	}


	void setOrthoLH(float width, float height, float nearPlane, float farPlane)
	{
		mat[0][0] = 2.0f / width;
		mat[1][1] = 2.0f / height;
		mat[2][2] = 1.0f / (farPlane - nearPlane);
		mat[3][2] = -(nearPlane / (farPlane - nearPlane));
	}

	void setPerspectiveFovLH(float fov, float aspect, float znear, float zfar)
	{
		setIdentity();
		float yscale = 1.0f / (float)tan(fov / 2.0f);
		float xscale = yscale / aspect;
		mat[0][0] = xscale;
		mat[1][1] = yscale;
		mat[2][2] = zfar / (zfar - znear);
		mat[2][3] = 1.0f;
		mat[3][2] = (-znear * zfar) / (zfar - znear);
		mat[3][3] = 0.0f;
	}

public:
	float mat[4][4] = {};
};