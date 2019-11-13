#pragma once

#ifndef CAMERA
#define CAMERA

#include "Mat.h"

class Camera {
public: 
	int state;//相机状态
	int attr;//相机属性

	Vec3 cameraPos;
	Vec3 viewDirection;
	Vec3 U, V, N;
	
	float cameraFov;

	//此时距离投影平面viewplane的距离d==1,且fov为垂直方向视野
	float halfViewplaneHeight;
	float halfViewplaneWidth;

	float viewportWidth;
	float viewportHeight;
	float aspectRatio;

	float nearClipZ;
	float farClipZ;

	Mat4x4 mCam;
	Mat4x4 mPer;
	Mat4x4 mScr;

	Camera(){}
	Camera(Vec3 pos, Vec3 dir, float fov, float width, float height, float nearZ, float farZ) {
		cameraPos = pos;
		viewDirection = dir;

		Vec3 viewTarget(0, 0, 0);
		float r = cos(dir.x / 180 * MY_PI);
		viewTarget.x = r * sin(dir.y / 180 * MY_PI);
		viewTarget.y = sin(dir.x / 180 * MY_PI);
		viewTarget.x = r * cos(dir.y / 180 * MY_PI);

		//U,V,N
		N = (viewTarget - cameraPos).normalize();
		Vec3 up(0.0f, 1.0f, 0.0f);
		U = cross(up, N).normalize();
		V = cross(N, U);

		cameraFov = fov;
		aspectRatio = width / height;
		nearClipZ = nearZ;
		farClipZ = farZ;

		//此时距离投影平面viewplane的距离d==1
		halfViewplaneHeight = tan((fov / 2) / 180 * MY_PI);
		halfViewplaneWidth = halfViewplaneHeight * aspectRatio;

		viewportWidth = width;
		viewportHeight = height;
		
	}
	~Camera(){}

	void UpdateCamera() {
		//计算相机观察方向
		Vec3 viewTarget(0, 0, 0);
		float r = cos(viewDirection.x / 180 * MY_PI);
		viewTarget.x = r * sin(viewDirection.y / 180 * MY_PI);
		viewTarget.y = sin(viewDirection.x / 180 * MY_PI);
		viewTarget.x = r * cos(viewDirection.y / 180 * MY_PI);

		//U,V,N
		N = (viewTarget - cameraPos).normalize();
		Vec3 up(0.0f, 1.0f, 0.0f);
		U = cross(up, N).normalize();
		V = cross(N, U);

		//此时距离投影平面viewplane的距离d==1
		halfViewplaneHeight = tan((cameraFov / 2) / 180 * MY_PI);
		halfViewplaneWidth = halfViewplaneHeight * aspectRatio;
	}

	Mat4x4 calViewMatrix() {
		Mat4x4 viewMat(0);
		viewMat.a[0][0] = U.x;	viewMat.a[0][1] = U.y;	viewMat.a[0][2] = U.z;	viewMat.a[0][3] = -cameraPos.x;
		viewMat.a[1][0] = V.x;	viewMat.a[1][1] = V.y;	viewMat.a[1][2] = V.z;	viewMat.a[1][3] = -cameraPos.y;
		viewMat.a[2][0] = N.x;	viewMat.a[2][1] = N.y;	viewMat.a[2][2] = N.z;	viewMat.a[2][3] = -cameraPos.z;
		viewMat.a[3][0] = 0;	viewMat.a[3][1] = 0;	viewMat.a[3][2] = 0;	viewMat.a[3][3] = 1;

		return viewMat;
	}
	Mat4x4 calPerspectiveMatrix() {
		Mat4x4 projectMat(0);
		projectMat.a[0][0] = 1.0f / halfViewplaneWidth;
		projectMat.a[1][1] = 1.0f / halfViewplaneHeight;
		projectMat.a[2][2] = farClipZ / (farClipZ - nearClipZ);
		projectMat.a[2][3] = -farClipZ * nearClipZ / (farClipZ - nearClipZ);

		projectMat.a[3][2] = 1;
		return projectMat;
	}
	Mat4x4 calScreenMatrix() {
		Mat4x4 screenMat(0);
		float alpha = (0.5f * viewportWidth - 0.5f);
		float beta = (0.5f * viewportHeight - 0.5f);
		screenMat.a[0][0] = alpha;
		screenMat.a[1][1] = -beta;
		screenMat.a[2][2] = 1.0f;
		screenMat.a[3][3] = 1.0f;

		screenMat.a[0][2] = alpha;
		screenMat.a[1][2] = beta;
		return screenMat;
	}


};




#endif



