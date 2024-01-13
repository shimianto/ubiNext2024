#pragma once
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

    static Matrix Translate (Vector3 &v);
};
