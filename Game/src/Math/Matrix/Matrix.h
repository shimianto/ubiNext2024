#pragma once
#include "../../Scene/Components/Transform/Transform.h"
class Vector3;

class Matrix
{
public:
    float m[4][4];
	Matrix();

    float &operator() (int row, int col);

	Matrix operator* (const Matrix &matrix);
    Matrix operator*= (const Matrix &matrix);

    static Matrix Identity();
    static Matrix Translate (const Vector3 &v);

    static Matrix MakeProjectionMatrix (const float &fov, const float &near, const float &far);
    static Matrix MakeRotationMatrix (const Vector3 &rotation);
    static Matrix MakeRotationMatrixX (const float &fAngleRad = 0);
    static Matrix MakeRotationMatrixY (const float &fAngleRad = 0);
    static Matrix MakeRotationMatrixZ (const float &fAngleRad = 0);
    static Matrix MakeScaledMatrix (const Vector3 &v);
    static Matrix MakeTransformedMatrix (const Transform &transform);
};
