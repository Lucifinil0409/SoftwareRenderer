#pragma once
#include<math.h>
#include<vector>
#include"Vec.h"

#define MY_PI 3.1415926

#ifndef MAT3X3
#define MAT3X3
class Mat3x3 {
private:
	static int Mat3x3Width;
public:
	float a[3][3];

	Mat3x3() = default;
	Mat3x3(const float value) {
		for (int i = 0; i < Mat3x3Width; i++) {
			for (int j = 0; j < Mat3x3Width; j++) {
				a[i][j] = value;
			}
		}
	}
	Mat3x3(const Mat3x3 &value) {
		for (int i = 0; i < Mat3x3Width; i++) {
			for (int j = 0; j < Mat3x3Width; j++) {
				a[i][j] = value.a[i][j];
			}
		}
	}
	~Mat3x3();

	static int width() { return Mat3x3Width; }

	static Mat3x3 unitMat() {
		Mat3x3 tempMat(0.0f);
		tempMat.a[0][0] = 1.0f;
		tempMat.a[1][1] = 1.0f;
		tempMat.a[2][2] = 1.0f;
		return tempMat;
	}

	Mat3x3 operator=(const Mat3x3 value) {
		for (int i = 0; i < Mat3x3Width; i++) {
			for (int j = 0; j < Mat3x3Width; j++) {
				this->a[i][j] = value.a[i][j];
			}
		}
	}

	Mat4x4 toMat4x4() const {
		Mat4x4 tempMat(0.0f);
		for (int i = 0; i < Mat3x3Width; i++) {
			for (int j = 0; j < Mat3x3Width; j++) {
				tempMat.a[i][j] = this->a[i][j];
			}
		}
		tempMat.a[3][3] = 1.0f;
		return tempMat;
	}

	Mat3x3 transpose() const {
		Mat3x3 tempMat(0.0f);
		for (int i = 0; i < Mat3x3Width; i++) {
			for (int j = 0; j < Mat3x3Width; j++) {
				tempMat.a[i][j] = this->a[j][i];
			}
		}
		return tempMat;
	}

	void LUdecomposition(Mat3x3 &L, Mat3x3 &U) {
		//初始化L，U 计算第一轮初始值（L的第一列，L的对角线1，U的第一行）
		L = Mat3x3::unitMat();
		U = Mat3x3(0.0f);
		for (int k = 0; k < Mat3x3Width; k++) {
			U.a[0][k] = this->a[0][k];
			L.a[k][0] = this->a[k][0] / U.a[0][0];
		}
		//第k轮
		for (int k = 1; k < Mat3x3Width; k++) {
			//计算U矩阵的第k行 第j列的值
			for (int j = k; j < Mat3x3Width; j++) {
				float tempMutAdd = 0.0f;
				for (int m = 0; m < k - 1; m++) {
					tempMutAdd = tempMutAdd + L.a[k][m] * U.a[m][j];
				}
				U.a[k][j] = this->a[k][j] - tempMutAdd;
			}
			//计算L矩阵的第i行 第k列的值
			for (int i = k; i < Mat3x3Width; i++) {
				float tempMutAdd = 0.0f;
				for (int m = 0; m < k - 1; m++) {
					tempMutAdd = tempMutAdd + L.a[i][m] * U.a[m][k];
				}
				L.a[i][k] = (this->a[i][k] - tempMutAdd) / U.a[k][k];
			}
		}
		return;
	}

	//求上下三角矩阵的逆矩阵
	Mat3x3 Linverse(const Mat3x3 L) const {
		Mat3x3 tempMat(0.0f);
		//对角线上为倒数
		for (int i = 0; i < Mat3x3Width; i++) {
			tempMat.a[i][i] = 1 / L.a[i][i];
		}
		//计算下三角的数值
		for (int i = 1; i < Mat3x3Width; i++) {
			for (int j = 0; j < i; j++) {
				float tempMutAdd = 0.0f;
				for (int k = j; k < i - 1; k++) {
					tempMutAdd = tempMutAdd + L.a[i][k] * tempMat.a[k][j];
				}
				tempMat.a[i][j] = -tempMutAdd / L.a[i][i];
			}
		}
		return tempMat;
	}
	Mat3x3 Uinverse(Mat3x3 U) {
		return Linverse(U.transpose()).transpose();
	}

	Mat3x3 inverse() {
		//是否需要判断矩阵是否可逆???

		Mat3x3 matL, matU;
		LUdecomposition(matL, matU);
		Mat3x3 matUinverse = Uinverse(matU);
		Mat3x3 matLinverse = Linverse(matL);
		return Mat3x3(matUinverse * matLinverse);
	}

};

int Mat3x3::Mat3x3Width = 3;

inline Mat3x3 operator+(Mat3x3 mat1, Mat3x3 mat2) {
	Mat3x3 tempMat(0.0f);
	for (int i = 0; i < Mat3x3::width(); i++) {
		for (int j = 0; j < Mat3x3::width(); j++) {
			tempMat.a[i][j] = mat1.a[i][j] + mat2.a[i][j];
		}
	}
	return tempMat;
}

inline Mat3x3 operator+(Mat3x3 mat1, float value) {
	Mat3x3 tempMat(0.0f);
	for (int i = 0; i < Mat3x3::width(); i++) {
		for (int j = 0; j < Mat3x3::width(); j++) {
			tempMat.a[i][j] = mat1.a[i][j] + value;
		}
	}
	return tempMat;
}

inline Mat3x3 operator+(float value, Mat3x3 mat1) {
	return operator+(mat1, value);
}

inline Mat3x3 operator*(Mat3x3 mat1, Mat3x3 mat2) {
	Mat3x3 tempMat(0.0f);
	for (int i = 0; i < Mat3x3::width(); i++) {
		for (int j = 0; j < Mat3x3::width(); j++) {
			for (int k = 0; k < Mat3x3::width(); k++) {
				tempMat.a[i][j] = tempMat.a[i][j] + mat1.a[i][k] * mat2.a[k][j];
			}
		}
	}
	return tempMat;
}

inline Mat3x3 operator*(Mat3x3 mat1, float value) {
	Mat3x3 tempMat(0.0f);
	for (int i = 0; i < Mat3x3::width(); i++) {
		for (int j = 0; j < Mat3x3::width(); j++) {
			tempMat.a[i][j] = mat1.a[i][j] * value;
		}
	}
	return tempMat;
}

inline Mat3x3 operator*(float value, Mat3x3 mat1) {
	return operator*(mat1, value);
}

#endif//endif MAT3X3



#ifndef MAT4X4
#define MAT4X4
class Mat4x4 {
private:
	static int Mat4x4Width;
public:
	float a[4][4];

	Mat4x4() = default;
	Mat4x4(const float value) {
		for (int i = 0; i < Mat4x4Width; i++) {
			for (int j = 0; j < Mat4x4Width; j++) {
				a[i][j] = value;
			}
		}
	}
	Mat4x4(const Mat4x4 &value) {
		for (int i = 0; i < Mat4x4Width; i++) {
			for (int j = 0; j < Mat4x4Width; j++) {
				a[i][j] = value.a[i][j];
			}
		}
	}
	~Mat4x4();

	static int width() { return Mat4x4Width; }

	static Mat4x4 unitMat() {
		Mat4x4 tempMat(0.0f);
		tempMat.a[0][0] = 1.0f;
		tempMat.a[1][1] = 1.0f;
		tempMat.a[2][2] = 1.0f;
		tempMat.a[3][3] = 1.0f;
		return tempMat;
	}

	Mat3x3 toMat3x3() const {
		Mat3x3 tempMat(0.0f);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				tempMat.a[i][j] = this->a[i][j];
			}
		}
		return tempMat;
	}

	Mat4x4 transpose() const {
		Mat4x4 tempMat(0.0f);
		for (int i = 0; i < Mat4x4Width; i++) {
			for (int j = 0; j < Mat4x4Width; j++) {
				tempMat.a[i][j] = this->a[j][i];
			}
		}
		return tempMat;
	}

	void LUdecomposition(Mat4x4 &L, Mat4x4 &U) {
		//初始化L，U 计算第一轮初始值（L的第一列，L的对角线1，U的第一行）
		L = Mat4x4::unitMat();
		U = Mat4x4(0.0f);
		for (int k = 0; k < Mat4x4Width; k++) {
			U.a[0][k] = this->a[0][k];
			L.a[k][0] = this->a[k][0] / U.a[0][0];
		}
		//第k轮
		for (int k = 1; k < Mat4x4Width; k++) {
			//计算U矩阵的第k行 第j列的值
			for (int j = k; j < Mat4x4Width; j++) {
				float tempMutAdd = 0.0f;
				for (int m = 0; m < k - 1; m++) {
					tempMutAdd = tempMutAdd + L.a[k][m] * U.a[m][j];
				}
				U.a[k][j] = this->a[k][j] - tempMutAdd;
			}
			//计算L矩阵的第i行 第k列的值
			for (int i = k; i < Mat4x4Width; i++) {
				float tempMutAdd = 0.0f;
				for (int m = 0; m < k - 1; m++) {
					tempMutAdd = tempMutAdd + L.a[i][m] * U.a[m][k];
				}
				L.a[i][k] = (this->a[i][k] - tempMutAdd) / U.a[k][k];
			}
		}
		return;
	}

	//求上下三角矩阵的逆矩阵
	Mat4x4 Linverse(const Mat4x4 L) const{
		Mat4x4 tempMat(0.0f);
		//对角线上为倒数
		for (int i = 0; i < Mat4x4Width; i++) {
			tempMat.a[i][i] = 1 / L.a[i][i];
		}
		//计算下三角的数值
		for (int i = 1; i < Mat4x4Width; i++) {
			for (int j = 0; j < i; j++) {
				float tempMutAdd = 0.0f;
				for (int k = j; k < i - 1; k++) {
					tempMutAdd = tempMutAdd + L.a[i][k] * tempMat.a[k][j];
				}
				tempMat.a[i][j] = -tempMutAdd / L.a[i][i];
			}
		}
		return tempMat;
	}
	Mat4x4 Uinverse(Mat4x4 U) {
		return Linverse(U.transpose()).transpose();
	}

	Mat4x4 inverse() {
		//是否需要判断矩阵是否可逆???

		Mat4x4 matL, matU;
		LUdecomposition(matL, matU);
		Mat4x4 matUinverse = Uinverse(matU);
		Mat4x4 matLinverse = Linverse(matL);
		return Mat4x4(matUinverse * matLinverse);
	}	

};

int Mat4x4::Mat4x4Width = 4;

inline Mat4x4 operator+(Mat4x4 mat1, Mat4x4 mat2) {
	Mat4x4 tempMat(0.0f);
	for (int i = 0; i < Mat4x4::width(); i++) {
		for (int j = 0; j < Mat4x4::width(); j++) {
			tempMat.a[i][j] = mat1.a[i][j] + mat2.a[i][j];
		}
	}
	return tempMat;
}

inline Mat4x4 operator+(Mat4x4 mat1, float value) {
	Mat4x4 tempMat(0.0f);
	for (int i = 0; i < Mat4x4::width(); i++) {
		for (int j = 0; j < Mat4x4::width(); j++) {
			tempMat.a[i][j] = mat1.a[i][j] + value;
		}
	}
	return tempMat;
}

inline Mat4x4 operator+(float value, Mat4x4 mat1) {
	return operator+(mat1, value);
}


inline Mat4x4 operator*(Mat4x4 mat1, Mat4x4 mat2) {
	Mat4x4 tempMat(0.0f);
	for (int i = 0; i < Mat4x4::width(); i++) {
		for (int j = 0; j < Mat4x4::width(); j++) {
			for (int k = 0; k < Mat4x4::width(); k++) {
				tempMat.a[i][j] = tempMat.a[i][j] + mat1.a[i][k] * mat2.a[k][j];
			}
		}
	}
	return tempMat;
}

inline Vec4 operator*(Mat4x4 mat, Vec4 vec) {
	Vec4 tempVec(0.0f);
	tempVec.x = mat.a[0][0] * vec.x + mat.a[0][1] * vec.y + mat.a[0][2] * vec.z + mat.a[0][3] * vec.w;
	tempVec.y = mat.a[1][0] * vec.x + mat.a[1][1] * vec.y + mat.a[1][2] * vec.z + mat.a[1][3] * vec.w;
	tempVec.z = mat.a[2][0] * vec.x + mat.a[2][1] * vec.y + mat.a[2][2] * vec.z + mat.a[2][3] * vec.w;
	tempVec.w = mat.a[3][0] * vec.x + mat.a[3][1] * vec.y + mat.a[3][2] * vec.z + mat.a[3][3] * vec.w;
	return tempVec;
}

inline Mat4x4 operator*(Mat4x4 mat1, float value) {
	Mat4x4 tempMat(0.0f);
	for (int i = 0; i < Mat4x4::width(); i++) {
		for (int j = 0; j < Mat4x4::width(); j++) {
			tempMat.a[i][j] = mat1.a[i][j] * value;
		}
	}
	return tempMat;
}

inline Mat4x4 operator*(float value, Mat4x4 mat1) {
	return operator*(mat1, value);
}

Mat4x4 matTranslate(const Mat4x4 mat, const Vec3 transValue) {
	Mat4x4 tempMat(mat);
	tempMat.a[0][3] = transValue.x;
	tempMat.a[1][3] = transValue.y;
	tempMat.a[2][3] = transValue.z;
	return tempMat;
}

Mat4x4 matTranslate(const Mat4x4 mat, const float transValueX, const float transValueY, const float transValueZ) {
	Mat4x4 tempMat(mat);
	tempMat.a[0][3] = transValueX;
	tempMat.a[1][3] = transValueY;
	tempMat.a[2][3] = transValueZ;
	return tempMat;
}

Mat4x4 matScale(const Mat4x4 mat, const Vec3 scaleValue) {
	Mat4x4 tempMat(mat);
	tempMat.a[0][0] = tempMat.a[0][0] * scaleValue.x;
	tempMat.a[1][1] = tempMat.a[1][1] * scaleValue.y;
	tempMat.a[2][2] = tempMat.a[2][2] * scaleValue.z;
	return tempMat;
}

Mat4x4 matScale(const Mat4x4 mat, const float scaleValue) {
	Mat4x4 tempMat(mat);
	tempMat.a[0][0] = tempMat.a[0][0] * scaleValue;
	tempMat.a[1][1] = tempMat.a[1][1] * scaleValue;
	tempMat.a[2][2] = tempMat.a[2][2] * scaleValue;
	return tempMat;
}

Mat4x4 matScale(const Mat4x4 mat, const float scaleValueX, const float scaleValueY, const float scaleValueZ) {
	Mat4x4 tempMat(mat);
	tempMat.a[0][0] = tempMat.a[0][0] * scaleValueX;
	tempMat.a[1][1] = tempMat.a[1][1] * scaleValueY;
	tempMat.a[2][2] = tempMat.a[2][2] * scaleValueZ;
	return tempMat;
}

Mat4x4 matRotate(const Mat4x4 mat, const float angle, const Vec3 axis) {
	float radian = angle * MY_PI / 180;
	float cosValue = cos(radian), sinValue = sin(radian);
	Vec3 normalAxis = axis.normalize();
	float u = normalAxis.x, v = normalAxis.y, w = normalAxis.z;
	//计算3x3的旋转矩阵
	Mat4x4 rotateMat = Mat4x4::unitMat();
	rotateMat.a[0][0] = u * u + (1 - u * u)*cosValue;			rotateMat.a[0][1] = u * v*(1 - cosValue) - w * sinValue;	rotateMat.a[0][2] = u * w*(1 - cosValue) + v * sinValue;
	rotateMat.a[1][0] = u * v*(1 - cosValue) + w * sinValue;	rotateMat.a[1][1] = v * v + (1 - v * v)*cosValue;			rotateMat.a[1][2] = v * w*(1 - cosValue) - u * sinValue;
	rotateMat.a[2][0] = u * w*(1 - cosValue) - v * sinValue;	rotateMat.a[2][1] = v * w*(1 - cosValue) + u * sinValue;	rotateMat.a[2][2] = w * w + (1 - w * w)*cosValue;

	Mat4x4 tempMat = rotateMat * mat;
	return tempMat;
}

void applyTrans(Mat4x4 trans, std::vector<Vec4> &pointArray) {
	size_t pointCount = pointArray.size();
	for (unsigned int i = 0; i < pointCount; i++) {
		pointArray[i] = trans * pointArray[i];
	}
	return;
}

#endif//endif MAT4X4